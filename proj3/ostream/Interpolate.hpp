#ifndef interp_hpp
#define interp_hpp


#include <assert.h>
#include <iostream>
#include <tuple>


#include <typeinfo>
#include <cxxabi.h>
#include <type_traits>

std::ostream &
operator<<(std::ostream &os, const std::type_info &ti) {
    int ec;
    char *p = abi::__cxa_demangle(ti.name(), 0, 0, &ec);
    assert(ec == 0);
    std::string s(p);
    free(p);
    return os << s;
}

namespace cs540{
  
  //template <typename T, std::size_t... Is>  
  class Streamer{
      std::string s;
  public:

      template <std::size_t... Is>
      Streamer(std::string sIn, std::index_sequence<Is...> tIn){ 
      

      }  

      

      inline friend std::ostream& operator << (std::ostream & os, Streamer & dt){
        os << dt.s;
        return os;
      }

  };


  template <typename T>
  auto InterHelper(T last){
    return std::make_tuple(last);
  }

  template <typename T, typename... Ts>
  auto InterHelper(T first, Ts... rest){
    return std::make_tuple(first, InterHelper(rest...));
  }


  template <typename... Ts>
  auto Interpolate(std::string first, Ts... rest){
    auto packed = InterHelper(rest...);
    auto sequence = std::make_index_sequence<std::tuple_size<decltype(packed)>::value>();
    return Streamer(first, sequence);
    //return Streamer<decltype(packed), decltype(std::tuple_size<decltype(packed)>::value)>(first, packed);
    //return Streamer<decltype(std::tuple_size<decltype(packed)>::value)>(first, sequence);
    //return Streamer<std::tuple_size<decltype(packed)>::value>(first, sequence);
  }



  


}

#endif //interp_hpp
