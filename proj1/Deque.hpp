#ifndef DEQUE_HPP
#define DEQUE_HPP


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define Deque_DEFINE(T) Deque_int d;


struct Deque_int_Iterator{

	int (*deref)(Deque_int_Iterator *);
	void (*inc)(Deque_int_Iterator *);
	void (*dec)(Deque_int_Iterator *);
};

//Dereference the iterator at its location
int Deque_int_Iterator_deref(Deque_int_Iterator * di)
{
	return 1;
}

bool Deque_int_Iterator_equal(Deque_int_Iterator d1, Deque_int_Iterator d2)
{
	return true;
}

struct Deque_int{

	//Length
	int (*size)(Deque_int *);
	int length;
	//Check if empty
	bool (*empty)(Deque_int *);
	//Identifier of struct name
	char * type_name;

	//Data entry methods
	//Push a value onto the back of the deque
	void (*push_back)(Deque_int *, int);
	//push a value into the front of the deque
	void (*push_front)(Deque_int *, int);

	//Getter methods
	int (*front)(Deque_int *);
	int (*back)(Deque_int *);
	int (*at)(Deque_int *, int);

	//Remove data methods
	void (*pop_back)(Deque_int *);
	void (*pop_front)(Deque_int *);
	void (*clear)(Deque_int *);

	//Destructor
	void (*dtor)(Deque_int *);
	
	//Iterator methods
	Deque_int_Iterator (*begin)(Deque_int *);
	Deque_int_Iterator (*end)(Deque_int *);


};


bool  Deque_int_equal(Deque_int d1, Deque_int d2)
{
	return false;
}
/*
 *	Housekeeping methods
 *	Size, empty
 */
//return the deques length
int Deque_int_size(Deque_int * d)
{
	return d->length;
}
//Return whether or not it's empty
bool Deque_int_empty(Deque_int * d)
{
	if(d->size > 0) return false;
	else return true;	

}

/*
 *	Data entry methods
 *	push_back, push_front
 */
//Push a value onto the back of the deque
void Deque_int_push_back(Deque_int *d, int val)
{
}
//Push a value onto the front of the deque
void Deque_int_push_front(Deque_int *d, int val)
{
}

/*
 * Getter methods
 * front, back, at
 */
//Get the value at the front
int Deque_int_front(Deque_int *d)
{
	return 0;
}
//Get the value in the back
int Deque_int_back(Deque_int *d)
{
	return 0;
}
//Get the value at the index
int Deque_int_at(Deque_int *d, int val)
{	
	return 0;
}

/*
 * Data removal methods
 *	pop_front, pop_back
 */
//Pop a value off the front
void Deque_int_pop_front(Deque_int *d)
{
}
//Pop a value off the back
void Deque_int_pop_back(Deque_int *d)
{
}
//Remove all values
void Deque_int_clear(Deque_int *d)
{
}

//Iterator methods
Deque_int_Iterator Deque_int_begin(Deque_int * d)
{
	Deque_int_Iterator di;
	return di;
}
Deque_int_Iterator Deque_int_end(Deque_int * d)
{
	Deque_int_Iterator di;
	return di;
}

//Destructor
void Deque_int_dtor(Deque_int * d)
{
}

void Deque_int_ctor(Deque_int * d, bool (*f)(const int&, const int&))
{
	//Initialize the members here
	d->size = &Deque_int_size;
	d->empty = &Deque_int_empty;
	//Type_name identifier for struct
	const char * type = "Deque_int";
	d->type_name = strdup(type);
	//memcpy(d->type_name, type, strlen(type)+1); 

	//Pushing functions
	d->push_back = &Deque_int_push_back;
	d->push_front = &Deque_int_push_front;

	//Getter functions
	d->front = &Deque_int_front;
	d->back = &Deque_int_back;
	d->at = &Deque_int_at;

	//Pop functions
	d->pop_back = &Deque_int_pop_back;
	d->pop_front = &Deque_int_pop_front;
	d->clear = &Deque_int_clear;	

	//Iterator methods
	d->begin = &Deque_int_begin;
	d->end = &Deque_int_end;

	//Destructor
	d->dtor = &Deque_int_dtor;
}




#endif //DEQUE_HPP



