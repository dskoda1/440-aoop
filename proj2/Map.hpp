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
				Node(const ValueType & v) : val(v), first(v.first), second(v.second){
					rHeight();
				}
				//Data members 
				private:
				int height;
				ValueType val;
				Key first;
				Mapped second;
				BaseNode ** forward;
			};
			Node * head;

		private:


		public:
			//Constructors
			Map();
			Map(const Map & m);
			Map(std::initializer_list<std::pair<const Key, Mapped>> l){}

			~Map();

			//TODO: typemember, the pair
			//Operators
			Map & operator = (const Map & m){}
			Mapped & operator [] (const Key & key){}

			//TODO: ==, !=, <
			//Housekeeping information
			size_t size(){}
			bool empty(){}

			class Iterator{
				friend class Map;
				public:
				Iterator(){}
				Iterator(Node * headIn, Node* curIn) : first(curIn->first), second(curIn->second), head(headIn), cur(curIn){}	

				Iterator & operator ++ (){
					if(static_cast<Node*>(cur->forward[0]) != NULL){
						cur = static_cast<Node*>(cur->forward[0]);	
						first = cur->first;
						second = cur->second;
					}else{
						cur = nullptr;
					}
					return *(this);
				}
				Iterator operator ++ (int i){}

				Iterator & operator -- (){}
				Iterator operator -- (int i){}

				ValueType & operator * () const{
					return cur->val;
				}
				ValueType * operator -> (){}

				Iterator & operator = (const Iterator & i){}
				friend bool operator == (const Iterator & lhs, const Iterator & rhs){
					return (lhs.cur == rhs.cur && lhs.head == rhs.head);
				}
				friend bool operator != (const Iterator & lhs, const Iterator & rhs){
					return !(lhs == rhs);
				}
				Key first;
				Mapped second;
				private:
				Node * head;
				Node * cur;
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
			Iterator begin(){
				Iterator i;
				i.head = head;
				i.cur = static_cast<Node *>(head->forward[0]);
				i.first = i.cur->first;
				i.second = i.cur->second;

				return i;
			}
			Iterator end(){
				Iterator i;
				i.head = head;
				i.cur = nullptr;
				//i.first = NULL;
				//i.second = NULL;

				return i;
			}
			//TODO:
			ConstIterator begin() const{}
			ConstIterator end() const{}
			//TODO:
			ReverseIterator rbegin(){}
			ReverseIterator rend(){}

			BaseNode ** findNode(Key k){
				static BaseNode * ret [MAX_HEIGHT];

				Node * currNode = head;
				for(int i = MAX_HEIGHT-1; i >= 0; i--)
				{
					while(currNode->forward[i] != NULL && (static_cast<Node*>(currNode->forward[i])->first < k))
					{
						currNode = static_cast<Node*>(currNode->forward[i]);
					}
					ret[i] = currNode;
				}
				return ret;
			}	

			std::pair<Iterator, bool> insert(const ValueType& t){
				Node * newNode = new Node(t);

				//Get the node right before we want to insert
				BaseNode ** update = findNode(t.first);
				
				//TODO:
				//Need to check if node with t.key already in or not
				for(int i = newNode->height - 1; i>=0; i--)
				{
					newNode->forward[i] = static_cast<Node*>(update[i])->forward[i];
					static_cast<Node*>(update[i])->forward[i] = newNode;
				}
				Iterator iter(head, newNode);
				return std::make_pair(iter, true);	
			}			

			void erase(Iterator pos){}
			void erase(const Key pos){}	
			Iterator find(const Key & k){
				Node * previous = static_cast<Node*>(findNode(k)[0]);
				if(previous != NULL && previous->forward[0] != NULL)
				{
					Node * match = static_cast<Node *>(previous->forward[0]);
					if(match->first == k){
						return Iterator(head, match);
					}else{
						std::cerr << "Map::find got a non null before node, but key doesnt match" << std::endl;
					}	
				}else{
					return end();
				}

			}
			ConstIterator find(const Key & k) const{}





	};
	template<class Key, class Mapped>
		using ValueType = typename Map<Key, Mapped>::ValueType;

	template<class Key, class Mapped> 
		using Iterator = typename Map<Key, Mapped>::Iterator;

	template<class Key, class Mapped> 
		using ConstIterator = typename Map<Key, Mapped>::ConstIterator;

	template<class Key, class Mapped> 
		using ReverseIterator = typename Map<Key, Mapped>::ReverseIterator;

	template<class Key, class Mapped> 
		Map<Key, Mapped>::Map(){
			srand(time(NULL));
			head = new Node(MAX_HEIGHT);
		}

	template<class Key, class Mapped> 
		Map<Key, Mapped>::Map(const Map<Key, Mapped> & m){

		}

	template<class Key, class Mapped> 
		Map<Key, Mapped>::~Map(){

		}

	/*
		 template<class Key, class Mapped>
		 bool operator==(Iterator<Key, Mapped> const & l, Iterator<Key, Mapped> const & r){
		 return false;
		 }	
	 */	template<class Key, class Mapped>
	inline bool operator!=(const Iterator<Key, Mapped> & l, const Iterator<Key, Mapped> & r){
		return false;
	}	


}


#endif //MAP_HH
