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
		//Access key with .first, value with .second
		typedef std::pair<Key, Mapped> ValueType;

		private:

		/*	----------------------------------------------------
		 *	Internal Node class
		 */
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
		class Node : private BaseNode{
			friend class Map;
			public:

			//Default constructor
			Node() = delete;
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

			public:
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
		class ReverseIterator{
			friend class Map;
			public:
			//Constructors
			//Iterator(){}
			//Copy constructor: implicit
			//Assignment operator: implicit
			//Destructor: implicit
			//Explicit value constructor
			ReverseIterator(Map * mapIn, BaseNode* curIn) : map(mapIn), cur(curIn){}	
			//Preincrement
			ReverseIterator & operator ++ (){
				if((cur->back) != NULL){
					cur = static_cast<Node*>(cur->back);	
				}else{
					cur = nullptr;
				}
				return *(this);
			}
			//Postincrement
			ReverseIterator operator ++ (int){
				ReverseIterator old( * this);
				++(*(this));
				return old;	
			}
			//Predecrement
			ReverseIterator & operator -- (){
				if(cur == map->head){
					cur = map->head->forward[0];
				}else{
					cur = cur->forward[0] ;
				}
				return *(this);
			}
			//Postdecrement
			ReverseIterator operator -- (int){
				ReverseIterator old( * this);
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
			friend inline bool operator == (const ReverseIterator & lhs, const ReverseIterator & rhs){
				return (lhs.cur == rhs.cur && lhs.map->head == rhs.map->head);
			}
			//Inequality operators	
			friend inline bool operator != (const ReverseIterator & lhs, const ReverseIterator & rhs){
				return !(lhs == rhs);
			}
			friend std::ostream& operator <<(std::ostream& os, const ReverseIterator & it){
				os << "Key: " << (*it).first << " Value: " << (*it).second;
				return os;
			}
			private:
			Map * map;
			BaseNode * cur;
		};


		/*	--------------------------------------------------------
		 *	Map specific functions 
		 */
			public:
		//Default Constructor
		Map(){
			head = new BaseNode(MAX_HEIGHT);
			tail = NULL;
			length = 0;
		}
		//Copy Constructor
		Map(const Map & m){
			this->head = new BaseNode(MAX_HEIGHT);
			this->tail = NULL;
			this->length = 0;
			for(auto it= m.begin(); it != m.end(); ++it){
				this->insert(*it);
			}

		}
		//Assignment operator
		Map & operator = (const Map & m){
			this->head = new BaseNode(MAX_HEIGHT);
			this->tail = NULL;
			this->length = 0;
			for(auto it = m.begin(); it != m.end(); ++it){
				this->insert(*it);
			}
			return *this;
		}
		//Initializer list Constructor
		Map(std::initializer_list<std::pair<const Key, Mapped>> l){
			//Initialize housekeeping element
			this->head = new BaseNode(MAX_HEIGHT);
			this->tail = NULL;
			this->length = 0;
			for(auto it = l.begin(); it != l.end(); it++){
				this->insert(*it);			

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

		size_t size() const{
			return length;
		}
		bool empty() const{
			return !length;
		}

		//Iterator methods
		Iterator begin(){
			return Iterator(this, head->forward[0]);
		}
		Iterator end(){
			return Iterator(this, NULL);
		}
		ConstIterator begin() const{
			return ConstIterator(this, head->forward[0]);
		}
		ConstIterator end() const{
			return ConstIterator(this, NULL);
		}
		ReverseIterator rbegin(){
			return ReverseIterator(this, tail);
		}
		ReverseIterator rend(){
			return ReverseIterator(this, head);
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

		Mapped & at(const Key & k){

			auto it = this->find(k);
			if(it == this->end()){
				throw std::out_of_range("Key not found in call to Map::at");
			}else{
				return it->second;
			}

		}

		const Mapped & at(const Key & k) const {
			auto it = this->find(k);
			if(it == this->end()){
				throw std::out_of_range("Key not found in call to Map::at");
			}else{
				return it->second;
			}


		}

		Mapped & operator [] (const Key & key){
			return this->insert(std::make_pair(key, Mapped{})).first->second;
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
		template <typename IT_T>
			void insert(IT_T range_beg, IT_T range_end){
				for(auto it = range_beg; it != range_end; ++it){
					this->insert(*it);
				}
			}
		void erase(Iterator pos){
			this->deleteKey(pos->first);
		}
		void erase(const Key key){
			this->deleteKey(key);
		}	

		void clear (){
			while(begin() != end()){
				erase(begin());
			}
		}

		bool operator==(const Map & r){
			if(this->length == r.length){
				auto it = this->begin();
				auto rit = r.begin();
				for( ; it != this->end(); ++it, ++rit){
					if((*it) != (*rit)){
						return false;
					}
				}	
				return true;	
			}else{
				return false;
			}
		}
		bool operator!=(const Map & r){
			return !((*this) == r);
		}
		bool operator<(const Map & rhs){
			auto lit = this->begin();
			auto rit = rhs.begin();

			for(;lit != this->end() && rit != rhs.end(); ++lit, ++rit){
				if((*lit) == (*rit)){
					continue;
				}else if((*lit) < (*rit)){
					return true;	
				}else{
					return false;
				}
			}

			//Gotten to this point so either one is shorter or theyre all equal
			if(lit == this->end() && rit != rhs.end()){
				return true;
			}else if(lit != this->end() && rit == rhs.end()){
				return false;
			}else{
				return false;
			}
		}

			private:
		//Data members that should be private eventually
		BaseNode * head;
		Node * tail;
		size_t length;

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

		void deleteKey(Key k){
			BaseNode ** update = findNode(k);

			//Ensure update[0]->forward[0] is pointing the the node with key marked for delete
			if(update[0]->forward[0] != NULL && !(static_cast<Node*>(update[0]->forward[0])->data.first == k)){
				throw std::out_of_range("No key found");
			}
			//Save a pointer to this node first
			Node * del = static_cast<Node*>(update[0]->forward[0]);
			//Go through each of the nodes pointer and assign them backwards
			for(int i = del->height - 1; i>=0; i--){
				update[i]->forward[i] = del->forward[i];
			}	
			//Update back pointer
			//Might need null check

			if(tail == del){
				tail = static_cast<Node*>(del->back);
			}else if(update[0]->forward[0] != NULL){
				update[0]->forward[0]->back = del->back;
			}
			delete del;
			length--;
			return;
		}	
		};
	}


#endif //MAP_HH
