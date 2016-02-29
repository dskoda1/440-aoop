#include <iostream>
#include <string.h>
#include <assert.h>
#include "Map.hpp"
#include <vector>

using namespace std;
int main(int argc, char** argv){

	cs540::Map<int, int> * m = new cs540::Map<int, int>();
	srand(time(NULL));
	vector<int> * vec = new vector<int>();
	for(int i = 0; i <10; ++i){
		auto pair = make_pair(i, rand());
		auto iter = m->insert(pair);
		vec->push_back(i);
		//cout << iter.first << endl;	
		//cout << --(m->end()) << endl;
	}



	for(auto it = --(m->end()); it != m->begin(); --it){
		auto val = *it;
//		cout << val.first << ": " << val.second << endl;
	}


	/*
		 auto it = m.find(4800);
		 if(it != m.end()){
		 cout << it.first << ", " << it.second << endl;
		 }else{
		 cout << "Returned end" << endl;
		 }
	 */
	/*	
			for(auto it = m.begin(); it != m.end(); ++it)
			{
			}	
	 */
	return 0;
}
