#ifndef ARRAY_2
#define ARRAY_2



namespace cs540{

  class Array2{
    private:
      int height;
      int width;

      int ** data;



    public:
      class Iterator {
        public:
        Iterator(){}
        Iterator(Array2 * arr, int i): array(arr), index(i){}

        //Increment/decrement
        Iterator & operator ++ (){
          index++;
          return *(this);
        }
        Iterator operator ++ (int){
          Iterator old( * this);
          ++(*(this));
          return old;
        }
        //Dereference
        int & operator * () const{

          if(index == 0) return (*array)[0][0];

          int * row = (*array)[index / (array->width)];
          return row[index % (array->width)];
        }

        bool operator == (const Iterator rhs){
          return (this->index == rhs.index);
        }

        bool operator != (const Iterator rhs){
          return !((*this) == rhs);
        }

        private:
        Array2 * array;
        int index;

      };      


      Array2(int heightIn, int widthIn): height(heightIn), width(widthIn){
        data = new int * [heightIn];
        for(int i = 0; i < heightIn; ++i){
          data[i] = new int [widthIn];
        }
      }

      ~Array2(){
        for(int i = height - 1; i >0; --i){
          delete data[i];
        }
        delete data;

      }
      int* operator [](const int i){
        return data[i];
      }

      Iterator begin(){
        Iterator i(this, 0);
        return i; 
      }
      Iterator end(){
        Iterator i(this, width * height);
        return i;
      }

  };

}

#endif //ARRAY_2
