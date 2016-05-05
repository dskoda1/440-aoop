#ifndef S_PTR_HPP
#define S_PTR_HPP

//Includes
#include <cstddef>
#include <iostream>
#include <assert.h>
namespace cs540{

  template <typename T> class SharedPtr{
    private:

      class refDataA{
        public:
          T * staticData;
          int refCount;
          refDataA() : refCount{1}{}
          refDataA(T * dataIn): refCount{1}, staticData{dataIn}{}
          virtual void destroy() = 0;
          virtual ~refDataA(){}
          void inc(){
            ++refCount;
          }
          void dec(){
            --refCount;
          }
      };

      template <typename U>
        class refData : public refDataA{
          public:
            U * runtimeData; 
            refData(U * dataIn) :
              refDataA{static_cast<T*>(dataIn)}, 
              runtimeData{dataIn}{}
            virtual void destroy(){
              delete runtimeData; 
            }
            ~refData(){}
        };
    public:

      refDataA * refCounter;
      T * data;
      /* Constructor */
      SharedPtr() : refCounter{}{
        std::cout << "in the default constructor" << std::endl; 
      }

      /* Explicit Constructor */
      template <typename U> 
        explicit SharedPtr(U * dataIn)
      {
        if(dataIn != nullptr)
          refCounter = new refData<U>{dataIn};
        std::cout << "in the explicit constructor" << std::endl;
      }

      /*
       * Copy Constructor
       * Increment the count by one.
       */
      SharedPtr(const SharedPtr &p)
      {
        std::cout << "in the copy constructor" << std::endl;
        
        if(p.refCounter != nullptr && p.refCounter->staticData != nullptr){
          refCounter = p.refCounter;
          refCounter->inc();
        }else{
          std::cout << "Dropping out of school" << std::endl;
        } 
      }

      template <typename U>
        SharedPtr(const SharedPtr<U> & p){
          std::cout << "In template copy constructor " << std::endl;
          if(p.refCounter != nullptr && p.refCounter->staticData != nullptr){
            //refCounter = p.refCounter;
            refCounter = static_cast<const SharedPtr<const T> &>(p).refCounter;
            refCounter->inc();
          }else{
           std::cout << "in template construcotr failed nullptr check" << std::endl; 
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
        //TODO: check if already pointing to something and handle
        if(&p != this){
          this->refCounter = p.refCounter;
          this->refCounter->refCount++;   
        }else{
          std::cout << "Detected self assignment in non derived op" << std::endl;
        }
        return *this;
      }

      template <typename U>
        SharedPtr<T> & operator = (const SharedPtr<U> & p)
        {
          //TODO: Check if currently pointing to something or not
          //Check that p refCount != null
          //Check for self assignment
          if(*this != static_cast<const SharedPtr<T> &>(p)){
            refCounter = static_cast<const SharedPtr<T> &>(p).refCounter;
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
        //return refCounter->data;
      }

      T & operator * () const {
        return *(refCounter->staticData);
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
