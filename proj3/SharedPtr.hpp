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
        int refCount;
        refDataA() : refCount{1}{}
        virtual void destroy() = 0;
        virtual ~refDataA(){}

      };

      template <typename U>
      class refData : public refDataA{
        public:
          U * data;
          //del d;
          //refData(U * dataIn, del dIn) : data{dataIn}, d{dIn} {}
          refData(U * dataIn) : data{dataIn} {}
          virtual void destroy(){
            delete data;
          }
          ~refData(){}
      };
      /*
      template<class U>
      struct virtualDtor{
        void operator()(U * data) const {
          delete data;
        }
      };*/

    public:

      refDataA * refCounter;
      T * data;



      /* Constructor */
      SharedPtr() : refCounter{}, data{}{
        std::cout << "in the default constructor" << std::endl; 
      }

      /* Explicit Constructor */
      template <typename U> 
        explicit SharedPtr(U * dataIn) : 
          refCounter{new refData<U>(dataIn)},
          data{dataIn} 
        {
          std::cout << "in the explicit constructor" << std::endl;
        }

      /*
       * Copy Constructor
       * Increment the count by one.
       */
      SharedPtr(const SharedPtr &p) : refCounter{p.refCounter}, data{p.data}{
        std::cout << "in the copy constructor" << std::endl;
        refCounter->refCount++;
      }

      template <typename U>
        SharedPtr(const SharedPtr<U> & p){
          //TODO 
          this->data = p.data;
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
      SharedPtr & operator = (const SharedPtr & p) 
      {
        refCounter = p.refCounter;
        data = p.data;
        refCounter->refCount++;
        return (*this);
  
      }

      template <typename U>
        SharedPtr<T> & operator = (const SharedPtr<U> & p)
      {
        refCounter = dynamic_cast<refDataA*>(p.refCounter);
        data = p.data;
        refCounter->refCount++;
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
