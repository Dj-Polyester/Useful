#include "string.h"

using namespace std;

void String::set_data(const char* str)
{
    delete [] str_data;
    size_t length=strlen(str);
    
    str_data = new char[length+1];
    str_data[length]='\0';

    cout << "line 13: " << (length+1)*sizeof(char) << endl;

    strcpy(str_data,str);
}


String operator + (const String& str1,const char*& str2)
{
    char* tmp;
    String tmp_str;
    
    size_t length_curr=strlen(str1.data());
    size_t length_next=strlen(str2);
    size_t length_total=length_curr+length_next;

    tmp = new char[length_total+1];
    tmp[length_total]='\0';

    cout << "line 31: " << (length_total+1)*sizeof(char) << endl;

    strcpy(tmp,str1.data());
    strcat(tmp,str2);

    tmp_str.set_data(tmp);

    delete[] tmp;

    return tmp_str; 
}

String operator + (const String& str1,const String& str2)
{
    char* tmp;
    String tmp_str;
    
    size_t length_curr=strlen(str1.data());
    size_t length_next=strlen(str2.data());
    size_t length_total=length_curr+length_next;

    tmp = new char[length_total+1];
    tmp[length_total]='\0';

    cout << "line 53: " << (length_total+1)*sizeof(char) << endl;

    strcpy(tmp,str1.data());
    strcat(tmp,str2.data());

    tmp_str.set_data(tmp);

    delete[] tmp;

    return tmp_str; 
}

/*
String String::operator + (const String& str)
{
    char* tmp;
    String tmp_str;
    
    size_t length_curr=strlen(str_data);
    size_t length_next=strlen(str.data());
    size_t length_total=length_curr+length_next;

    tmp = new char[length_total+1];
    tmp[length_total]='\0';
    
    cout << "line 76: " << (length_total+1)*sizeof(char) << endl;

    strcpy(tmp,str_data);
    strcat(tmp,str.data());

    tmp_str.set_data(tmp);

    return tmp_str; 
}
*/

//reference variables are aliasing variables 
String& String::operator = (const char* &str)
{
    delete [] str_data;
    size_t length=strlen(str);
    
    str_data = new char[length+1];
    str_data[length]='\0';

    cout << "line 96: " << (length+1)*sizeof(char) << endl;

    strcpy(str_data,str);

    return *this;
}

String& String::operator = (const String &str)
{
    delete [] str_data;
    str_data=NULL;
    size_t length=strlen(str.data());
    
    str_data = new char[length+1];
    str_data[length]='\0';

    cout << "line 112: " << (length+1)*sizeof(char) << endl;


    strcpy(str_data,str.data());

    return *this;
}

String::String(const char* str)
{
    if(str)
    {
        size_t length=strlen(str);
        
        str_data = new char[length+1];
        str_data[length]='\0';

            cout << "line 129: " << (length+1)*sizeof(char) << endl;


        strcpy(str_data,str);
    }
    else
    {
        str_data=NULL;
    }   
}

String::String(const String& other)
{
    if(other.str_data)
    {
        size_t length=strlen(other.str_data);
        
        str_data = new char[length+1];
        str_data[length]='\0';

        cout << "line 149: " << (length+1)*sizeof(char) << endl;


        strcpy(str_data,other.str_data);
    }
    else
    {
        str_data=NULL;
    }
}

String::~String()
{
    delete [] str_data;
    str_data=NULL;
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

    cout << str2 << endl;
    cout << str1 << endl;
    
    str1="yoman";
    str2="dhagd asdasdh";

    cout << str1 << endl;
    cout << str2 << endl;

    String str3=str2;

    cout << "str1 before "<< str3 << endl;
    cout << "str1 before "<<str1 << endl;
    cout << "str2 before "<<str2 << endl;
    
    str3=str1;
    
    cout << "str1 after "<< str3 << endl;
    cout << "str1 after "<<str1 << endl;
    cout << "str2 after "<<str2 << endl;
   

    str3=str1+str2;
    cout << "str1 after after"<< str3 << endl;
    cout << "str1 after after"<<str1 << endl;
    cout << "str2 after after"<<str2 << endl;

    String str4=str2;
    cout << str4 << endl;

    
    str4=str3+" anber";
    cout << str4 << endl;

    String str5="minber "+str4;
    cout << str5 << endl;
/*

    String str3=str2+str1;
    cout << "yey" <<endl;
    String str4=str2;
    cout << str1 << endl;
    cout << "yey1"<<endl;
    str4=str3;
    cout << str1 << endl;
    
     //cout << str1 << endl;
     //cout << str2 << endl;
    //cout << str3 << endl;
*/

    return 0;
}
