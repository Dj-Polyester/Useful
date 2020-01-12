#ifndef STRING
#define STRING

#include <iostream>
#include <string.h>

class String
{
private:
    char* str_data;
public:
    String(const char* str=NULL);
    String(const String& other);
    ~String();
    void print();
    String& operator = (const char* &str);
    String& operator = (const String &str);
    
    String operator + (const String& str1,const char*& str2);
    String operator + (const String& str1,const String& str2);
 /*   String operator + (const char*& str1,const String& str2);
    String operator + (const char*& str1,const char*& str2);*/

    //friend method, to access private variables of std class
    friend std::ostream& operator<<(std::ostream& out, const String &str);
    char* data() const {return str_data;}
    void set_data(const char* str);
};

#endif