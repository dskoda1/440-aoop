XX= clang++
CXXFLAGS= -Wfatal-errors -std=c++1z -pthread -Wall -Wextra -pedantic -g 


all: Test

Test: Test.o
	$(CXX) $(CXXFLAGS) -o test Test.o

Test.o: Test.cpp Interpolate.hpp 
	$(CXX) $(CXXFLAGS) -c Test.cpp
  
clean: 
	rm -rf *.o *.gch test
