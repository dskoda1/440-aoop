#include "SmartPtr.hpp"

#include <iostream>

int main(){

  using cs540::SmartPtr; 

  SmartPtr<int> spi = new int(3); 

  SmartPtr<int> copy(spi);




}
