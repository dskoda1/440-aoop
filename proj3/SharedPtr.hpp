#ifndef S_PTR_HPP
#define S_PTR_HPP

//Includes
#include <cstddef>
#include <iostream>
#include <assert.h>
namespace cs540{

  class refDataA{
    public:
      int refCount;
      refDataA() : refCount{1}{}
      virtual ~refDataA(){}
      void inc(){
        ++refCount;
      }
      void dec(){
        refCount--;
      }
  };

  template <typename U>
    class refData : public refDataA{
      public:
        U * runtimeData; 
        refData() : runtimeData{nullptr}{}
        refData(U * dataIn) :
          runtimeData{dataIn}{}
        ~refData(){
          delete runtimeData;
        }
    };


  template <typename T> class SharedPtr{
    private:

    public:

      refDataA * refCounter;
      T * data;
      /* Constructor */
      SharedPtr() : refCounter{nullptr}, data{nullptr}{
        std::cout << "in the default constructor" << std::endl; 
      }

      /* Explicit Constructor */
      template <typename U> 
        explicit SharedPtr(U * dataIn) : refCounter{nullptr}, data{nullptr}
      {

        if(dataIn != nullptr)
        {
          data = static_cast<T*>(dataIn);
          refCounter = new refData<U>{dataIn};
        }

        std::cout << "in the explicit constructor" << std::endl;
      }

      /*
       * Copy Constructor
       * Increment the count by one.
       */
      SharedPtr(const SharedPtr &p)
      {
        std::cout << "in regular copy constructor" << std::endl;
        if(p.data == nullptr){
          refCounter = nullptr;
          data = nullptr;
        }else{
          data = p.data;
          refCounter = p.refCounter;
          refCounter->inc();
        }
      }

      template <typename U>
        SharedPtr(const SharedPtr<U> & p){

          if(p.data == nullptr){
            refCounter = nullptr;
            data = nullptr;
          }else{
            data = static_cast<T*>(p.data);
            refCounter = p.refCounter;
            refCounter->inc(); 
         }
        } 

      /*
       * Move constructor
       * The reference count remains unchanged.
       */
      SharedPtr(const SharedPtr && p){
        //TODO
      }

      template <typename U>
        SharedPtr(const SharedPtr<U> && p){
          //TODO
        }

      /*
       * Copy assignment operator.
       * Must be able to handle self assignment.
       */
      SharedPtr & operator = (const SharedPtr & p) 
      {
        if(&p != this){
          data = p.data;
          refCounter = p.refCounter;
          refCounter->inc();
        }
        return *this;
      }

      template <typename U>
        SharedPtr<T> & operator = (const SharedPtr<U> & p)
        {
          std::cout << "In template assignment op" << std::endl;
          //Already pointing to something
          reset();
          if(p.refCounter != nullptr){
            data = static_cast<T*>(p.data);
            refCounter = p.refCounter;
            refCounter->inc();
          }

          return *this; 
        }

      /*
       * Move assignment operator.
       */
      SharedPtr & operator = (SharedPtr && p){}

      template <typename U>
        SharedPtr<T> & operator = (SharedPtr<U> && p){}  

      /* Destructor */
      ~SharedPtr(){
        if(refCounter != nullptr){
          refCounter->dec();
          if(refCounter->refCount == 0){
            delete refCounter;
            refCounter = nullptr;
          }
        }
      }

      /*********************
       * Modifiers
       *********************/


      /* Reset the pointer. */
      void reset(){
        if(refCounter != nullptr){
          refCounter->dec();
          if(refCounter->refCount == 0){
            delete refCounter;
          }
        }
        data = nullptr;
        refCounter = nullptr;
      };

      /* Replace the pointer with another pointer. */
      template <typename U>
        void reset(U * p){
        reset();
        data = static_cast<T *>(p);
        refCounter = new refData<U>(p);

      }


      /*********************
       * Observers 
       *********************/

      T * get() const {
        return data;
      }

      T & operator * () const {
        
        return *(data);
      }

      T * operator -> () const {
        return data;   
      }

      explicit operator bool() const{
        return (data != nullptr);
      }

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
