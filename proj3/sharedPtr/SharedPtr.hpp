#ifndef S_PTR_HPP
#define S_PTR_HPP

//Includes
#include <cstddef>
#include <atomic>
#include <mutex>
#include <assert.h>
namespace cs540{

  class refDataA{
    public:
      std::mutex countLock;
      int refCount;
      refDataA() : refCount{1}{}
      virtual ~refDataA(){}
      int getCount(){
        return refCount;
      }
  
      void inc(){
        countLock.lock(); 
        ++refCount;
        countLock.unlock();
      }
      void dec(){
        countLock.lock();
        --refCount;
        countLock.unlock();
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
      }

      /*
       * Copy Constructor
       * Increment the count by one.
       */
      SharedPtr(const SharedPtr &p)
      {
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
      SharedPtr(SharedPtr && p){
        refCounter = p.refCounter;
        data = p.data;
        //Now set p to null
        p.refCounter = nullptr;
        p.data = nullptr;
      }

      template <typename U>
        SharedPtr(SharedPtr<U> && p){
          if(p.data == nullptr){
            refCounter = nullptr;
            data = nullptr;
          }else{
            data = static_cast<T*>(p.data);
            refCounter = p.refCounter;
            p.data = nullptr;
            p.refCounter = nullptr;
          }
        }

      /*
       * Copy assignment operator.
       * Must be able to handle self assignment.
       */
      SharedPtr & operator = (const SharedPtr & p) 
      {
        if(&p != this){
          reset();
          data = p.data;
          refCounter = p.refCounter;
          if(refCounter != nullptr){
            refCounter->inc();
            //++(refCounter->refCount);
          }
        }
        return *this;
      }

      template <typename U>
        SharedPtr<T> & operator = (const SharedPtr<U> & p)
        {
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
      SharedPtr & operator = (SharedPtr && p){
        refCounter = p.refCounter;
        data = p.data;
        p.refCounter = nullptr;
        p.data = nullptr;
        return *this;
      }

      template <typename U>
        SharedPtr<T> & operator = (SharedPtr<U> && p){
        if(p.data == nullptr){
          data = nullptr;
          refCounter = nullptr;
        }else{
          data = static_cast<T*>(p.data);
          refCounter = p.refCounter; 
        }

        p.data = nullptr;
        p.refCounter = nullptr;
      }  

      /* Destructor */
      ~SharedPtr(){
        if(refCounter != nullptr){
          refCounter->dec();
          if(refCounter->getCount() == 0){
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
          if(refCounter->getCount() == 0){
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
      return (p1.data == p2.data);
    }

  template <typename T>
    bool operator==(const SharedPtr<T> & p, std::nullptr_t np){
      return (p.data == np);
    }

  template <typename T>
    bool operator==(std::nullptr_t np, const SharedPtr<T> & p){
      return (np == p.data);
    }

  template <typename T1, typename T2>
    bool operator!=(const SharedPtr<T1>& p1, const SharedPtr<T2> & p2){
      return !(p1 == p2);
    }

  template <typename T>
    bool operator!=(const SharedPtr<T> & p, std::nullptr_t np){
      return !(p == np);
    }
  template <typename T>
    bool operator!=(std::nullptr_t np, const SharedPtr<T> & p){
      return !(np == p);
    }  

  template <typename T, typename U>
    SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp){
      return SharedPtr<T>(sp);      
    }

  template <typename T, typename U>
    SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp){
      SharedPtr<T> ret;
      if(sp.data == nullptr){
        ret.refCounter = nullptr;
        ret.data = nullptr;
      }else{
        ret.data = dynamic_cast<T*>(sp.data);
        ret.refCounter = sp.refCounter;
        ret.refCounter->inc();
        //++(ret.refCounter->refCount);
      }
      return ret;

    }




}

#endif //S_PTR_HPP
