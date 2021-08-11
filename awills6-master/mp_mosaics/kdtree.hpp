/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
      return (first[curDim] == second[curDim]) ?
          first < second : first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double pot_dist = getDistance(potential,target);
     double cur_dist = getDistance(currentBest,target);
     return (pot_dist == cur_dist) ?
        potential < currentBest : pot_dist < cur_dist;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if (!newPoints.empty()) {
       if (newPoints.size() > 1) {
         vector<Point<Dim>> points(newPoints);
         this->size = points.size();
         pointsToTree(points,this->root,0,points.size()-1,0);
       }
       else {
         Point<Dim> rootPoint = newPoints[0];
         this->root = new KDTreeNode(rootPoint);
         this->size = 1;
       }
     }
     else {
       this->size = 0;
       this->root = nullptr;
     }
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copy_(other.root,this->root);
   this->size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != &rhs) {
    clear_(this->root);
    copy_(rhs.root,this->root);
    this->size = rhs.size;
  }
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear_(root);
   size = 0;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    KDTreeNode* bestNode = nullptr;
    FNN_helper(query,root,bestNode,0);
    return bestNode->point;
}


template <int Dim>
void KDTree<Dim>::FNN_helper(const Point<Dim> &query,
                             KDTree<Dim>::KDTreeNode* subroot,
                             KDTree<Dim>::KDTreeNode*& curBestNode,
                             const int curDim) const
{
  if (subroot) {
    if (!subroot->left && !subroot->right) {
      FNN_update(query,subroot,curBestNode);
      return;
    }
  }
  else {return;}
  bool goLeft = smallerDimVal(query,subroot->point,curDim);

  FNN_helper(query,goLeft?subroot->left:subroot->right,curBestNode,(curDim+1)%Dim);
  FNN_update(query,subroot,curBestNode);

  double distToSplit = (subroot->point[curDim]-query[curDim]) *
                       (subroot->point[curDim]-query[curDim]);
  if (distToSplit > getDistance(curBestNode->point,query)) {return;}

  FNN_helper(query,goLeft?subroot->right:subroot->left,curBestNode,(curDim+1)%Dim);
  FNN_update(query,subroot,curBestNode);
}

template <int Dim>
void KDTree<Dim>::FNN_update(const Point<Dim>& query,
                             KDTree<Dim>::KDTreeNode* subroot,
                             KDTree<Dim>::KDTreeNode*& curBestNode) const
{
  if (!curBestNode){
    curBestNode = subroot;
  }
  else if (shouldReplace(query,curBestNode->point,subroot->point)) {
    curBestNode = subroot;
  }
  return;
}

template <int Dim>      // should make this generic for return type T (?)
double KDTree<Dim>::getDistance(const Point<Dim> &first,
                                const Point<Dim> & second) const
{
  double distance = 0;
  for (int i = 0; i < Dim; ++i) {
    distance += ((second[i]-first[i])*(second[i]-first[i]));
  }
  return distance;
}


template <int Dim>
void KDTree<Dim>::pointsToTree(vector<Point<Dim>> &points,
                               KDTree<Dim>::KDTreeNode*& subroot,
                               int l, int r, int curDim)
{
  if (l <= r ) {
    int medianIdx = floor(((double)(r+l))/2);
    //int k = ceil(((double)(r-l+1))/2);
    Point<Dim> swapPoint = kthSmallest(points,l,r,medianIdx,curDim);
    std::swap(points[medianIdx],swapPoint);
    subroot = new KDTreeNode(points[medianIdx]);
    if (l == r) {return;}

    int newDim = (curDim+1)%Dim;
    pointsToTree(points,subroot->left,l,medianIdx-1,newDim);
    pointsToTree(points,subroot->right,medianIdx+1,r,newDim);
  }
  return;
}


template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> &points, int l, int r,
                           int pivotIdx, int curDim)
{
  Point<Dim> pivotVal = points[pivotIdx];
  std::swap(points[pivotIdx],points[r]);
  int retIdx = l;
  for(int i = l; i < r; ++i) {
    if (smallerDimVal(points[i],pivotVal,curDim)) {
      std::swap(points[retIdx],points[i]);
      ++retIdx;
    }
  }
  std::swap(points[retIdx],points[r]);
  return retIdx;
}


template <int Dim>    //????
Point<Dim> KDTree<Dim>::kthSmallest(vector<Point<Dim>> &points, int l, int r,
                                int k, int curDim)
{
  srand(r);

  if (l == r) {return points[r];}
  int pivotIdx = l + floor(rand() % (r - l));
  pivotIdx = partition(points,l,r,pivotIdx,curDim);
  if (k == pivotIdx) {return points[k];}
  else if (k < pivotIdx) {return kthSmallest(points,l,pivotIdx-1,k,curDim);}
  else {return kthSmallest(points,pivotIdx+1,r,k,curDim);}
}


template <int Dim>
void KDTree<Dim>::copy_(const KDTree<Dim>::KDTreeNode* otherRoot,
                        KDTree<Dim>::KDTreeNode*& subroot)
{
  if (!otherRoot) {
    subroot = nullptr;
    return;
  }
  subroot = new KDTreeNode(otherRoot->point);
  copy_(otherRoot->left,subroot->left);
  copy_(otherRoot->right,subroot->right);
}


template <int Dim>
void KDTree<Dim>::clear_(KDTree<Dim>::KDTreeNode*& subroot)
{
  if (!subroot) {return;}
  clear_(subroot->left);
  clear_(subroot->right);
  delete subroot;
}
