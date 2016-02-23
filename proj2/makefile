CXX= clang++
CXXFLAGS= -std=c++11 -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-return-type -g



all: Test
	

Test: Test.o
	$(CXX) $(CXXFLAGS) -o Test Test.o

Test.o: Test.cpp Map.hpp
	$(CXX) $(CXXFLAGS) -c Test.cpp
	
clean:
	 rm -rf *.o *.gch Test
