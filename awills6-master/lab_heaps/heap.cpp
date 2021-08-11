
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return ((currentIdx-1)/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const /// doesnt make sense
{
    // @TODO Update to return whether the given node has a child

    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    //if (!hasAChild(currentIdx)) {return currentIdx;}
    size_t lIdx = leftChild(currentIdx);
    size_t rIdx = rightChild(currentIdx);
    if (!(rIdx < _elems.size())) {return lIdx;}
    return (higherPriority(_elems[lIdx],_elems[rIdx])) ? lIdx : rIdx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if (!hasAChild(currentIdx)) {return;}
    size_t childIdx = maxPriorityChild(currentIdx);
    if (higherPriority(_elems[childIdx],_elems[currentIdx])) {
      std::swap(_elems[childIdx],_elems[currentIdx]);
      heapifyDown(childIdx);
    }
    return;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    if (!elems.empty()) {
      _elems.insert(_elems.end(),elems.begin(),elems.end());
      size_t i = parent(_elems.size()-1);
      while (i > 0) {
        heapifyDown(i);
        --i;
      }
      heapifyDown(0);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if (empty()) {return T();}
    T ret = _elems[root()];
    std::swap(_elems[root()],_elems[_elems.size()-1]);
    _elems.pop_back();
    heapifyDown(root());
    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if (empty()) {return T();}
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
    return;
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    if (idx >= _elems.size()) {return;}
    _elems[idx] = elem;
    if (idx == root()) {
      heapifyDown(idx);
      return;
    }
    else if (!hasAChild(idx)) {
      heapifyUp(idx);
      return;
    }
    else {
      if (higherPriority(_elems[idx],_elems[parent(idx)])) {
        heapifyUp(idx);
      }
      else {heapifyDown(idx);}
      return;
    }

}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return _elems.empty();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
