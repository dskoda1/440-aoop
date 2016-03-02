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
			class Node;
			class BaseNode{
				friend class Map;
				public:
				BaseNode(int heightIn){
					height = heightIn;
					forward = new Node * [heightIn];
					for(int i = 0; i < heightIn; i++){
						forward[i] = NULL;
					}
				}	
				int height = 0;
				Node ** forward;
			};
			/*	----------------------------------------------------
			 *	Internal Node class
			 */
			class Node{
				friend class Map;
				public:

				//Default constructor
				Node(){
				}
				//Destructor
				~Node(){
					delete [] forward;
				}
				//Explicit height constructor
				Node(int heightIn){
					height = heightIn;
					forward = new Node * [heightIn];
					for(int i = 0; i < heightIn; i++){
						forward[i] = NULL;
					}
				}
				//Explicit value constructor
				Node(const ValueType & v) : data(v)//, first(v.first), second(v.second){
				{
					rHeight();
				}
				private:
				//Obtain a random height for the node, and initialize the fwd ptr array
				void rHeight(){
					int i = 0;
					for( ; (((double)rand() / RAND_MAX) >= 0.5) && i < MAX_HEIGHT; i++){}
					height = i + 1;
					forward = new Node *[height];
					return;
				}
				//Data members 
				int height;
				ValueType data;
				//Key first;
				//Mapped second;
				Node * back;
				Node ** forward;
			};

			class Iterator{
				friend class Map;
				public:
				//Constructors
				Iterator(){}
				//Copy constructor: implicit
				//Assignment operator: implicit
				//Destructor: implicit
				//Explicit value constructor
				Iterator(Map * mapIn, Node* curIn) : first(curIn->data.first), second(curIn->data.second), map(mapIn), cur(curIn){}	

				//Preincrement
				Iterator & operator ++ (){
					if((cur->forward[0]) != NULL){
						cur = (cur->forward[0]);	
						first = cur->data.first;
						second = cur->data.second;
					}else{
						cur = nullptr;
					}
					return *(this);
				}
				//Postincrement
				Iterator operator ++ (int){
					Iterator old( * this);
					++(*(this));
					return old;	
				}
				//Predecrement
				Iterator & operator -- (){
					if(cur !=  NULL){
						cur = (cur->back);
						first = cur->data.first;
						second = cur->data.second;

					}else{
						cur = map->tail;
						first = cur->data.first;
						second = cur->data.second;
					}
					return *(this);
				}
				//Postdecrement
				Iterator operator -- (int){
					Iterator old( * this);
					--(*(this));
					return old;
				}
				//Dereference
				ValueType & operator * () const{
					return cur->data;
				}
				//Special member access
				ValueType * operator -> (){
					return &(cur->data);
				}
				//Equality operators
				friend inline bool operator == (const Iterator & lhs, const Iterator & rhs){
					return (lhs.cur == rhs.cur && lhs.map->head == rhs.map->head);
				}
				//friend inline bool operator == (const Iterator & lhs, const ConstIterator & rhs){}
				//friend inline bool operator == (const ConstIterator & lhs, const Iterator & rhs){}
				//friend inline bool operator == (const ConstIterator & lhs, const ConstIterator & rhs){}			
				//Inequality operators	
				friend inline bool operator != (const Iterator & lhs, const Iterator & rhs){
					return !(lhs == rhs);
				}
				//friend inline bool operator != (const Iterator & lhs, const ConstIterator & rhs){}
				//friend inline bool operator != (const ConstIterator & lhs, const Iterator & rhs){}
				//friend inline bool operator != (const ConstIterator & lhs, const ConstIterator & rhs){}

				friend std::ostream& operator <<(std::ostream& os, const Iterator & it){
					os << "Key: " << it.first << " Value: " << it.second;
					return os;
				}
				Key first;
				Mapped second;
				private:
				Map * map;
				Node * cur;
			};

			//Data members that should be private eventually
			Node ** head;
			Node * tail;
			size_t length;

			/*	--------------------------------------------------------
			 *	Map specific functions 
			 */

			//Default Constructor
			Map(){
				srand(time(NULL));
				head = new Node * [MAX_HEIGHT];
				tail = NULL;
				length = 0;
			}
			//Copy Constructor
			Map(const Map & m){
				//TODO
				this->head = m.head;
			}
			//Assignment operator
			Map & operator = (const Map & m){
				//TODO
				this->head = m.head;
			}
			//Initializer list Constructor
			Map(std::initializer_list<std::pair<const Key, Mapped>> l){
				//TODO
				for(auto it = l.begin(); it != l.end(); it++){
					std::cout << (*it).first << ": " << (*it).second << std::endl;
				}

			}
			//Destructor
			~Map(){
				//Has at least one element
				Node * curr = (head->forward[0]);
				if(curr != NULL){
					while(curr->forward[0] != NULL){
						Node * temp = curr->forward[0];
						delete curr;
						curr = temp;
					}

					delete curr;
				}
				delete head;
			}

			//Operators
			Mapped & operator [] (const Key & key){
				//TODO
				Iterator ele = this->find(key);



			}

			//Housekeeping information
			size_t size(){
				return length;
			}
			bool empty(){
				return !length;
			}
			friend bool operator==(const Map &, const Map &){}
			friend bool operator!=(const Map &, const Map &){}
			friend bool operator<(const Map &, const Map &){}

			//Iterator methods
			Iterator begin(){
				Iterator i;
				i.map = this;
				i.cur = (head->forward[0]);
				i.first = i.cur->data.first;
				i.second = i.cur->data.second;

				return i;
			}
			Iterator end(){
				Iterator i;
				i.map = this;
				i.cur = NULL;
				//i.cur->back = tail;
				i.first = Key();
				i.second = Mapped();

				return i;
			}
			//TODO:
			//ConstIterator begin() const{}
			//ConstIterator end() const{}
			//TODO:
			//ReverseIterator rbegin(){}
			//ReverseIterator rend(){}

			Node ** findNode(Key k){
				static Node * ret [MAX_HEIGHT];
/*
				Node * currNode = NULL;
				for(int i = MAX_HEIGHT - 1; i >=0; --i){
					if(head[i] != NULL){
						currNode = head[i];
						break;
					}
				}
				
				if(currNode == NULL){
					std::cout << "inserting first into list" << std::endl;
					return head;
				}
*/			
				Node ** currNode = head;	
				for(int i = MAX_HEIGHT-1; i >= 0; --i)
				{
					while(currNode[i] != NULL && ((currNode->forward[i])->data.first < k))
					{
						currNode = (currNode->forward[i]);
					}
					ret[i] = currNode;
				}
				return ret;
			}	

			std::pair<Iterator, bool> insert(const ValueType& t){
				Node * newNode = new Node(t);

				//Get the node right before we want to insert
				Node ** update = findNode(t.first);
				//Check if pointing to a node that already exists with the key
				if (update == head){
					for(int i = newNode->height - 1; i>=0; i--)
					{
						newNode->forward[i] = update[i];
						update[i] = newNode;
					}
				}else if(update[0]->forward[0] != NULL && update[0]->forward[0]->data.first == t.first){
					return std::make_pair(Iterator(this, update[0]->forward[0]), false);
				}

				//If gotten to this point, continue on with regular insert
				for(int i = newNode->height - 1; i>=0; i--)
				{
					newNode->forward[i] = (update[i])->forward[i];
					(update[i])->forward[i] = newNode;
				}

				//Update the back ref
				newNode->back = update[0];

				//Update the maps tail and the length
				if(tail == NULL){
					tail = newNode;
				}else if(tail->data.first < t.first){
					tail = newNode;
				}
				length++;

				return std::make_pair(Iterator(this, newNode), true);	
			}			

			void erase(Iterator pos){
				//TODO
				//this->delete(pos.first)
				Iterator i = pos;
			}
			void erase(const Key key){
				//TODO
				//this->delete(key)
				Key k = key;
			}	
			Iterator find(const Key & k){
				Node * previous = (findNode(k)[0]);
				if(previous == tail) return end();
				if(previous != NULL && previous->forward[0] != NULL)
				{
					Node * match = previous->forward[0];
					if(match->data.first == k){
						return Iterator(this, match);
					}else{
						return end();	
					}	
				}else{
					return end();
				}

			}
			//ConstIterator find(const Key & k) const{}





			};
			/* Old stuff
				 template<class Key, class Mapped>
				 using ValueType = typename Map<Key, Mapped>::ValueType;

				 template<class Key, class Mapped> 
				 using Iterator = typename Map<Key, Mapped>::Iterator;

				 template<class Key, class Mapped> 
				 using ConstIterator = typename Map<Key, Mapped>::ConstIterator;

				 template<class Key, class Mapped> 
				 using ReverseIterator = typename Map<Key, Mapped>::ReverseIterator;

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
			 */

	}


#endif //MAP_HH
