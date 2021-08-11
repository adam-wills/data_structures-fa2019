/* my code here! */

#pragma once
#include <vector>

class DisjointSets
{
  public:
    DisjointSets();

    // creates n unconnected root nodes at the end of the vector.
    // @param num: number of nodes to create
    void addelements(int num);

    // returns the representative member of the set to which elem belongs.
    // @param elem: member of up-tree
    // Returns: root of up-tree
    int find(int elem);


    // creates a union of the sets to which a and b belong.
    // the new representative element of the resulting joined set will
    // be the representative element of whichever set was initially larger
    // @params a, b: members of sets to be joined
    void setunion(int a, int b);

    // returns number of nodes in the up-tree containing the element
    // @param elem: element in question
    // Returns: size of up-tree to which element belongs
    int size(int elem);

  private:
    std::vector<int> _elems;
};
