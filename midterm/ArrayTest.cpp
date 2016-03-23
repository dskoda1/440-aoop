#include "Array2.hpp"
#include <iostream>



int main(){

  using cs540::Array2;

  Array2 a1(3, 4); // Creates an 3 by 4 array of ints. Initialized to zero.

  std::cout << "Indexing: " << std::endl;
  a1[2][3] = 1234; // Index operation.
  int &i1(a1[2][3]); // Bind ref.
  // Prints 1234 twice.
  std::cout << a1[2][3] << std::endl;
  std::cout << i1 << std::endl;
  i1 = 567; // Assigns to element.
  // Prints 567 twice.
  std::cout << a1[2][3] << std::endl;
  std::cout << i1 << std::endl;

  std::cout << "Iteration: " << std::endl;
  // Iterates in row-major order.
  int i = 0;
  for (auto it = a1.begin(); it != a1.end(); ++it) {
    *it = i++; // Can assign through iterator.
  }
  // Prints 0 through 11
  for (auto e : a1) {
    std::cout << e << " " << std::endl;
  }
  std::cout << "More iteration: " << std::endl;
  // it++ and ++it should work properly.
  auto it = a1.begin();
  std::cout << *it++ << std::endl; // Should print 0.
  std::cout << *it << std::endl; // Should print 1.
  std::cout << *++it << std::endl; // Should print 2.
  std::cout << *it << std::endl; // Should print 2.
}
