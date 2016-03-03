CXX= clang++
CXXFLAGS= -std=c++11 -O -Wall -Wextra -pedantic -ldl -g

all: Test

Test: Test.o
	$(CXX) $(CXXFLAGS) -o Test Test.o

Test.o: Test.cpp Map.hpp
	$(CXX) $(CXXFLAGS) -c Test.cpp
	
clean:
	 rm -rf *.o *.gch Test
