#include <iostream>
#include <string.h>
#include <assert.h>
#include "Map.hpp"
#include <vector>

using namespace std;
struct Person {
	friend bool operator<(const Person &p1, const Person &p2) {
		return p1.name < p2.name;
	}
	friend bool operator==(const Person &p1, const Person &p2) {
		return p1.name == p2.name;
	}
	Person(const char *n) : name(n) {}
	void print() const {
		printf("Name: %s\n", name.c_str());
	}
	const std::string name;
	Person &operator=(const Person &) = delete;
};

int main(){

	cs540::Map<const Person, int> m; 
	srand(time(NULL));
	Person p1("Jane");
	Person p2("John");
	Person p3("Mary");
	Person p4("Dave");
	Person none("Jim");
	m.insert(make_pair(p1, 1));
	m.insert(make_pair(p2, 2));
	m.insert(make_pair(p3, 3));
	auto davePair = make_pair(p4, 4);
	m.insert(davePair);



	for(auto it = m.begin(); it != m.end(); ++it){
		cout << (*it).first.name << endl;
	}

	for(auto it = m.rbegin(); it != m.rend(); ++it){
		cout << (*it).first.name << endl;


	}


/*	for(auto it = m.begin(); it != m.end(); ++it){
		cout << (*it).first.name << endl;
	}

	auto it1 = m.begin();
	auto it2 = m.end();
	it1++; // Second node now.
	it1++; // Third node now.
	it2--; // Fourth node now.
	cout << "Expecting john, it1: " << (*it1).first.name << endl;	
	cout << "Expecting mary, it2: " << (*it2).first.name << endl;	
	it2--; // Third node now.
	cout << "Expecting john, it2: " << (*it2).first.name << endl;	
	assert(it1 == it2);
	it2--; // Second node now.
	cout << "Expecting jane, it2: " << (*it2).first.name << endl;	
	it2--; // First node now.
	cout << "Expecting dave, it2: " << (*it2).first.name << endl;	
	assert(m.begin() == it2);
for(int i = 0; i < 10; i++){

		auto pair = make_pair(i, rand());
		auto iter = m.insert(pair);
		cout << iter.first << endl;
		}
		const cs540::Map<const int, int> copy(m);	
		auto it = copy.find(3);
		cout << it << endl;
		for(int i = 0; i <10000; ++i){
		auto pair = make_pair(i, rand());
		m->insert(pair);
		}
		auto first = make_pair(1, rand());
		auto second = make_pair(1, rand());

		auto one = m->insert(first);
		auto two = m->insert(second);



		for(auto it =m->begin(); it != m->end(); it++){
		auto val = *it;
		cout << val.first << ": " << val.second << endl;
		}

		for(auto it =m->begin(); it != m->end(); ++it){
		auto val = *it;
		cout << val.first << ": " << val.second << endl;
		}




		auto it = m->find(4800);
		if(it != m->end()){
		cout << it.first << ", " << it.second << endl;
		}else{
		cout << "Returned end" << endl;
		}
	 */

	return 0;
}
