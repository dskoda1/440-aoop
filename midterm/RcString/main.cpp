#include "RCString.hpp"
#include <iostream>
int
main() {
    using cs540::RCString;

    RCString s1; // Initialize to "".
    // After the below, s2 and s1 should point to the same data object.
    RCString s2(s1);

    RCString s3;
    s3 = s1; // After this, also point to same data object.

    RCString s4("hello");

    RCString s5(std::string("hello"));

    // Output.
    std::cout << s5 << std::endl;

    // Concatentation.
    {
        RCString s1("hello ");
        RCString s2("goodbye");
        RCString s3(s1 + s2); // Invoke move ctor.
        std::cout << s3 << std::endl;

        RCString s4;
        s4 = s3 + " forever."; // Move assignment.
        std::cout << s4 << std::endl;
    }

}
