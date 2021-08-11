
#include "dsets.h"

DisjointSets::DisjointSets() : _elems(0)
{
//Nothin
}


void DisjointSets::addelements(int num)
{


  for (int i = 0; i < num; ++i) {
    _elems.push_back(-1);
  }
  
}


int DisjointSets::find(int elem)
{
  if (_elems[elem] < 0) {return elem;}
  else {
    int root = find(_elems[elem]);
    _elems[elem] = root;
    return root;
  }
}


void DisjointSets::setunion(int a, int b)
{
  int idxA = find(a);
  int idxB = find(b);

  int newSize = _elems[idxA] + _elems[idxB];

  if (_elems[idxA] <= _elems[idxB]) {
    _elems[idxB] = idxA;
    _elems[idxA] = newSize;
  }
  else {
    _elems[idxA] = idxB;
    _elems[idxB] = newSize;
  }
}


int DisjointSets::size(int elem) {
  return -_elems[find(elem)];
}
