David Skoda
B00400675

For erasure.cpp:
clang++ -std=c++14 erasure.cpp
(I use c++14 features!)

There are no memory leaks with valgrind when I ran it.


For exception.cpp, my changes were:
1. Moved size++ to the end of the function, so that it only runs that
code if the object was inserted with no throws. 
2. I changed the insert to use size instead of size - 1, to account for
the first change. I also updated the error message along with printed the 
exception specific message.
3. To meet the exception neutral requirement, I rethrow the exception.
I realize I couldv'e just taken out the entire try catch block but I
think printing a useful error message along with the exceptions message
is more valuable to the user.
