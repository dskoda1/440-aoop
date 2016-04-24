
#include <iostream>


namespace cs540{


  class HashTable{

    public:    
      class LinkedList{
        public:
          class Node{
            int val;
            Node * next;
          };
        

          LinkedList() : head(nullptr){}

      private:
          Node * head;
      };
  
      HashTable(){
        length = 20;
        

      }
    private:
      int length;
      LinkedList ll;

  };




}



