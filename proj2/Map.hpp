#ifndef MAP_HPP
#define MAP_HPP

#define MAX_HEIGHT 32

//Includes
#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
//using namespace std;

namespace cs540{
	template <class Key, class Mapped> class Map{

		public:

			//Access key with .first, value with .second
			typedef std::pair<Key, Mapped> ValueType;

			class BaseNode{
				friend class Map;
				BaseNode(BaseNode * n, BaseNode*p): next(n), prev(p) {}
				BaseNode * next, * prev;
				BaseNode() : next(NULL), prev(NULL) {}
			};
			class Node : public BaseNode{
				friend class Map;
				void rHeight(){
					int i = 0;
					for( ; (((double)rand() / RAND_MAX) >= 0.5) && i < MAX_HEIGHT; i++){}
					height = i + 1;
					forward = new BaseNode *[height];
					return;
				}
				//Default constructor
				Node(){
				}
				//Explicit height constructor
				Node(int heightIn){
					height = heightIn;
					forward = new BaseNode * [heightIn];
				}
				//Explicist value constructor
				Node(const ValueType & v) : first(v.first), second(v.second){
					rHeight();
				}
				//Data members 
				int height;
				Key first;
				Mapped second;
				BaseNode ** forward;
			};
			Node * head;

		private:
			Node * findNode(Key k){
				//Node * update = new Node(MAX_HEIGHT);
				Node * ret;




				/*for(int i = 0; i < MAX_HEIGHT; i++){
					ret->forward[i] = head->forward[i];
					}
				//Start at the max index
				for(int i = MAX_HEIGHT - 1; i >= 0; i--){
				//Attemp to move the tmp pointer fwd if 
				//Next bn ptr at that lvl is not null
				//and is < key looking for
				if(ret->forward[i] != NULL){
				while((ret->forward[i]->next != NULL) && (static_cast<Node*>(ret->forward[i]->next)->first > k))
				{
				ret->forward[i] = ret->forward[i]->next;
				}
				}
				}
				 */
				return ret;
			}


		public:
			//Constructors
			Map();
			Map(const Map & m);
			Map(std::initializer_list<std::pair<const Key, Mapped>> l){}

			~Map();

			//TODO: typemember, the pair
			//Operators
			Map & operator = (const Map & m);
			Mapped & operator [] (const Key & key);

			//TODO: ==, !=, <
			//Housekeeping information
			size_t size();
			bool empty();

			/*
			 *	Nested iterator classes and methods
			 */
			class BaseIter {
				public:


			};

			class Iterator : public BaseIter{
				public:
					Iterator & operator ++ (){}
					Iterator operator ++ (int i){}
					Iterator & operator -- (){}
					Iterator operator -- (int i){}

					ValueType & operator * () const{}
					//ValueType * operator -> ();
					Iterator & operator = (const Iterator & i){}
					//Node_base * cur;
					bool &operator == (const Iterator & rhs){}			
					bool &operator !=(const Iterator & rhs){}
				private:
			};

			class ConstIterator{
				public:
					ConstIterator & operator ++ (){}
					ConstIterator operator ++ (int i){}
					ConstIterator & operator -- (){}
					ConstIterator operator -- (int i){}

					//This line below is what triggers the linker error
					const ValueType & operator * () const{}
					const ValueType * operator -> () const{}
					ConstIterator & operator = (const ConstIterator & i){}
					//Node_base * cur;
					bool &operator == (const ConstIterator & rhs){}			
					bool &operator !=(const ConstIterator & rhs){}
				private:
			};

			class ReverseIterator{
				public:
				private:
					ReverseIterator();
			};
			//Iterator methods
			Iterator begin(){}
			Iterator end(){}

			ConstIterator begin() const{}
			ConstIterator end() const{}

			ReverseIterator rbegin(){}
			ReverseIterator rend(){}

			std::pair<Iterator, bool> insert(const ValueType& t){
				Node * newNode = new Node(t);
				//The array of base nodes we set to update after finding key
				BaseNode * update[MAX_HEIGHT];
				Node * currNode = head;
				for(int i = MAX_HEIGHT-1; i >= 0; i--)
				{
					while(currNode->forward[i] != NULL && (static_cast<Node*>(currNode->forward[i])->first > t.first))
					{
						currNode = static_cast<Node*>(currNode->forward[i]);
					}
					update[i] = currNode;
				}

				//Arrived at either end of list or value wanted
				for(int i = newNode->height - 1; i>=0; i--)
				{
					newNode->forward[i] = static_cast<Node*>(update[i])->forward[i];
					static_cast<Node*>(update[i])->forward[i] = newNode;
				}	
				Iterator iter;
				return std::make_pair(iter, false);	
			}			

			void erase(BaseIter pos){}
			void erase(const Key pos){}	
			Iterator find(const Key & k){}
			ConstIterator find(const Key & k) const{}





	};

	/*
	 *	Some common typedefs for use in methods section
	 */
	template<class Key, class Mapped>
		using ValueType = typename Map<Key, Mapped>::ValueType;

	template<class Key, class Mapped> 
		using Iterator = typename Map<Key, Mapped>::Iterator;

	template<class Key, class Mapped> 
		using ConstIterator = typename Map<Key, Mapped>::ConstIterator;

	template<class Key, class Mapped> 
		using ReverseIterator = typename Map<Key, Mapped>::ReverseIterator;

	//template<class Key, class Mapped>
	//	using Node = typename Map<Key, Mapped>::Node;


	/*
	 *	Methods section
	 *	----------------------------------------------------
	 *	All of the methods described in the requirements are 
	 *	implemented below as the api of this class.
	 * template<class Key, class Mapped> Map<Key, Mapped>::
	 */
	/*
	 *	Default constructor
	 */
	template<class Key, class Mapped> 
		Map<Key, Mapped>::Map(){
			srand(time(NULL));
			head = new Node(MAX_HEIGHT);
		}


	/*
	 *	Copy Constructor
	 */
	template<class Key, class Mapped> 
		Map<Key, Mapped>::Map(const Map<Key, Mapped> & m){

		}


	/*
	 *	Destructor
	 */
	template<class Key, class Mapped> 
		Map<Key, Mapped>::~Map(){

		}


	/*
	 *	Assignment operator
	 */
	template<class Key, class Mapped> 
		Map<Key, Mapped> &  Map<Key, Mapped>::operator=(const Map & m){

			return m;
		}


	/*
	 *	Bracket operator
	 */
	template<class Key, class Mapped> 
		Mapped & Map<Key, Mapped>::operator[](const Key & key){
		}

	//TODO: Rest of operators here: ==, !=, <

	/*
	 *	---------------------------------
	 *	Housekeeping information methods
	 */

	/*
	 *	Size: returns the number of elements
	 */
	template<class Key, class Mapped> size_t Map<Key, Mapped>::size(){
		return 0;
	}


	/*
	 *	Empty: returns whether or not the map is empty
	 */
	template<class Key, class Mapped> 
		bool Map<Key, Mapped>::empty(){
			return false;
		}
	/*template<class Key, class Mapped>
		std::pair<Iterator<Key, Mapped>, bool> insert(const ValueType<Key, Mapped>& t){
		Iterator<Key, Mapped> iter;	

		return std::make_pair(iter, false);
		}			
	 */

	/*
	 *	Iterator Class methods
	 *	----------------------
	 *	Typedefs for iterator classes
	 *
	 */

	/*
	 *	Regular Iterator functions
	//Begin
	template<class Key, class Mapped> 
	Iterator<Key, Mapped> Map<Key, Mapped>::begin(){
	Iterator i;


	return i;
	}
	//End 
	template<class Key, class Mapped> 
	Iterator<Key, Mapped> Map<Key, Mapped>::end(){
	Iterator i;
	return i;
	}
	 */



	//Body of the Iterator dereference
	//Dereference operator overload
	/*	template<class Key, class Mapped> 
			ValueType<Key, Mapped> & Map<Key, Mapped>::Iterator::operator *() const {
			return static_cast<Map<Key, Mapped>::Node * > (this->cur) ->val ;
			}
	//Body of the Const Iterator deref
	template<class Key, class Mapped> 
	const ValueType<Key, Mapped> & Map<Key, Mapped>::ConstIterator::operator *() const {
	return static_cast<Map<Key, Mapped>::Node * > (this->cur) ->val ;
	}
	 */








}


#endif //MAP_HH
