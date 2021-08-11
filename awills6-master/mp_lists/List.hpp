/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() //: head_(NULL), tail_(NULL)
{
  head_ = nullptr;
  tail_ = nullptr;
  length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_); // previously return List<T>::ListIterator(NULL);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(nullptr);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  if (head_) {
    ListNode* curr = head_;

    while (curr->next) {
      ListNode* temp = curr;
      curr = curr->next;
      delete temp;
    }
    delete curr;
  }
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  ListNode* newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = nullptr;

  if (head_) {head_ -> prev = newNode;}
  head_ = newNode; // function should update the head
  if (!tail_) {tail_ = newNode; }

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {

  ListNode* newNode = new ListNode(ndata);
  newNode->next = nullptr;
  newNode->prev = tail_;

  if (tail_) {tail_->next = newNode;}
  tail_ = newNode;
  if (!head_) {head_ = tail_;}

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {

  if (!start) {return nullptr;}
  if (splitPoint == 0) {return head_;}

  ListNode* curr = start;
  ListNode* prev = nullptr;

  for(int i = 0; i < splitPoint && curr; ++i){
    prev = curr;
    curr = curr->next;
  }

  if (curr) {curr->prev = nullptr;}
  if (prev) {prev->next = nullptr;}

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if (this->empty()) {return;}
  if (!head_->next || (head_->next == tail_)) {return;} //lists of size 1&2  unchanged

  ListNode* curr = head_;
  ListNode* prev = nullptr;

  while (curr->next && curr->next != tail_) {
    ListNode* move = curr->next; // skip a node each iteration
    ListNode* movePrev = curr;

    move->next->prev = movePrev; // cut move out of list
    movePrev->next = move->next;

    move->next = nullptr; // put move at end
    move->prev = tail_;

    tail_->next = move;
    tail_ = move; // update tail

    prev = curr;
    curr = curr->next; // increment
  }
  return;
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */

template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if (this->empty() || length_ == 1) {return;}
  if (!startPoint || !endPoint) {return;}
  if (startPoint == endPoint) {return;} //tryna exhaust all possible ridiculousness
  if (endPoint == head_ || startPoint == tail_) {return;} //??

  ListNode* startPrev = startPoint->prev; //retain node prior to start
  startPoint->prev = nullptr; // separate start of list from previous node

  ListNode* endNext = endPoint->next; //retain node after end
  endPoint->next = nullptr; // separate end of list from next node

  ListNode* curr = startPoint;
  while (curr) {                // flip prev and next pointers, reversing segment
    ListNode* temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = curr->prev;
  }

  ListNode* temp = startPoint; // flip start and end
  startPoint = endPoint;
  endPoint = temp;

  if (startPrev) {startPrev->next = startPoint;} // if startPoint was not head, reattach
  else {head_ = startPoint;}
  startPoint->prev = startPrev;

  if (endNext) {endNext->prev = endPoint;} // if endPoint was not tail, reattach
  else {tail_ = endPoint;}
  endPoint->next = endNext;
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if (n == 0 || n == 1) {return;} //n = 0 doesn't make sense, n = 1 returns original
  if (n >= length_) { // for n > length_ just reverse it who cares
    reverse();
    return;
  }
  int num_blocks = (this->length_ / n); //length_ % n blocks will be left over
  ListNode* start = head_;
  ListNode* end = start;

  for (int i = 0; i < num_blocks; ++i) {
    end = start;
    for (int j = 0; j < n-1; ++j) {  // reverse chunks of N
      end = end->next;
    }
    reverse(start,end);
    if (end->next) {start = end->next;} // if we're not done yet, set up next N

  }

    if (end->next) { // if we're not done, length_ wasnt evenly divided by N
    end = tail_;     // do the rest
    reverse(start,end);
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_) {
        while (tail_->next) {
          tail_ = tail_->next;
        }    //
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = nullptr;
    otherList.tail_ = nullptr;
    otherList.length_ = 0;


}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode* first, ListNode* second) {

  if (!first) {return second;}
  if (!second) {return first;}

  ListNode* ref1 = first;
  ListNode* ref2 = second;  // to avoid actually changing values of first/second

  ListNode* newHead = nullptr;
  if (ref2->data < ref1->data) { // first->data >= second->data
    newHead = ref2;                  // set head to lowest of two values
    ref2 = ref2->next;
  }
  else {
    newHead = ref1;
    ref1 = ref1->next;
  }

  ListNode* headRef = newHead;         // maintain reference to new head
  while (ref1 && ref2) {
    if (ref2->data < ref1->data) {
      newHead->next = ref2;          // set newHead->next to lowest of 2 vals
      ref2 = ref2->next;
    }
    else {
      newHead->next = ref1;
      ref1 = ref1->next;
    }
    newHead->next->prev = newHead;     // set prev pointers
    newHead = newHead->next;
  }

  newHead->next = (ref2) ? ref2 : ref1;  // if either list has remaining
  newHead->next->prev = newHead;              // items, set rest of new list as
  return headRef;                             // rest of original list
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {

  if (!start) {return nullptr;}   // empty list
  if (chainLength == 0||chainLength == 1) {return start;} // 1-member lists

  int l1 = chainLength/2;
  int l2 = chainLength-l1; //if chainLength not divisible by 2

  ListNode* head2 = split(start,l1); //get another list, l=this->length - chainLength
  ListNode* head1 = start;

  head1 = mergesort(head1,l1);
  head2 = mergesort(head2,l2);

  return merge(head1,head2);
}
