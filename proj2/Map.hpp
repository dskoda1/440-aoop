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
				int height = 0;
				BaseNode ** forward;
				BaseNode * back;

				BaseNode(){};
				//Destructor
				~BaseNode(){
					delete [] forward;
				}
				BaseNode(int heightIn){
					height = heightIn;
					forward = new BaseNode * [heightIn];
					for(int i = 0; i < heightIn; i++){
						forward[i] = NULL;
					}
				}	
			};
			/*	----------------------------------------------------
			 *	Internal Node class
			 */
			class Node : public BaseNode{
				friend class Map;
				public:

				//Default constructor
				Node(){
				}
				//Destructor
				~Node(){
					//delete [] forward;
				}
				//Explicit height constructor
				/*Node(int heightIn){
					height = heightIn;
					forward = new BaseNode * [heightIn];
					for(int i = 0; i < heightIn; i++){
					forward[i] = 0;
					}
					}
				 */
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
					this->forward = new BaseNode *[height];
					for(int i = 0; i < height; i++){
						this->forward[i] = 0;
					}
					return;
				}
				//Data members 
				int height;
				ValueType data;
				//Key first;
				//Mapped second;
			};
			class ConstIterator{
				friend class Map;
				friend class Iterator;
				public:
				//Constructors
				//Iterator(){}
				//Copy constructor: implicit
				//Assignment operator: implicit
				//Destructor: implicit
				//Explicit value constructor
				ConstIterator(const Map * mapIn, BaseNode* curIn) : map(mapIn), cur(curIn){}	
				//Preincrement
				ConstIterator & operator ++ (){
					if((cur->forward[0]) != NULL){
						cur = static_cast<Node*>(cur->forward[0]);	
					}else{
						cur = nullptr;
					}
					return *(this);
				}
				//Postincrement
				ConstIterator operator ++ (int){
					ConstIterator old( * this);
					++(*(this));
					return old;	
				}
				//Predecrement
				ConstIterator & operator -- (){
					if(cur !=  NULL){
						cur = (cur->back);
					}else{
						cur = map->tail;
					}
					return *(this);
				}
				//Postdecrement
				ConstIterator operator -- (int){
					ConstIterator old( * this);
					--(*(this));
					return old;
				}
				//Dereference
				const ValueType & operator * () const{
					return static_cast<Node*>(cur)->data;
				}
				//Special member access
				const ValueType * operator -> (){
					return &(static_cast<Node*>(cur)->data);
				}
				friend inline bool operator == (const ConstIterator & lhs, const ConstIterator & rhs){
					return (lhs.cur == rhs.cur && lhs.map->head == rhs.map->head);
				}			
				friend inline bool operator != (const ConstIterator & lhs, const ConstIterator & rhs)
				{
					return !(lhs == rhs);
				}

				friend std::ostream& operator <<(std::ostream& os, const ConstIterator & it){
					os << "Key: " << (*it).first << " Value: " << (*it).second;
					return os;
				}
				private:
				const Map * map;
				BaseNode * cur;
			};


			class Iterator{
				friend class Map;
				friend class ConstIterator;
				public:
				//Constructors
				//Iterator(){}
				//Copy constructor: implicit
				//Assignment operator: implicit
				//Destructor: implicit
				//Explicit value constructor
				Iterator(Map * mapIn, BaseNode* curIn) : map(mapIn), cur(curIn){}	
				//Preincrement
				Iterator & operator ++ (){
					if((cur->forward[0]) != NULL){
						cur = static_cast<Node*>(cur->forward[0]);	
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
					}else{
						cur = map->tail;
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
					return static_cast<Node*>(cur)->data;
				}
				//Special member access
				ValueType * operator -> (){
					return &(static_cast<Node*>(cur)->data);
				}
				//Equality operators
				friend inline bool operator == (const Iterator & lhs, const Iterator & rhs){
					return (lhs.cur == rhs.cur && lhs.map->head == rhs.map->head);
				}
				friend inline bool operator == (const Iterator & lhs, const ConstIterator & rhs){
					return (lhs.cur == rhs.cur && lhs.map->head == rhs.map->head);

				}
				friend inline bool operator == (const ConstIterator & lhs, const Iterator & rhs){
					return (lhs.cur == rhs.cur && lhs.map->head == rhs.map->head);
				}
				//Inequality operators	
				friend inline bool operator != (const Iterator & lhs, const Iterator & rhs){
					return !(lhs == rhs);
				}
				friend inline bool operator != (const Iterator & lhs, const ConstIterator & rhs){
					return !(lhs == rhs);
				}
				friend inline bool operator != (const ConstIterator & lhs, const Iterator & rhs){
					return !(lhs == rhs);
				}
				friend std::ostream& operator <<(std::ostream& os, const Iterator & it){
					os << "Key: " << (*it).first << " Value: " << (*it).second;
					return os;
				}
				private:
				Map * map;
				BaseNode * cur;
			};

			//Data members that should be private eventually
			BaseNode * head;
			Node * tail;
			size_t length;

			/*	--------------------------------------------------------
			 *	Map specific functions 
			 */

			//Default Constructor
			Map(){
				srand(time(NULL));
				head = new BaseNode(MAX_HEIGHT);
				tail = NULL;
				length = 0;
			}
			//Copy Constructor
			Map(const Map & m){
				this->head = new BaseNode(MAX_HEIGHT);
				for(auto it= m.begin(); it != m.end(); ++it){
					this->insert(*it);
				}
				this->tail = m.tail;
				this->length = m.length;

			}
			//Assignment operator
			Map & operator = (const Map & m){
				//TODO
				assert(false);
				this->head = m.head;
			}
			//Initializer list Constructor
			Map(std::initializer_list<std::pair<const Key, Mapped>> l){
				//TODO
				assert(false);
				for(auto it = l.begin(); it != l.end(); it++){
					std::cout << (*it).first << ": " << (*it).second << std::endl;
				}

			}
			//Destructor
			~Map(){
				//Has at least one element
				BaseNode * curr = head->forward[0];
				if(curr != NULL){
					while(curr->forward[0] != NULL){
						BaseNode * temp = curr->forward[0];
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

				assert(false);


			}

			//Housekeeping information
			size_t size(){
				return length;
			}
			bool empty(){
				return !length;
			}
			friend bool operator==(const Map &, const Map &){}
			friend bool operator!=(const Map & l, const Map & r){}
			friend bool operator<(const Map &, const Map &){}

			//Iterator methods
			Iterator begin(){
				return Iterator(this, head->forward[0]);
			}
			Iterator end(){
				return Iterator(this, NULL);
			}
			//TODO:
			ConstIterator begin() const{
				return ConstIterator(this, head->forward[0]);
			}
			ConstIterator end() const{
				return ConstIterator(this, NULL);
			}
			//TODO:
			//ReverseIterator rbegin(){}
			//ReverseIterator rend(){}

			BaseNode ** findNode(Key k)const {
				static BaseNode * ret [MAX_HEIGHT];

				BaseNode * currNode = head;
				for(int i = MAX_HEIGHT-1; i >= 0; i--)
				{
					while(currNode->forward[i] != NULL && (static_cast<Node*>(currNode->forward[i])->data.first < k))
					{
						currNode = currNode->forward[i];
					}
					ret[i] = currNode;
				}
				return ret;
			}	

			std::pair<Iterator, bool> insert(const ValueType& t){

				//Get the node right before we want to insert
				BaseNode ** update = findNode(t.first);
				//Check if pointing to a node that already exists with the key
				if(update[0]->forward[0] != NULL && static_cast<Node*>(update[0]->forward[0])->data.first == t.first){
					return std::make_pair(Iterator(this, static_cast<Node*>(update[0]->forward[0])), false);
				}
				Node * newNode = new Node(t);
		
				//If gotten to this point, continue on with regular insert
				for(int i = newNode->height - 1; i>=0; i--)
				{
					newNode->forward[i] = update[i]->forward[i];
				
					//Only at bottom level update back pointer
					if(i == 0 && update[i]->forward[i] != NULL){
						update[i]->forward[i]->back = newNode;
					}
					update[i]->forward[i] = newNode;
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
				assert(false);

			}
			void erase(const Key key){
				//TODO
				assert(false);
				//this->delete(key)
				Key k = key;
			}	
			Iterator find(const Key & k){
				Node * previous = static_cast<Node*>(findNode(k)[0]);
				if(previous == tail) return end();
				if(previous != NULL && previous->forward[0] != NULL)
				{
					Node * match = static_cast<Node*>(previous->forward[0]);
					if(match->data.first == k){
						return Iterator(this, match);
					}else{
						return end();	
					}	
				}else{
					return end();
				}

			}
			ConstIterator find(const Key & k) const{
				Node * previous = static_cast<Node*>(findNode(k)[0]);
				if(previous == tail) return end();
				if(previous != NULL && previous->forward[0] != NULL)
				{
					Node * match = static_cast<Node*>(previous->forward[0]);
					if(match->data.first == k){
						return ConstIterator(this, match);
					}else{
						return end();	
					}	
				}else{
					return end();
				}


			}





			};

	}


#endif //MAP_HH
