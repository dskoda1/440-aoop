#include "Map.hpp"


#include <iostream>
using namespace std;
int main(){

	cs540::Map<int, int> * m = new cs540::Map<int, int>();

	//cs540::Map<int, int>::Iterator i = m->begin();
	using Iterator = typename cs540::Map<int, int>::Iterator;
	Iterator i = m->begin();
}
