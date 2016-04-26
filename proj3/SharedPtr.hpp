#ifndef S_PTR_HPP
#define S_PTR_HPP

//Includes
#include <cstddef>
#include <iostream>
#include <assert.h>
namespace cs540{

  template <typename T> class SharedPtr{
    private:

    public:

      class refData{

        friend class SharedPtr;
        public:
        refData(T *dataIn, int countIn=0): data{dataIn}, refCount{countIn}{}
        int getRefCount(){ return refCount; };

        /*refData & operator ++ (){
          ++refCount;
          return *(this);
          }
          refData operator ++(int){
          refData old( * this);
          ++refCount;
          return old;
          }*/
        private:
        T * data;
        int refCount;

      };

      refData * refCounter;




      /* Constructor */
      SharedPtr(){
        std::cout << "in the default constructor" << std::endl; 
        refCounter = nullptr; 
      }

      /* Explicit Constructor */
      template <typename U> 
        explicit SharedPtr(U * dataIn){
          std::cout << "in the explicit constructor" << std::endl;
          refCounter = new refData(dataIn, 1);
        }

      /*
       * Copy Constructor
       * Increment the count by one.
       */
      SharedPtr(const SharedPtr &p){
        std::cout << "in the copy constructor" << std::endl;
        if(p.refCounter != NULL){
          refCounter = p.refCounter;
          ++refCounter->refCount;
        }else{
          refCounter = nullptr;
        }
      }

      template <typename U>
        SharedPtr(const SharedPtr<U> & p){
          assert(false);
        }

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

      T * get() const {
        return refCounter->data;
      }

      T & operator * () const {
      }

      T * operator -> () const {}

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
