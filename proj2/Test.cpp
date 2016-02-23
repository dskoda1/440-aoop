#include <iostream>
#include <string.h>
#include <assert.h>
#include "Map.hpp"


using namespace std;
int main(int argc, char** argv){

	cs540::Map<int, int> m;
	for(int i = 0; i < 20; i++){
		m.insert(make_pair(i, i));

	}
	


	return 0;
}
