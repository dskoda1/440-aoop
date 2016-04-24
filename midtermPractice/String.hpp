#ifndef STRING_H
#define STRING_H

#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <string.h>
namespace cs540{

  class String{
    private:
      char * data;


    public:
      String(){
        data = strdup("");
      }
      //String(char * dataIn): data(strdup(dataIn)){}
      String(std::string dataIn): data(strdup(dataIn.c_str())){}

      String(const String & sIn){
        data = sIn.data;
      }


      String & operator = (const String & sIn){
        if (&sIn == this){
          return *this;
        }

        data = sIn.data;
        return *this;
      }

      friend std::ostream & operator << (std::ostream& os, const String & sIn){
          os << (std::string)sIn.data; 

        return os;

      }

      char & operator [](int i){
        return data[i];

      }
      String & operator + (std::string cIn){
        strcat(data, cIn.c_str());
        return *this;
      }

      friend char *  operator + (const String & s1, const String & s2){
        char * newS = new char [strlen(s1.data) + strlen(s2.data)];
        strcat(newS, s1.data);
        strcat(newS, s2.data);
        return newS;

      }

  };




}

#endif //STRING_H
