#ifndef FUNC_HPP
#define FUNC_HPP

#include <functional>

namespace cs540{



  template <typename R, typename ... Args>
  class Function{

    public:

      Function(R (*f)(Args...)): func{f}{
      }

      R(*func)(Args...);

  };









}




#endif //FUNC_HPP
