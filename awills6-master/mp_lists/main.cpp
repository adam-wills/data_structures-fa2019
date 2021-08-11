#include "List.h"
#include <iostream>

int main() {
  List<int>* newList = new List<int>();


  for (int i = 8; i >0 ; --i) {
    newList->insertBack(i);
  }

  newList->print();
  std::cout << std::endl;

  newList->sort();
  newList->print();
  std::cout << std::endl;

  delete newList;

  return 0;
}
