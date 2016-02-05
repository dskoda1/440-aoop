#ifndef DEQUE_HPP
#define DEQUE_HPP


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define Deque_DEFINE(T) Deque_int d;


struct Deque_int_Iterator{
	int * current;

	int (*deref)(Deque_int_Iterator *di);

	void (*inc)(Deque_int_Iterator *);
	void (*dec)(Deque_int_Iterator *);

};

//Dereference the iterator at its location
/*
	 int Deque_int_Iterator_deref(Deque_int_Iterator * di)
	 {
	 return 1;
	 }
 */
bool Deque_int_Iterator_equal(Deque_int_Iterator d1, Deque_int_Iterator d2)
{
	return true;
}

struct Deque_int{
	/*
	 *	This struct will be maintaining two different array, which will act	
	 *	like one to the user. A front array, which has a front and back index,
	 *	and a back array, which also has indices. 
	 */

	//Front array and pointers
	int * frontArr;
	int ff;
	int fb;
	int frontSize;
	double maxFrontSize;

	//Back array and pointers
	int * backArr;
	int bf;
	int bb;
	int backSize;
	double maxBackSize;

	//Length
	//Number of members that are actually in, returns length
	int (*size)(Deque_int *);

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

void print_Deque(Deque_int * d)
{
	cout << "Information about deque: " << d << endl;
	cout << "front size: " << d->frontSize << endl;
	cout << "max front size: " << d->maxFrontSize << endl;
	cout << "back size: " << d->backSize << endl;
	cout << "max back size: " << d->maxBackSize << endl;
	cout << "bb: " << d->bb << endl;
	cout << "bf: " << d->bf << endl;
	cout << "fb: " << d->fb << endl;
	cout << "ff: " << d->ff << endl;

}

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
	return d->backSize + d->frontSize;
}
//Return whether or not it's empty
bool Deque_int_empty(Deque_int * d)
{
	int size = d->backSize + d->frontSize;

	if(size > 0)
	{ return false; }
	else
	{	return true;	}

}

/*
 *	Data entry methods
 *	push_back, push_front
 */
void reallocateFront(Deque_int * d)
{

}
void reallocateBack(Deque_int * d)
{
	//int newSize = d->maxBackSize * 2;


}

//Push a value onto the back of the deque
void Deque_int_push_back(Deque_int *d, int val)
{
	//If both arrays have values
	cout << &d->backArr[d->bb + 1] << endl;
	if((d->bf == -1) && (d->fb == -1))
	{
		(d->bb)++;
		cout << "about to set the next val " << endl;
		d->backArr[d->bb] = val;
		(d->backSize)++;
		//Check if back is too big
		if((d->backSize / d->maxBackSize) > 0.8)
		{
			cout << "Back got too big reallocating.. size: " << d->backSize << ", " << d->maxBackSize << endl;
			d->backArr = (int *)realloc(d->backArr, d->maxBackSize * 4);
			d->maxBackSize = d->maxBackSize * 4;
		}

	}
	else if(d->bf > -1)//front is empty
	{
		(d->bb)++;
		d->backArr[d->bb] = val;
		(d->backSize)++;
		//Check if back is too big
		if((d->backSize / d->maxBackSize) > 0.8)
		{
			cout << "Back got too big reallocating.. size: " << d->backSize << ", " << d->maxBackSize << endl;
			d->backArr = (int *)realloc(d->backArr, d->maxBackSize * 2);
			d->maxBackSize = d->maxBackSize * 2;
		}

	}
	else if(d->fb > -1)//back is empty
	{
		(d->fb)--;
		if(d->fb > -1)
		{//push onto the back of the front
			d->frontArr[d->fb] = val;
			(d->frontSize)++;

		}else
		{//push onto the back of the back
			(d->bb)++;
			d->backArr[d->bb] = val;
			(d->backSize)++;
		}

		//Dont need to check anything?

	} 
}
//Push a value onto the front of the deque
void Deque_int_push_front(Deque_int *d, int val)
{
	//if both arrays have values
	//or are empty
	if((d->bf == -1) && (d->fb == -1))
	{
		(d->ff)++;
		d->frontArr[d->ff] = val;
		(d->frontSize)++;
		//Check if front is too big
		if((d->frontSize / d->maxFrontSize) > 0.8)
		{
			cout << "front got too big reallocating.. size: " << d->frontSize << ", " << d->maxFrontSize << endl;
			d->frontArr = (int*)realloc(d->frontArr, d->maxFrontSize * 2);
			d->maxFrontSize = d->maxFrontSize * 2;
		}
	}
	else if(d->fb > -1)//back is empty
	{
		(d->ff)++;
		d->frontArr[d->ff] = val;
		(d->frontSize)++;
		//Check if front is too big
		if((d->frontSize / d->maxFrontSize) > 0.8)
		{
			cout << "front got too big reallocating.. size: " << d->frontSize << ", " << d->maxFrontSize << endl;
			d->frontArr = (int *)realloc(d->frontArr, d->maxFrontSize * 2);
			d->maxFrontSize = d->maxFrontSize * 2;
		}
	}
	else if(d->bf > -1)//front is empty
	{
		(d->bf)--;
		if(d->bf > -1)
		{//push onto the front of the back
			d->backArr[d->bf] = val;
			(d->backSize)++;
		}
		else
		{//push onto the front of the front
			(d->ff)++;
			d->frontArr[d->ff] = val;
			(d->frontSize)++;
		}
	}
}

/*
 * Getter methods
 * front, back, at
 */
//Get the value at the front
int Deque_int_front(Deque_int *d)
{
	int ret = 0;
	//if both arrays have values
	if((d->bf == -1) && (d->fb == -1))
	{
		ret = (d->frontArr)[d->ff];
	}
	else if(d->fb > -1)//back is empty
	{
		ret = (d->frontArr)[d->ff];
	}
	else if(d->bf > -1)//front is empty
	{
		ret = (d->backArr)[d->bf];
	}
	return ret;

}
//Get the value in the back
int Deque_int_back(Deque_int *d)
{
	int ret = 0;
	//if both arrays have values
	if((d->bf == -1) && (d->fb == -1))
	{
		ret = (d->backArr)[d->bb];
	}
	else if(d->fb > -1)//back is empty
	{
		ret = (d->frontArr)[d->fb];
	}
	else if(d->bf > -1)//front is empty
	{
		ret = (d->backArr)[d->bb];
	}
	//Get the value where bbp points to
	return ret;
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
	//if both arrays have values
	//or are empty
	//print_Deque(d);
	if(d->bf > -1 || d->ff == -1)//front is empty
	{
		(d->bf)++;
		(d->backSize)--;
		//Check if bf is bigger than half of backMax
	}
	else if(d->fb > -1)//back is empty
	{
		(d->ff)--;
		(d->frontSize)--;
	}
	else if((d->bf == -1) && (d->fb == -1))
	{
		(d->ff)--;
		(d->frontSize)--;
	}

}
//Pop a value off the back
void Deque_int_pop_back(Deque_int *d)
{
	//if both arrays have values
	//or are empty
	if(d->fb > -1 || d->bb == -1)//back is empty
	{
		(d->fb)++;
		(d->frontSize)--;
		//Check if fb > frontMax/2
	}
	else if(d->bf > -1)//front is empty
	{
		(d->bb)--;
		(d->backSize)--;
	}
	else if((d->bf == -1) && (d->fb == -1))
	{
		(d->bb)--;
		(d->backSize)--;
	}
}
//Remove all values
void Deque_int_clear(Deque_int *d)
{
	//reset all indices to -1
	d->ff = -1;
	d->fb = -1;
	d->bf = -1;
	d->bb = -1;

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
	//Free the arrays
	free(d->frontArr);
	free(d->backArr);
}

void Deque_int_ctor(Deque_int * d, bool (*f)(const int&, const int&))
{
	//Initialize the members here
	d->size = &Deque_int_size;

	//Front array
	d->frontArr = (int *) malloc(1000 * sizeof(int));
	d->ff = -1;
	d->fb = -1;
	d->maxFrontSize = 1000;
	d->frontSize = 0;

	//Back array
	d->backArr = (int*) malloc(1000 * sizeof(int));
	d->bf = -1;
	d->bb = -1;
	d->maxBackSize = 1000;
	d->backSize = 0;


	d->empty = &Deque_int_empty;
	//Type_name identifier for struct
	/*
		 char type [9];// = "Deque_int\0";
		 d->type_name = (char *)malloc(strlen(type) + 1);
		 memcpy(d->type_name, type, strlen(type));
	//memcpy(d->type_name, type, strlen(type)+1); 
	 */
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



