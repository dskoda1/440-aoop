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



class Base1 {
  protected:
    Base1() : derived_destructor_called(false) {
      printf("Base1::Base1()\n");
    }
  private:
    Base1(const Base1 &); // Disallow.
    Base1 &operator=(const Base1 &); // Disallow.
  protected:
    ~Base1() {
      printf("Base1::~Base1()\n");
      assert(derived_destructor_called);
    }
  protected:
    bool derived_destructor_called;
};

class Derived : public Base1 {
  friend void basic_tests_1();
  public:
  Derived() {}
  Derived(const Derived &); // Disallow.
  Derived &operator=(const Derived &); // Disallow.
  public:
  ~Derived() {
    printf("Derived::~Derived()\n");
    derived_destructor_called = true;
  }
  int value;
};




class Test {

  public: 
    string name;
    vector<string> * titles;
    vector<function<void()>> * tests;


    Test(string nameIn): name{nameIn}{
      titles = new vector<string>;
      tests = new vector<function<void()>>;
    }
    ~Test(){
      delete titles;
      delete tests;
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
        tests->at(i)();
        cout << "\t**** \u2713" << endl;

      }

      cout << "\n\t-------------------\n\n" << endl;


    }


};


int main(int argc, char** argv){

  Test t("cs540::SharedPtr");

  t.addTest("test copy constructor", [](){

      SharedPtr<Base1> sp(new Derived);
      {
        // Test copy constructor.
        SharedPtr<Base1> sp2(sp);
      }
   });


  t.addTest("Copy construct a base from a derived.", [](){
      SharedPtr<Base1> sp2;
      {
        SharedPtr<Derived> sp(new Derived);
        // Test template copy constructor.
        SharedPtr<Base1> sp3(sp);
        
        sp2 = sp;
        sp2 = sp2;
      }
  });

/*
  t.addTest("test copy constructor and template copy cons.", [](){
      {
        SharedPtr<Derived> sp(new Derived);
        SharedPtr<Derived> sp2(sp);
      }
      {
        SharedPtr<Derived> sp(new Derived);
        SharedPtr<Base1> sp2(sp);
      }
  });
  t.addTest("test assignment operator", [](){
      {
        SharedPtr<Derived> sp(new Derived);
        SharedPtr<Derived> sp2;
        sp2 = sp;
        sp = sp; // Self assignment.
      }
  });

  t.addTest("test template assignment operator", [](){
      {
        SharedPtr<Derived> sp(new Derived);
        SharedPtr<Base1> sp2;
        sp2 = sp;
        sp2 = sp2; // Self assignment.
        sp2 = sp;
        sp = sp;
      }
  });
*/
  /*

     t.addTest("Test copy constructor and *", [](){
     SharedPtr<Derived> sp(new Derived);
     (*sp).value = 1234;
     cout << (*sp).value << endl;
     SharedPtr<const Derived> sp2(sp);
     cout << (*sp2).value << endl;
     int i = (*sp2).value;
     assert(i == 1234);


     });



   */


  // (*sp2).value = 567; // Should give a syntax error if uncommented.

  /*
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
   */

  t.verifyTests();
}











