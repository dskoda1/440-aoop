#include "SharedPtr.hpp"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <vector>
#include <functional>

using namespace std;
using namespace cs540;





class Test {

  public: 
    string name;
    vector<string> * titles;
    vector<function<void()>> * tests;

    
    Test(string nameIn): name{nameIn}{
      titles = new vector<string>;
      tests = new vector<function<void()>>;
    }

    void addTest(string titleIn, std::function<void()> func){
       titles->push_back(titleIn);
       tests->push_back(func);
    }

    void verifyTests(){
      cout << "\n\n\t-------------------" << endl;

      cout << "\t** " << name << endl;
      for(auto i = 0; i < titles->size(); ++i){
        cout << "\t-------------------" << endl;
        cout << "\t**** " << titles->at(i) << endl;
        //cout << "**** ";
        tests->at(i)();
        //cout << endl;
        cout << "\t**** \u2713" << endl;

      }
        
      cout << "\n\t-------------------\n\n" << endl;
      

    }


};


int main(int argc, char** argv){

  Test t("cs540::SharedPtr");

  t.addTest("Constructor should expose a null refcount obj", []() {
    SharedPtr<int> sp;
    assert(sp.refCounter == nullptr);
  });

  t.addTest("Refcount object should be initialized to 1 by default", [](){
    SharedPtr<int> sp(new int(5));
    assert(sp.refCounter->getRefCount() == 1);    
  }); 

  t.addTest("Refcount should increase after copy constructing", [](){
    SharedPtr<int> sp(new int(5));
    assert(sp.refCounter->getRefCount() == 1);

    SharedPtr<int> sp2(sp);
    assert(sp.refCounter->getRefCount() == 2);
    assert(sp2.refCounter->getRefCount() == 2);
  });

  t.addTest("Refcount shouldn't increase if copy constructor given null.", [](){
    SharedPtr<int> nullSp;
    

    SharedPtr<int> sp;
    assert(sp.refCounter == nullptr);

    SharedPtr<int> sp1(sp);
    assert(sp1.refCounter == nullptr);

    ;
    

  });
  t.verifyTests();
}













