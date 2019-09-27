#ifndef COMPLEX
#define COMPLEX

#include <iostream>
#include <cmath>

class Complex
{
    private:
        float im, re;
    public:
        Complex(float x=0,float y=0): re(x),im(y) {}

        Complex operator + (Complex const &obj);
        Complex operator - (Complex const &obj);
        Complex operator * (Complex const &obj);
        Complex operator / (Complex const &obj);
        friend std::ostream& operator<<(std::ostream& out, const Complex &str);
        float distance() const {return sqrt(im*im+re*re);}
        void print();
};

#endif