#include "Interpolate.hpp"
#include <iostream>
#include <tuple>
#include <sstream>

#include <assert.h>

using namespace std;
using namespace cs540;

int main(){

  int i = 5;
  int j = 6;
  int k = 7;
  
  stringstream ss;

  ss << Interpolate(R"(i=%, j=%, 88\%, k=%)", i,j, k) << endl;

  cout << "the results of interpolate are" << endl;
  cout << ss.str() << endl;



  return 0;
}



/*
template <typename T>
const T & sum(const T &v){
  return v;
}

template <typename T, typename... Ts>
T sum(const T &v, const Ts & ... params){
  cout << sizeof...(params) << endl;
  return v + sum(params...);
}

template <typename T>
auto TestTF(T arg){

  return arg;
}

template <typename T, typename... Ts>
auto TestTF(T first, Ts ... args){
    
  return std::make_tuple(first, TestTF(args...));
}

template <typename... Ts>
class summer{

  public:
   summer(Ts... args){

    auto argtupe = std::make_tuple(args...);
  } 



};

*/

