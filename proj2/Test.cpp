#include <iostream>
#include <string.h>
#include <assert.h>
#include "Map.hpp"


using namespace std;
int main(int argc, char** argv){

	cs540::Map<int, int> m;
	for(int i = 20; i > 0; i--){
		auto pair = make_pair(i, i);
		m.insert(pair);

	}


	return 0;
}
