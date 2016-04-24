CXX= clang++
CXXFLAGS= -std=c++11 -pthread -Wall -Wextra -pedantic -g


all: Test

Test: Test.o
	$(CXX) $(CXXFLAGS) -o Test Test.o

Test.o: Test.cpp SharedPtr.hpp
	$(CXX) $(CXXFLAGS) -c Test.cpp
  
clean: 
	rm -rf *.o *.gch Test
