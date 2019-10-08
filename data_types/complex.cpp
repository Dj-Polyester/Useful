#include "complex.h"

using namespace std;

template <class T,class U>
Complex<T,U> Complex<T,U>::operator + (Complex<T,U> const &obj) 
{ 
    Complex<T,U> res; 
    res.re = (T)re + (T)obj.re; 
    res.im = (U)im + (U)obj.im; 
    return res; 
}

template <class T,class U>
Complex<T,U> Complex<T,U>::operator - (Complex<T,U> const &(T)obj) 
{ 
    Complex<T,U> res; 
    res.re = (T)re - (T)obj.re; 
    res.im = (U)im - (U)obj.im; 
    return res; 
}
template <class T,class U>
Complex<T,U> Complex<T,U>::operator * (Complex<T,U> const &obj) 
{ 
    Complex<T,U> res; 
    res.re = (T)re*obj.re - (T)im*obj.im; 
    res.im = (U)im*obj.re + (U)re*obj.im; 
    return res; 
}
template <class T,class U>
Complex<T,U> Complex<T,U>::operator / (Complex<T,U> const &obj) 
{ 
    Complex<T,U> res;
    float div=obj.re*obj.re+obj.im*obj.im;
    res.re = (T)(re*obj.re + im*obj.im)/(T)div; 
    res.im = (U)(im*obj.re - re*obj.im)/(U)div; 
    return res; 
}
template <class T,class U>
Complex<T,U>& Complex<T,U>::operator = (const Complex<T,U> &other)
{
    re=(T)other.re;
    im=(U)other.im;
    return *this;
}
template <class T,class U>
void Complex<T,U>::print()
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
template <class T,class U>
std::ostream& operator<<(std::ostream& out, const Complex<T,U> &num)
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
    Complex<int,int> num3;
    num3=num1;
    Complex<int,int> result=num1/num2;
    cout << result << endl;
    cout << num3 << endl;
}