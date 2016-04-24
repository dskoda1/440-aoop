#ifndef SMART_PTR
#define SMART_PTR

#include <iostream>
namespace cs540{

  template <class Obj> class SmartPtr{

    public: 
      SmartPtr(): data{nullptr}, refCount{nullptr}{

      } 

      SmartPtr(Obj * objIn): data{objIn}, refCount{new int(1)}{
      }

      SmartPtr(const SmartPtr & sp): data{sp.data}, refCount{sp.refCount}{
        
        (*refCount)++;
      }

      ~SmartPtr(){
        if((*refCount) == 1){
          delete data;
          delete refCount;
        }
        else{
          --(*refCount);
        }
      }

    private:
      Obj * data;
      int * refCount;
  };
}



#endif //SMART_PTR
