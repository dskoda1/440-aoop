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
	char type_name [sizeof("Deque_"#t)] = "Deque_"#t; \
	void (*push_back)(Deque_##t *, const t &); \
	void (*push_front)(Deque_##t *, const t &); \
	t& (*front)(Deque_##t *); \
	t& (*back)(Deque_##t *); \
	t& (*at)(Deque_##t *, int); \
	void (*pop_back)(Deque_##t *); \
	void (*pop_front)(Deque_##t *); \
	void (*clear)(Deque_##t *); \
	void (*dtor)(Deque_##t *); \
	Deque_##t##_Iterator (*begin)(Deque_##t *); \
	Deque_##t##_Iterator (*end)(Deque_##t *);}; \
struct Deque_##t##_Iterator{ \
	int  current; \
	Deque_##t * d; \
	t& (*deref)(Deque_##t##_Iterator *di); \
	void (*inc)(Deque_##t##_Iterator *); \
	void (*dec)(Deque_##t##_Iterator *);}; \
void Deque_##t##_iter_inc(Deque_##t##_Iterator * di) \
{ di->current += 1; } \
void Deque_##t##_iter_dec(Deque_##t##_Iterator * di) \
{ di->current -= 1; } \
t& Deque_##t##_Iterator_deref(Deque_##t##_Iterator * di) \
{ return di->d->at(di->d, di->current); } \
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator d1, Deque_##t##_Iterator d2) \
{ if(d1.current == d2.current){	return true; } \
	else return false; } \
void setUpIterator(Deque_##t##_Iterator * di) \
{ di->inc = &Deque_##t##_iter_inc; \
	di->dec = &Deque_##t##_iter_dec; \
	di->deref = &Deque_##t##_Iterator_deref; } \
Deque_##t##_Iterator Deque_##t##_end(Deque_##t * d) \
{ Deque_##t##_Iterator di; \
	setUpIterator(&di); \
	di.d = d; \
	if(d->bb >= 0) \
	{ di.current = d->frontSize + d->backSize; } \
	else \
	{ di.current = d->frontSize;} \
	return di; } \
Deque_##t##_Iterator Deque_##t##_begin(Deque_##t * d) \
{ Deque_##t##_Iterator di; \
	di.d = d; \
	setUpIterator(&di); \
	if(d->ff >= 0) { di.current = d->ff; } \
	else{ di.current = d->bf; } \
  return di; } \
bool  Deque_##t##_equal(Deque_##t d1, Deque_##t d2) \
{if(d1.size(&d1) != d2.size(&d2)) return false; \
	for(int i = 0; i < d1.size(&d1); i++) \
	{	if(d1.comp(d1.at(&d1, i), d2.at(&d2, i)) || d1.comp(d2.at(&d2, i), d1.at(&d1, i))) return false; } \
	return true;} \
int Deque_##t##_size(Deque_##t * d) \
{ return d->backSize + d->frontSize; } \
bool Deque_##t##_empty(Deque_##t * d) \
{ int size = d->backSize + d->frontSize; \
	if(size > 0){ return false; } \
	else {	return true;}} \
void reallocateFront(Deque_##t * d, int sizeMult) \
{ int newSize = d->maxFrontSize * sizeMult; \
	t * newArr = ( t *)calloc(newSize, sizeof( t )); \
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
void reallocateBack(Deque_##t * d, int sizeMult) \
{ int newSize = d->maxBackSize * sizeMult; \
	t * newArr = ( t *)calloc(newSize, sizeof( t )); \
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
void Deque_##t##_push_back(Deque_##t *d, const t & val) \
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
void Deque_##t##_push_front(Deque_##t *d, const t & val) \
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
t& Deque_##t##_front(Deque_##t *d) \
{ \
	if((d->bf == -1) && (d->fb == -1)) \
	{ return (d->frontArr)[d->ff];} \
	else if(d->fb > -1) \
	{ return  (d->frontArr)[d->ff];} \
	else \
	{ return (d->backArr)[d->bf];}} \
t& Deque_##t##_back(Deque_##t *d) \
{ \
	if((d->bf == -1) && (d->fb == -1)) \
	{ return (d->backArr)[d->bb];} \
	else if(d->fb > -1) \
	{return (d->frontArr)[d->fb];} \
	else \
	{return (d->backArr)[d->bb];}} \
t& Deque_##t##_at(Deque_##t *d, int val) \
{ if(val <= d->frontSize - 1) \
	{ int inv = d->frontSize - val; \
		return d->frontArr[inv + d->fb];} \
	else{return d->backArr[val - d->frontSize];}} \
void Deque_##t##_pop_front(Deque_##t *d) \
{ if(d->bf > -1 || d->ff == -1) \
	{(d->bf)++; \
		(d->backSize)--; \
		if(d->bf > (d->maxBackSize/4)) \
		{reallocateBack(d, 1);}} \
	else{(d->ff)--; \
		if(d->ff != -1){(d->frontSize)--;}}} \
void Deque_##t##_pop_back(Deque_##t *d) \
{if(d->fb > -1 || d->bb == -1){ \
		(d->fb)++; \
		(d->frontSize)--; \
		if(d->fb > (d->maxFrontSize/4)) \
		{reallocateFront(d, 1);}} \
	else{(d->bb)--; \
		if(d->bb != -1){(d->backSize)--;}}} \
void Deque_##t##_clear(Deque_##t *d) \
{ d->ff = -1; \
	d->fb = -1; \
	d->bf = -1; \
	d->bb = -1; \
	d->frontSize = 0; \
	d->backSize = 0;} \
void Deque_##t##_dtor(Deque_##t * d) \
{ free(d->frontArr); \
	free(d->backArr);} \
void Deque_##t##_ctor(Deque_##t * d, bool (*f)(const t &, const t &)) \
{ d->size = &Deque_##t##_size; \
	d->frontArr = ( t *) malloc(1000 * sizeof( t )); \
	d->ff = -1; \
	d->fb = -1; \
	d->maxFrontSize = 1000; \
	d->frontSize = 0; \
	d->backArr = ( t *) malloc(1000 * sizeof( t )); \
	d->bf = -1; \
	d->bb = -1; \
	d->maxBackSize = 1000; \
	d->backSize = 0; \
	d->comp = f; \
	d->empty = &Deque_##t##_empty; \
	d->push_back = &Deque_##t##_push_back; \
	d->push_front = &Deque_##t##_push_front; \
	d->front = &Deque_##t##_front; \
	d->back = &Deque_##t##_back; \
	d->at = &Deque_##t##_at; \
	d->pop_back = &Deque_##t##_pop_back; \
	d->pop_front = &Deque_##t##_pop_front; \
	d->clear = &Deque_##t##_clear; \
	d->begin = &Deque_##t##_begin; \
	d->end = &Deque_##t##_end; \
	d->dtor = &Deque_##t##_dtor; \
}

#endif //DEQUE_HPP



