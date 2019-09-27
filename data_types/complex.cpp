#include "complex.h"

using namespace std;

Complex Complex::operator + (Complex const &obj) 
{ 
    Complex res; 
    res.re = re + obj.re; 
    res.im = im + obj.im; 
    return res; 
}

Complex Complex::operator - (Complex const &obj) 
{ 
    Complex res; 
    res.re = re - obj.re; 
    res.im = im - obj.im; 
    return res; 
}
Complex Complex::operator * (Complex const &obj) 
{ 
    Complex res; 
    res.re = re*obj.re - im*obj.im; 
    res.im = im*obj.re + re*obj.im; 
    return res; 
}
Complex Complex::operator / (Complex const &obj) 
{ 
    Complex res;
    float div=obj.re*obj.re+obj.im*obj.im;
    res.re = (re*obj.re + im*obj.im)/div; 
    res.im = (im*obj.re - re*obj.im)/div; 
    return res; 
}

void Complex::print()
{        
    if(re!=0)
    {
        cout << re;
    }
    if(im>0)
    {
        cout << "+" << im << "i";
    }
    else if(im<0)
    {
        cout << im << "i";
    }        
}

std::ostream& operator<<(std::ostream& out, const Complex &num)
{
    if(num.re!=0)
    {
        out << num.re;
    }
    if(num.im>0)
    {
    if(num.im>0)
        cout << "+" << num.im << "i";
    }
    else if(num.im<0)
    {
        out << num.im << "i";
    }
    
	return out;
}

int main()
{
    Complex num1(3,5);
    Complex num2(2,-7);
    Complex result=num1/num2;
    cout << result;
}