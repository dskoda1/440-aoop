#ifndef MAP_HPP
#define MAP_HPP

//Includes
#include <iostream>
using namespace std;

namespace cs540{
	template <class Key_T, class Mapped_T> class Map{


		private:

		public:
			//Constructors
			Map();
			Map(const Map & m);
			~Map();
			//TODO: typemember, the pair
			//Operators
			Map & operator = (const Map & m);
			Mapped_T & operator [] (const Key_T & key);
			//TODO: ==, !=, <
			//Housekeeping information
			size_t size();
			bool empty();

			/*
			 *	Nested iterator classes and methods
			 */
			class Iterator{
				friend Map;
				public:
				private:
				//Iterator();
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

	};

	/*
	 *	Methods section
	 *	----------------------------------------------------
	 *	All of the methods described in the requirements are 
	 *	implemented below as the api of this class.
	 * template<class Key_T, class Mapped_T> Map<Key_T, Mapped_T>::
	 */

	/*
	 * Default constructor
	 */ 
	template<class Key_T, class Mapped_T> Map<Key_T, Mapped_T>::Map(){
	}


	/*
	 *	Copy Constructor
	 */
	template<class Key_T, class Mapped_T> Map<Key_T, Mapped_T>::Map(const Map & m){

	}


	/*
	 *	Destructor
	 */
	template<class Key_T, class Mapped_T> Map<Key_T, Mapped_T>::~Map(){

	}


	/*
	 *	Assignment operator
	 */
	template<class Key_T, class Mapped_T> Map<Key_T, Mapped_T> &  Map<Key_T, Mapped_T>::operator=(const Map & m){

		return m;
	}


	/*
	 *	Bracket operator
	 */
	template<class Key_T, class Mapped_T> Mapped_T & Map<Key_T, Mapped_T>::operator[](const Key_T & key){
		Mapped_T x;
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
	template<class Key_T, class Mapped_T> size_t Map<Key_T, Mapped_T>::size(){
		return 0;
	}


	/*
	 *	Empty: returns whether or not the map is empty
	 */
	template<class Key_T, class Mapped_T> bool Map<Key_T, Mapped_T>::empty(){
		return false;
	}




	/*
	 *	Iterator Class methods
	 *	----------------------
	 */
	template<class Key_T, class Mapped_T> typename Map<Key_T, Mapped_T>::Iterator Map<Key_T, Mapped_T>::begin(){
		Iterator i;
		return i;
	}












}


#endif //MAP_HH
