#Project 1

##Implement a deque template using a macro
###Do this with a circular array

####To compile:

clang++ -g -std=c++11 -Wall -Wextra -pedantic test.cpp -ldl -O -o test

##Current Deque struct data members


####Array housekeeping

#####For the front array:
	int * frontArr
	int * ffp
	int * fbp
	int frontSize
	int maxFrontSize

#####For the back array:
	int * backArr
	int * bfp
	int * bbp
	int backSize
	int maxBackSize	

####Other members:
	(char * ?) type_name

####Methods

1.	int size(): returns the current number of elements
			-needs to return frontSize + backSize
done

2.	bool empty(): returns whether or not the deque is empty
			-needs to check if frontSize + backSize == 0
done

3.	void pushBack(): pushes an element onto the back array
			-needs to put an element where bbp points to
			-needs to increment bbp
			-needs to increment frontSize
			-check for frontSize/maxFrontSize > 0.9
				-call subroutine to realloc
done minus realloc

4.	void pushFront(): pushes an element onto the front array
			-needs to put an element where ffp points to
			-needs to increment ffp
			-needs to increment backSize
			-check if 
			-check for backSize/maxBackSize > 0.9
				-call subroutine to realloc
done minus realloc

5.	int front(): get the element at the front
			-return the element ffp points to
done

6.	int back():	get the element at the back
			-return the element bbp points to
done

7.	int at(index): get the element at the index
			-Case one: front and back are empty
				-return 0?
			-Case two: front has elements, back is empty
				-check if frontSize > val
					-true, return ffp + (sizeof(int) * val)
					-false, return 0?
			-Case three: front is empty, back has elements
				-check if backSize > val
					-true, return bfp + (sizeof(int) * val)
					-false, return 0?
			-Case four: Both have elements
				-check if (backSize + frontSize) > val
					-true: check if frontSize > val
						-true, return ffp + (sizeof(int) * val)
						-false, return bfp + (sizeof(int) * (val - frontSize))
					-false: return 0?

8.	void popBack(): pop an element off the back
			-needs to decrement bbp
			-needs to decrement backSize

9.	void popFront(): pop an element off the front
			-needs to decrement ffp
			-needs to decrement frontSize

10. void clear():	clear the deque
			-needs to move ffp to = fbp
			-needs to make frontSize = 0
			-needs to move bbp to = bfp
			-needs to make backSize = 0

11. void dtor(): destroy the deque
			-needs to free the front array
			-needs to free the back array
			-needs to free the type_name ??

12. reallocSubroutine(int * arr, int currSize): enlarge the array passed
			-needs to call realloc on arr, with size = currSize * 2






























