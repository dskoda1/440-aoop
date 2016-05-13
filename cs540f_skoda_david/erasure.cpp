#include <iostream>
#include <vector>
#include <typeinfo>
// Put your code here.
class Val {

  public:
    virtual ~Val(){}
    virtual void get(std::ostream & os){}  
};

template <typename T>
class internalDataT : public Val{
  public:
    T * data;
    internalDataT(T * dataIn): data{dataIn}{}
    void get(std::ostream & os){
      os << *data;
    }
    ~internalDataT(){ delete data; }
};


/* Helper function that begins the process of unpacking
 */
template <typename ... Ts>
auto helper(Ts ... args){
  std::vector <Val *> ret;  
  unpacker(ret, args...);
  return ret;
}


template <typename T, typename ... Ts>
auto unpacker(std::vector<Val *> & vec, T t, Ts... rest){
  vec.push_back(new internalDataT<T>(new T{t}));
  return unpacker(vec, rest...);
}

template <typename T>
void unpacker(std::vector<Val *> & vec, T t){
  vec.push_back(new internalDataT<T>(new T{t}));
  return;
}



// Do not modify this class.
struct A {
  friend std::ostream &operator<<(std::ostream &, const A &);
  public:
  A(int i) : ptr{new int{i}} {}
  A(const A &tt) : ptr(new int{*tt.ptr}) {}
  ~A() { delete ptr; }
  A &operator=(const A &) = delete;
  private:
  int *ptr;
};

// Do not modify this function.
std::ostream &
operator<<(std::ostream &os, const A &a) {
  return os << *a.ptr;
}

std::ostream &
operator <<(std::ostream &os, const std::vector<Val *> vec){

  os << "[ ";
  for(Val * v: vec){
    v->get(os);
    os << ", "; 
  } 
  os << " ]";

  return os;
}


/*
 * This returns a vector of pointers to objects that have the given value
 * "hidden" inside of them.  Arguments to this function should be saved by
 * value, and are guaranteed to have copy constructors, but not assignment
 * operators.
 */
template <typename... Ts>
std::vector<Val *> erase_type(Ts... params) {
  return helper(params...);
}

int main() {

  std::vector<Val *> v = erase_type(1, 3.14, std::string("hello"), A(1234));
  // The below should print out one line:
  // [1, 3.14, hello, 1234]
  std::cerr << v << std::endl;

  // Free.
  for (auto e : v) {
    delete e;
  }
}
