#Project 1
David Skoda
CS 440

To compile:
clang++ -g -std=c++11 -Wall -Wextra -pedantic test.cpp -ldl -O -o test
g++ also works.

Status of project:

All the test code passes.
No memory leaks (besides suppressed leaks from test code).

Deque.hpp is the minified version of intDeque.hpp, plus the changes resulting in making it a macro. I have provided intDeque.hpp so you can see comments and reasoning behind the code, as I removed all the comments for the submission file (Deqe.hpp). intDeque.hpp works with intTest.cpp. Some of the arguments were changed from the pre-post macro version, so in Deque.hpp some arguments are references, whereas in intDeque theyre not. 
