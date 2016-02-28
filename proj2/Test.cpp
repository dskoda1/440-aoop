#include <iostream>
#include <string.h>
#include <assert.h>
#include "Map.hpp"


using namespace std;
int main(int argc, char** argv){

	cs540::Map<int, int> m;
	srand(time(NULL));
	for(int i = 0; i <6; i++){
		int k = rand();
		auto pair = make_pair(i, k);
		auto insertPair = m.insert(pair);
		auto it = insertPair.first;
		cout << "Iterator: " << it.first << ", " << it.second << endl;
		//cout << insertPair.second << endl << endl; 	
	}

		auto it = m.find(7);
		if(it != m.end()){
			cout << it.first << ", " << it.second << endl;
		}else{
			cout << "Returned end" << endl;
		}

/*	
	for(auto it = m.begin(); it != m.end(); ++it)
	{
		auto val = *it;
		cout << val.first << ": " << val.second << endl;
	}	
*/
	return 0;
}
