#include "Interpolate.hpp"
#include <iostream>
#include <tuple>


#include <assert.h>

using namespace std;
using namespace cs540;
int main(){

  auto i = Interpolate("Hello", std::uppercase, std::hex); 
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

