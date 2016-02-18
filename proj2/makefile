CXX= clang++
CXXFLAGS= -std=c++11 -Wall -Wextra -pedantic -g

all: Test
	

Test: Test.o
	

Test.o: Test.cpp Map.hpp
	$(CXX) $(CXXFLAGS) Test.cpp Map.hpp
	
clean:
	 rm -rf *.gch Test
