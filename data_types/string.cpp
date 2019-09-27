#include "string.h"

using namespace std;

void String::set_data(const char* str)
{
    delete [] str_data;
    size_t length=strlen(str);
    str_data = new char[length];
    strcpy(str_data,str);
}

String String::operator + (const String& str)
{
    char* tmp;
    String tmp_str;
    
    size_t length_curr=strlen(str_data);
    size_t length_next=strlen(str.data());
   
    tmp = new char[length_curr+length_next];
    
    strcpy(tmp,str_data);
    strcat(tmp,str.data());
    
    tmp_str.set_data(tmp);

    return tmp_str; 
}

//reference variables are aliasing variables 
void String::operator = (const char* &str)
{
    delete [] str_data;
    size_t length=strlen(str);
    str_data = new char[length];
    strcpy(str_data,str);
}

String::String(const char* str)
{
    if(str)
    {
        size_t length=strlen(str);
        str_data = new char[length];
        strcpy(str_data,str);
    }
    else
    {
        str_data=NULL;
    }
    
}

String::~String()
{
    delete [] str_data;
}

void String::print()
{
    std::cout << str_data << std::endl;
}

std::ostream& operator << (std::ostream& out, const String &str)
{
	out << str.str_data;
	return out;
}

int main()
{
    
    String str1="wassup man oy";
    String str2="yo man oy";

    String str3=str2+str1;
    
    
     //cout << str1 << endl;
     //cout << str2 << endl;
    cout << str3 << endl;

}
