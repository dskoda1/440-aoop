#ifndef DEQUE_HPP
#define DEQUE_HPP


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

#define Deque_DEFINE(T) Deque_int d;
struct Deque_int_Iterator;

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

	//Comparator function
	bool (*comp)(const int&, const int&);

	//Length
	//Number of members that are actually in, returns length
	int (*size)(Deque_int *);

	//Check if empty
	bool (*empty)(Deque_int *);
	//Identifier of struct name
	//char * type_name;
	char type_name [sizeof("Deque_int")] = "Deque_int";
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
struct Deque_int_Iterator{
	int  current;
	Deque_int * d;
	int (*deref)(Deque_int_Iterator *di);

	void (*inc)(Deque_int_Iterator *);
	void (*dec)(Deque_int_Iterator *);

};

void Deque_int_iter_inc(Deque_int_Iterator * di)
{
	di->current += 1; 
}
void Deque_int_iter_dec(Deque_int_Iterator * di)
{
	di->current -= 1;

}
//Dereference the iterator at its location
int Deque_int_Iterator_deref(Deque_int_Iterator * di)
{
	 return di->d->at(di->d, di->current);
}
bool Deque_int_Iterator_equal(Deque_int_Iterator d1, Deque_int_Iterator d2)
{
	if(d1.current == d2.current)
	{	return true; }
	else return false;


}
void setUpIterator(Deque_int_Iterator * di)
{
	di->inc = &Deque_int_iter_inc;
	di->dec = &Deque_int_iter_dec;
	di->deref = &Deque_int_Iterator_deref;
}

Deque_int_Iterator Deque_int_end(Deque_int * d)
{
	Deque_int_Iterator di;
	setUpIterator(&di);
	di.d = d;
	if(d->bb >= 0)
	{
		di.current = d->frontSize + d->backSize;
	}
	else
	{
		di.current = d->frontSize;
	}

	return di;
}

Deque_int_Iterator Deque_int_begin(Deque_int * d)
{
  Deque_int_Iterator di;
	di.d = d;
	setUpIterator(&di);
	if(d->ff >= 0)
	{
		di.current = d->ff;
	}
	else
	{
		di.current = d->bf;
	}

  return di;
}
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
	//Quick check of sizes first
	if(d1.size(&d1) != d2.size(&d2))
		return false;
	
	//Now iterate through and compare values
	for(int i = 0; i < d1.size(&d1); i++)
	{	
		//check each comp function to be false;
		if(d1.comp(d1.at(&d1, i), d2.at(&d2, i)) || d2.comp(d1.at(&d1, i), d2.at(&d2, i)))
			return false;
	}	
	
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
void reallocateFront(Deque_int * d, int sizeMult)
{
	int newSize = d->maxFrontSize * sizeMult;
	int * newArr = (int *)calloc(newSize, sizeof(int));

	if(d->fb == -1)
	{
		for(int i = 0; i <= d->ff; i++)
		{
			newArr[i] = d->frontArr[i];
		}
	}else{
		int i, j;	
		for(i = d->fb, j = 0; i <= d->ff; i++, j++)
		{
			newArr[j] = d->frontArr[i];
		}
	}
	d->fb = -1;
	d->ff = d->frontSize - 1;
	free(d->frontArr);
	d->frontArr = newArr;
	d->maxFrontSize = newSize;

}
void reallocateBack(Deque_int * d, int sizeMult)
{
	int newSize = d->maxBackSize * sizeMult;
	int * newArr = (int *)calloc(newSize, sizeof(int));

	if(d->bf == -1)
	{
		for(int i = 0; i <= d->bb; i++)
		{
			newArr[i] = d->backArr[i];
		}
	}else{
		int i, j;	
		for(i = d->bf, j = 0; i <= d->bb; i++, j++)
		{
			newArr[j] = d->backArr[i];
		}
	}
	d->bf = -1;
	d->bb = d->backSize - 1;
	free(d->backArr);
	d->backArr = newArr;
	d->maxBackSize = newSize;
}

//Push a value onto the back of the deque
void Deque_int_push_back(Deque_int *d, int val)
{
	//First case: no elements in back array, push to fb
	if(d->fb >= 0 && d->bb == -1 && d->bf == -1)
	{
		(d->fb)--;
		if(d->fb >= 0)
    {//push onto the back of the front
      d->frontArr[d->fb] = val;
      (d->frontSize)++;

    }else
    {//push onto the back of the back
      (d->bb)++;
      d->backArr[d->bb] = val;
      (d->backSize)++;
    }
	}
	else//Normal case, push to bb
	{
		(d->bb)++;
		d->backArr[d->bb] = val;
		(d->backSize)++;	
		if((d->backSize / d->maxBackSize) > 0.8)
    {
      reallocateBack(d, 2);
    }
	}
}
//Push a value onto the front of the deque
void Deque_int_push_front(Deque_int *d, int val)
{
	//First case: No elements in front, push to bf
	if(d->bf >= 0 && d->ff == -1 && d->fb == -1)//front is empty
  {
    (d->bf)--;
    if(d->bf >= 0)
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
	else//Normal: push to front
	{
		(d->ff)++;
    d->frontArr[d->ff] = val;
    (d->frontSize)++;
    //Check if front is too big
    if((d->frontSize / d->maxFrontSize) > 0.8)
    {
      reallocateFront(d, 2);
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
	int ret = 0;
	if(val <= d->frontSize - 1)
	{
		int inv = d->frontSize - val;
		
		ret = d->frontArr[inv + d->fb];
	}	
	else
	{
		ret = d->backArr[val - d->frontSize];
	}
	return ret;
}


/*
 * Data removal methods
 *	pop_front, pop_back
 */
//Pop a value off the front
void Deque_int_pop_front(Deque_int *d)
{
	if(d->bf > -1 || d->ff == -1)//front is empty
	{
		(d->bf)++;
		(d->backSize)--;
		if(d->bf > (d->maxBackSize/2))
		{
			reallocateBack(d, 1);
		}
		//Check if bf is bigger than half of backMax
	}
	else
	{
		(d->ff)--;
		if(d->ff != -1)
		{
			(d->frontSize)--;
		}
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
		if(d->fb > (d->maxFrontSize/2))
		{
			reallocateFront(d, 1);
		}
	}
	else
	{
		(d->bb)--;
		if(d->bb != -1)
		{
			(d->backSize)--;
		}
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
	d->frontSize = 0;
	d->backSize = 0;
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

	d->comp = f;

	d->empty = &Deque_int_empty;
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



