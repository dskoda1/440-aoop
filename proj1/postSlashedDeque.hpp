#ifndef DEQUE_HPP
#define DEQUE_HPP


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define Deque_DEFINE(t) \
struct Deque_##t##_Iterator; \
struct Deque_##t { \
	t * frontArr; \
	int ff; \
	int fb; \
	int frontSize; \
	double maxFrontSize; \
	t * backArr; \
	int bf; \
	int bb; \
	int backSize; \
	double maxBackSize; \
	bool (*comp)(const t &, const t &); \
	int (*size)(Deque_##t *); \
	bool (*empty)(Deque_##t *); \
	char type_name [sizeof("Deque_##t##")] = "Deque_##t##"; \
	void (*push_back)(Deque_int *, const int &); \
	void (*push_front)(Deque_int *, const int &); \
	int (*front)(Deque_int *); \
	int (*back)(Deque_int *); \
	int (*at)(Deque_int *, int); \
	void (*pop_back)(Deque_int *); \
	void (*pop_front)(Deque_int *); \
	void (*clear)(Deque_int *); \
	void (*dtor)(Deque_int *); \
	Deque_int_Iterator (*begin)(Deque_int *); \
	Deque_int_Iterator (*end)(Deque_int *);}; \
struct Deque_int_Iterator{ \
	int  current; \
	Deque_int * d; \
	int (*deref)(Deque_int_Iterator *di); \
	void (*inc)(Deque_int_Iterator *); \
	void (*dec)(Deque_int_Iterator *);}; \
void Deque_int_iter_inc(Deque_int_Iterator * di) \
{ di->current += 1; } \
void Deque_int_iter_dec(Deque_int_Iterator * di) \
{ di->current -= 1; } \
int Deque_int_Iterator_deref(Deque_int_Iterator * di) \
{ return di->d->at(di->d, di->current); } \
bool Deque_int_Iterator_equal(Deque_int_Iterator d1, Deque_int_Iterator d2) \
{ if(d1.current == d2.current){	return true; } \
	else return false; } \
void setUpIterator(Deque_int_Iterator * di) \
{ di->inc = &Deque_int_iter_inc; \
	di->dec = &Deque_int_iter_dec; \
	di->deref = &Deque_int_Iterator_deref; } \
Deque_int_Iterator Deque_int_end(Deque_int * d) \
{ Deque_int_Iterator di; \
	setUpIterator(&di); \
	di.d = d; \
	if(d->bb >= 0) \
	{ di.current = d->frontSize + d->backSize; } \
	else \
	{ di.current = d->frontSize;} \
	return di; } \
Deque_int_Iterator Deque_int_begin(Deque_int * d) \
{ Deque_int_Iterator di; \
	di.d = d; \
	setUpIterator(&di); \
	if(d->ff >= 0) { di.current = d->ff; } \
	else{ di.current = d->bf; } \
  return di; } \
bool  Deque_int_equal(Deque_int d1, Deque_int d2) \
{if(d1.size(&d1) != d2.size(&d2)) return false; \
	for(int i = 0; i < d1.size(&d1); i++) \
	{	if(d1.comp(d1.at(&d1, i), d2.at(&d2, i)) || d1.comp(d2.at(&d2, i), d1.at(&d1, i))) return false; } \
	return true;} \
int Deque_int_size(Deque_int * d) \
{ return d->backSize + d->frontSize; } \
bool Deque_int_empty(Deque_int * d) \
{ int size = d->backSize + d->frontSize; \
	if(size > 0){ return false; } \
	else {	return true;}} \
void reallocateFront(Deque_int * d, int sizeMult) \
{ int newSize = d->maxFrontSize * sizeMult; \
	int * newArr = (int *)calloc(newSize, sizeof(int)); \
	if(d->fb == -1) \
	{ for(int i = 0; i <= d->ff; i++){newArr[i] = d->frontArr[i];} \
	}else{ int i, j; \
		for(i = d->fb, j = 0; i <= d->ff; i++, j++) \
		{ newArr[j] = d->frontArr[i]; }} \
	d->fb = -1; \
	d->ff = d->frontSize - 1; \
	free(d->frontArr); \
	d->frontArr = newArr; \
	d->maxFrontSize = newSize; } \
void reallocateBack(Deque_int * d, int sizeMult) \
{ int newSize = d->maxBackSize * sizeMult; \
	int * newArr = (int *)calloc(newSize, sizeof(int)); \
	if(d->bf == -1) \
	{ for(int i = 0; i <= d->bb; i++){ newArr[i] = d->backArr[i];} \
	}else{ int i, j; \
		for(i = d->bf, j = 0; i <= d->bb; i++, j++) \
		{ newArr[j] = d->backArr[i];}} \
	d->bf = -1; \
	d->bb = d->backSize - 1; \
	free(d->backArr); \
	d->backArr = newArr; \
	d->maxBackSize = newSize;} \
void Deque_int_push_back(Deque_int *d, const int & val) \
{ if(d->fb >= 0 && d->bb == -1 && d->bf == -1) \
	{ (d->fb)--; \
		if(d->fb >= 0) \
    { d->frontArr[d->fb] = val; \
     (d->frontSize)++;} \
		else{(d->bb)++; \
      d->backArr[d->bb] = val; \
      (d->backSize)++;}} \
	else{(d->bb)++; \
		d->backArr[d->bb] = val; \
		(d->backSize)++; \
		if((d->backSize / d->maxBackSize) > 0.8) \
    {reallocateBack(d, 3);}}} \
void Deque_int_push_front(Deque_int *d, const int & val) \
{ if(d->bf >= 0 && d->ff == -1 && d->fb == -1){(d->bf)--; \
    if(d->bf >= 0) \
      {d->backArr[d->bf] = val; \
      (d->backSize)++; \
    }else{(d->ff)++; \
      d->frontArr[d->ff] = val; \
      (d->frontSize)++;} \
  }else{(d->ff)++; \
    d->frontArr[d->ff] = val; \
    (d->frontSize)++; \
    if((d->frontSize / d->maxFrontSize) > 0.8) \
    {reallocateFront(d, 3);}}} \
int Deque_int_front(Deque_int *d) \
{ int ret = 0; \
	if((d->bf == -1) && (d->fb == -1)) \
	{ret = (d->frontArr)[d->ff];} \
	else if(d->fb > -1) \
	{ret = (d->frontArr)[d->ff];} \
	else if(d->bf > -1) \
	{ret = (d->backArr)[d->bf];} \
	return ret;} \
int Deque_int_back(Deque_int *d) \
{ int ret = 0; \
	if((d->bf == -1) && (d->fb == -1)) \
	{ret = (d->backArr)[d->bb];} \
	else if(d->fb > -1) \
	{ret = (d->frontArr)[d->fb];} \
	else if(d->bf > -1) \
	{ret = (d->backArr)[d->bb];} \
	return ret;} \
int Deque_int_at(Deque_int *d, int val) \
{ int ret = 0; \
	if(val <= d->frontSize - 1) \
	{ int inv = d->frontSize - val; \
		ret = d->frontArr[inv + d->fb];} \
	else{ret = d->backArr[val - d->frontSize];} \
	return ret;} \
void Deque_int_pop_front(Deque_int *d) \
{ if(d->bf > -1 || d->ff == -1) \
	{(d->bf)++; \
		(d->backSize)--; \
		if(d->bf > (d->maxBackSize/4)) \
		{reallocateBack(d, 1);}} \
	else{(d->ff)--; \
		if(d->ff != -1){(d->frontSize)--;}}} \
void Deque_int_pop_back(Deque_int *d) \
{if(d->fb > -1 || d->bb == -1){ \
		(d->fb)++; \
		(d->frontSize)--; \
		if(d->fb > (d->maxFrontSize/4)) \
		{reallocateFront(d, 1);}} \
	else{(d->bb)--; \
		if(d->bb != -1){(d->backSize)--;}}} \
void Deque_int_clear(Deque_int *d) \
{ d->ff = -1; \
	d->fb = -1; \
	d->bf = -1; \
	d->bb = -1; \
	d->frontSize = 0; \
	d->backSize = 0;} \
void Deque_int_dtor(Deque_int * d) \
{ free(d->frontArr); \
	free(d->backArr);} \
void Deque_int_ctor(Deque_int * d, bool (*f)(const int&, const int&)) \
{ d->size = &Deque_int_size; \
	d->frontArr = (int *) malloc(1000 * sizeof(int)); \
	d->ff = -1; \
	d->fb = -1; \
	d->maxFrontSize = 1000; \
	d->frontSize = 0; \
	d->backArr = (int*) malloc(1000 * sizeof(int)); \
	d->bf = -1; \
	d->bb = -1; \
	d->maxBackSize = 1000; \
	d->backSize = 0; \
	d->comp = f; \
	d->empty = &Deque_int_empty; \
	d->push_back = &Deque_int_push_back; \
	d->push_front = &Deque_int_push_front; \
	d->front = &Deque_int_front; \
	d->back = &Deque_int_back; \
	d->at = &Deque_int_at; \
	d->pop_back = &Deque_int_pop_back; \
	d->pop_front = &Deque_int_pop_front; \
	d->clear = &Deque_int_clear; \
	d->begin = &Deque_int_begin; \
	d->end = &Deque_int_end; \
	d->dtor = &Deque_int_dtor; \
}

#endif //DEQUE_HPP



