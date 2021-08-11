/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <cstdlib>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}
/*
template <class K, class V>
typename AVLTree<K,V>::Node*& AVLTree<K,V>::_find(Node*& root, const K& key)
{
  if (!root) {return root;}
  if (root->key == key) {return root;}
  if (root->key > key) {
    Node*& root_L = root->left;
    return _find(root_L,key);
  }
  else if (root->key < key) {
    Node*& root_R = root->right;
    return _find(root_R,key);
  }
}
*/
template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node* x = t->right;
    t->right = x->left;
    t->height = 1+std::max(heightOrNeg1(t->left),heightOrNeg1(t->right));
    x->left = t;
    x->height = 1+std::max(heightOrNeg1(x->left),heightOrNeg1(x->right));
    t = x;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* x = t->left;
    t->left = x->right;
    t->height = 1+std::max(heightOrNeg1(t->left),heightOrNeg1(t->right));
    x->right = t;
    x->height = 1+std::max(heightOrNeg1(x->left),heightOrNeg1(x->right));
    t = x;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    int b = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    if (b == -2) {
      int b_L = heightOrNeg1(subtree->left->right) -
                heightOrNeg1(subtree->left->left);
      if (b_L == -1) {rotateRight(subtree);}
      else {rotateLeftRight(subtree);}
    }
    else if (b == 2) {
      int b_R = heightOrNeg1(subtree->right->right) -
                heightOrNeg1(subtree->right->left);
      if (b_R == 1) {rotateLeft(subtree);}
      else {rotateRightLeft(subtree);}
    }
    //subtree->right->height = getHeight(subtree->right);
    //subtree->left->height = getHeight(subtree->left);
    subtree->height = 1+std::max(heightOrNeg1(subtree->left),
                                 heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (!subtree) {subtree = new Node(key,value);}
    else if (key < subtree->key) {insert(subtree->left,key,value);}
    else if (key > subtree->key) {insert(subtree->right,key,value);}
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
    //rebalance(root);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL) {return;}

    if (key < subtree->key) {
        remove(subtree->left,key);
        //if (subtree) {rebalance(subtree);}
    } else if (key > subtree->key) {
        remove(subtree->right,key);
        //if (subtree) {rebalance(subtree);}
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            //Node* temp = subtree; //?
            delete subtree;
            subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove*/
            Node* tempRef = subtree->left;
            while (tempRef->right) {tempRef = tempRef->right;}
            swap(subtree,tempRef);
            remove(subtree->left,key);
            //if (subtree) {rebalance(subtree);}
        } else {
            /* one-child remove */
            Node* temp_del = subtree;
            subtree = (subtree->left) ? subtree->left : subtree->right;
            delete temp_del;
            //if (subtree) {rebalance(subtree);}
        }
        if (subtree) {rebalance(subtree);}
        return;
    }
    if (subtree) {rebalance(subtree);}
    return;

}
