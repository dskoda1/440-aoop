David Skoda
dskoda1@binghamton.edu
B-00400675

What works:
I believe I have tested all of the methods inside of my Map class
and that they are error free.

Scale:
Using Test-kec and the -i option, my code works up to ~125k Iterations.
I was unable to find the cause of why it fails around there.

Test-scaling worked for all the cases, and on genie.cs.binghamton.edu 
server the big iteration test completed; It maxed out at ~50gb of RAM.

Extra Credit:
Inside of test-scaling.cpp (included in the tarball) I have included an
extra test near the bottom. It runs a templated function similar in format
to all of the other scaling tests. I have two find(key) functions for my map;
find, and slowFind. The former demonstrates locality in searches, and my test
case demonstrates how much faster the find function than the latter which
does not use locality for finds.

TO RUN:
I have included the file which has my locality test called my-test-scaling.cpp.
My makefile is configured to compile any file called Test.cpp with my Map.hpp.
So change the name of the test file youd like to compile with to Test.cpp and 
call make on it.

