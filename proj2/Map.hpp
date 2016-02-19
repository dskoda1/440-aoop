#ifndef MAP_HPP
#define MAP_HPP

#define MAX_HEIGHT 32

//Includes
#include <iostream>
#include <vector>
//using namespace std;

namespace cs540{
	template <class Key, class Mapped> class Map{

		public:

			//Access key with .first, value with .second
			typedef std::pair<Key, Mapped> ValueType;

		private:
			struct Node_base {
					Node_base * next, * prev;
					Node_base() {}
			};
			struct Node : Node_base {
				Node() {};
				Node(const ValueType & v) : val(v){}
				ValueType val;
				Node_base * forwards;

			};

			Node * sentinel;



		public:
			//Constructors
			Map();
			Map(const Map & m);
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
			class Iterator{
				public:
					
					ValueType & operator * () const;
					Iterator & operator = (const Iterator & i) {}
					Node_base * cur;
					
					//Iterator constructIter();
				private:
			};

			class ConstIterator{
				public:
				private:
					ConstIterator();
			};

			class ReverseIterator{
				public:
				private:
					ReverseIterator();
			};
			//Iterator methods
			Iterator begin();
			Iterator end();

			ConstIterator begin() const;
			ConstIterator end() const;

			ReverseIterator rbegin();
			ReverseIterator rend();
	};

	/*
	 *	Some common typedefs for use in methods section
	 */
	template<class Key, class Mapped>
		using ValueType = typename Map<Key, Mapped>::ValueType;

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
	 * Default constructor
	 */ 
	template<class Key, class Mapped> 
		Map<Key, Mapped>::Map(){
			sentinel = new Node();
			sentinel->forwards = new Node_base[MAX_HEIGHT];
	}


	/*
	 *	Copy Constructor
	 */
	template<class Key, class Mapped> 
		Map<Key, Mapped>::Map(const Map & m){

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
			Mapped x;
			return x;
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
	template<class Key, class Mapped> bool Map<Key, Mapped>::empty(){
		return false;
	}




	/*
	 *	Iterator Class methods
	 *	----------------------
	 *	Typedefs for iterator classes
	 *
	 */
	template<class Key, class Mapped> 
		using Iterator = typename Map<Key, Mapped>::Iterator;

	template<class Key, class Mapped> 
		using ConstIterator = typename Map<Key, Mapped>::ConstIterator;

	template<class Key, class Mapped> 
		using ReverseIterator = typename Map<Key, Mapped>::ReverseIterator;

	/*
	 *	Regular Iterator functions
	 */
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

	//Dereference operator overload
	template<class Key, class Mapped> 
		ValueType<Key, Mapped> & Map<Key, Mapped>::Iterator::operator *()const {
			//return static_cast<Map<Key, Mapped>::Node * > (this->cur) ->val ;
		}









}


#endif //MAP_HH
