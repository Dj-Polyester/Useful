#ifndef COMPLEX
#define COMPLEX

#include <iostream>
#include <cmath>


template <class T,class U>
class Complex
{
    private:
        T re;
        U im;
    public:
        Complex(T x=0,U y=0): re(x),im(y) {}

        Complex operator + (Complex const &obj);
        Complex operator - (Complex const &obj);
        Complex operator * (Complex const &obj);
        Complex operator / (Complex const &obj);
        Complex& operator = (const Complex &other);
        friend std::ostream& operator<<(std::ostream& out, const Complex &str);
        float distance() const {return sqrt(im*im+re*re);}
        void print();
};

#endif