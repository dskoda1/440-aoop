/*
 * Consider the push_back() member function of a vector class based on
 * std::vector.  Make it exception-safe and exception-neutral.  This code will
 * not run, but will compile (use -c).
 *
 * Exception-safe means that if an exception is thrown, the container is not in
 * an inconsistent state, and is unchanged as much as possible.
 *
 * Exception-neutral means that exceptions of application-level types are
 * propagated up so that the application can handle them.
 */

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <exception>
// Leave the class definition unchanged.
template <typename T>
class Vector {
    public:
        Vector() : size(0) {}
        // Other stuff here.
        void push_back(const T &);
    private:
        // Capacity is fixed to 100.
        T array[100];
        std::size_t size;
};

// You only need to modify the body of this function.  You may consider
// exceeding the capacity to be undefined behavior.  (Hint: You need to delete
// code also.)
template <typename T>
void
Vector<T>::push_back(const T &v) {
    try {
        array[size] = v;
    } catch (std::exception& e){
        std::cerr << "User object threw while adding to vector." << std::endl;
        std::cerr << e.what() << std::endl;
        throw e;
    }
    size++;
}

// Example of usage.
void
foo(Vector<std::string> &v) {
    v.push_back("hello");
}
