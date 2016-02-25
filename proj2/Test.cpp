#include <iostream>
#include <string.h>
#include <assert.h>
#include "Map.hpp"


using namespace std;
int main(int argc, char** argv){

	cs540::Map<int, int> m;
	srand(time(NULL));
	for(int i = 0; i <5; i++){
		int k = rand();
		auto pair = make_pair(k, k);
		m.insert(pair);

	}

	for(auto it = m.begin(); it != m.end(); it++)
	{

	}
		

	return 0;
}
