#ifndef S_PTR_HPP
#define S_PTR_HPP

//Includes
#include <cstddef>
#include <iostream>

namespace cs540{

  template <typename T> class SharedPtr{
    private:

    public:
      /* Constructor */
      SharedPtr(){}

      /* Explicit Constructor */
      template <typename U> 
        explicit SharedPtr(U *){}

      /*
       * Copy Constructor
       * Increment the count by one.
       */
      SharedPtr(const SharedPtr &p){}

      template <typename U>
        SharedPtr(const SharedPtr<U> & p){}

      /*
       * Move constructor
       * The reference count remains unchanged.
       */
      SharedPtr(const SharedPtr && p){}

      template <typename U>
        SharedPtr(const SharedPtr<U> && p){}

      /*
       * Copy assignment operator.
       * Must be able to handle self assignment.
       */
      SharedPtr & operator = (const SharedPtr & p){}

      template <typename U>
        SharedPtr<T> & operator = (const SharedPtr<U> & p){}

      /*
       * Move assignment operator.
       */
      SharedPtr & operator = (SharedPtr && p){}

      template <typename U>
        SharedPtr<T> & operator = (SharedPtr<U> && p){}  

      /* Destructor */
      ~SharedPtr(){}

      /*********************
       * Modifiers
       *********************/


      /* Reset the pointer. */
      void reset(){};

      /* Replace the pointer with another pointer. */
      template <typename U>
        void reset(U * p){}

      /*********************
       * Observers 
       *********************/

      T * get() const {}

      T & operator * () {}

      T * operator -> () {}

      explicit operator bool() const{}

  };


  /*********************
   * Free Functions
   *********************/


  template <typename T1, typename T2>
    bool operator == (const SharedPtr<T1> & p1, const SharedPtr<T2> & p2){
      return false;
    }

  template <typename T>
    bool operator==(const SharedPtr<T> & p, std::nullptr_t np){
      return false;
    }

  template <typename T>
    bool operator==(std::nullptr_t np, const SharedPtr<T> & p){
      return false;
    }

  template <typename T1, typename T2>
    bool operator!=(const SharedPtr<T1>& p1, const SharedPtr<T2> & p2){
      return false;
    }

  template <typename T>
    bool operator!=(const SharedPtr<T> &, std::nullptr_t){
      return false;
    }
  template <typename T>
    bool operator!=(std::nullptr_t, const SharedPtr<T> &){
      return false;
    }  

  template <typename T, typename U>
    SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp){

    }

  template <typename T, typename U>
    SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp){

    }




}

#endif //S_PTR_HPP
