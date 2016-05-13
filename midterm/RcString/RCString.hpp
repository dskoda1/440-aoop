/*
 * This is a reference counted string implementation.  Two RcString objects
 * that have a common ancestor and contain the original string should point to
 * the same data object.  This provides very fast copies.
 *
 * You are not allowed to use std::string in this.
 */



#ifndef CS540_RC_STRING_HPP
#define CS540_RC_STRING_HPP
#include <iostream>
#include <string.h>
#include <stdlib.h>
namespace cs540 {


  class RCString {
    private:
      class stringData {
        friend class RCString;
        stringData(const char * sIn = "", int lengthIn = 0): data(strdup(sIn)), length(static_cast<int>(strlen(sIn) + 1)), refCount(1){}   

        ~stringData(){
          free(data);
        }

        int length;
        char * data;
        int refCount;
      };
    public:
      // Public methods.
      RCString(const char * sIn = ""){
        m_data = new stringData(sIn, strlen(sIn));
      }

      RCString(RCString & rcIn){
        ++rcIn.m_data->refCount;
        m_data = rcIn.m_data;
      }

      RCString(std::string && sIn){
        m_data = new stringData(sIn.c_str(), sIn.length());

      }

      RCString(RCString && rcIn){
        m_data = new stringData(rcIn.m_data->data, strlen(rcIn.m_data->data));
      }
 
      RCString & operator = (RCString & rcIn){
        delete m_data;
        ++rcIn.m_data->refCount;
        m_data = rcIn.m_data;
        return (*this);
      }

      RCString & operator = (RCString && rcIn){
          delete m_data;
         m_data = new stringData(rcIn.m_data->data, strlen(rcIn.m_data->data));
        return *this;
      }

      ~RCString() {
        // Delete the data object if the ref count goes to 0.
        if(--m_data->refCount == 0){
          delete m_data;
        }

      }
  
      RCString operator + (RCString & rcIn){
        RCString ret(*this);
        strcat(ret.m_data->data, rcIn.m_data->data);
        return ret;
      }

      RCString operator + (const char * rcIn){
        RCString ret(*this);
        strcat(ret.m_data->data, rcIn);
        return ret;

      }

      
      friend std::ostream& operator <<(std::ostream & os, const RCString & rc){
        os << rc.m_data->data;
        return os;
      }
    private:
      stringData *m_data;
  };



}



#endif
