#include <iostream>
#include <string.h>
#include <assert.h>
#include "Map.hpp"
#include <vector>

using namespace std;
int main(){

	cs540::Map<int, int> * m = new cs540::Map<int, int>();
	srand(time(NULL));


	for(int i = 0; i < 20; i++){

			auto pair = make_pair((i%10), rand());
			auto iter = m->insert(pair);
			cout << iter.first << endl;
			cout << iter.second << endl;


	}






	/*Vfor(int i = 0; i <1000; ++i){
		auto pair = make_pair(i, rand());
		m->insert(pair);
	}*/
		/*auto first = make_pair(1, rand());
		auto second = make_pair(1, rand());

		auto one = m->insert(first);
		auto two = m->insert(second);
		
		cout << two.second << endl;	
		int i = 0;
		int y = i++;
		int z = i + y;
		cout << z << endl;
*/
	/*
	for(auto it =m->begin(); it != m->end(); it++){
		auto val = *it;
		cout << val.first << ": " << val.second << endl;
	}

	for(auto it =m->begin(); it != m->end(); ++it){
		auto val = *it;
		cout << val.first << ": " << val.second << endl;
	}
*/


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
