#ifndef interp_hpp
#define interp_hpp


#include <assert.h>
#include <iostream>
#include <tuple>
#include <iomanip>
#include <string>
#include <string.h>
#include <ctype.h>
#include <typeinfo>
#include <cxxabi.h>
#include <type_traits>
#include <exception>
#include <stdexcept>
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
  class WrongNumberOfArgs : public std::exception {

      virtual const char* what() const throw(){
        return "You passed an invalid number of args.";
      }
  };
  template <typename ... Ts>
    class StreamHelper {
      public:        
        StreamHelper(std::string & sIn, const Ts & ... ts) : s{sIn}, tup(ts ...){}
        inline friend std::ostream& operator << (std::ostream& os, const StreamHelper & sh){
          sh.interHelp(os, sh.tup, std::make_index_sequence<std::tuple_size<decltype(tup)>::value>());
          return os;
        }

        template <typename T, size_t ... Is>
        std::ostream& interHelp(std::ostream& os, const T & t, const std::index_sequence<Is...> &) const{
          return helper(os, s, std::get<Is>(t)...);
        }

        template <typename T, typename ... St>
        std::ostream & helper(std::ostream & os, std::string str, const T & t, const St & ... rest) const{
          //Find the next instance of a %
          std::size_t ind = std::string::npos;
          std::string ret = "";

          while((ind = str.find_first_of("%")) != std::string::npos){

            //Get the part of the string up to the first %
            std::string pre = str.substr(0, ind);
            
            
            if(checkIfEscaped(pre, pre.size() - 1)){
              
              //Insert pre without the \ and the %
              os << pre.substr(0, pre.size() - 1);
              os << "%";
              //Now reshape str
              str = str.substr(ind + 1);
              //Continue
              continue;

            }else{
              //Put pre in, the arg, create the ret, and break
              os << pre;
              os << t;
              ret = str.substr(ind + 1); 
              break;
            }
          
          }
          if(ind == std::string::npos){
            throw WrongNumberOfArgs();
          }

          return helper(os, ret, rest...);
        }
     
      bool checkIfEscaped(std::string string, size_t index) const {
        
        if(index < string.size())
          return string.at(index) == '\\';
        else
          return false;
      }
 
      std::ostream & helper(std::ostream & os, std::string str) const{
        //Check for any % first
        if(str.find_first_of("%") == std::string::npos){
          os << str;
        }else{
          throw WrongNumberOfArgs();  
        }
        return os;
      }
      private:
        std::string s;
        std::tuple<Ts...> tup;
    };



  //Function template to be called
  template <typename... Ts>
    auto Interpolate(std::string first,const Ts & ... rest){
      //Construct and return a streamer object
      return StreamHelper<const Ts & ...>(first, rest...);
    }



  //FFR
  auto ffr(std::ostream & (*f)(std::ostream &)){
    return f;
  }

}

#endif //interp_hpp
