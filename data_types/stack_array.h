#include <iostream>

template<class T>
class Stack
{
private:
    size_t Top;
    T* stack;
public:
    Stack();
    size_t length() const;
    bool isEmpty() const;
    void push(const T & item);
    T pop(); //removes and returns Top
    T top() const;
    ~Stack() { delete [] stack; }
    
    template<class U>
    friend std::ostream& operator<<(std::ostream& out, const Stack<U> &stack);
};

template<class T>
Stack<T>::Stack()
{
    Top=0;
    stack=new T[1];
    *stack=0;
}

template<class T>
size_t Stack<T>::length() const
{
    return Top;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const Stack<T> &el)
{
    size_t i=0;
    for(;i<el.Top;++i)
    {
        out << el.stack[i] << " ";
    }
    return out;
}

template<class T>
T Stack<T>::top() const
{
    return stack[Top-1];
}

template<class T>
T Stack<T>::pop()
{
    if (!Top)
    {
    	throw "pop from an empty stack"
    }

    T tmp_ret=stack[--Top];
    T* tmp=new T[Top];
    size_t i=0;
    for(;i<Top;++i)
    {
        tmp[i]=stack[i];
    }
    delete [] stack;
    stack=NULL;
    stack=new T[Top+1];
    i=0;
    for(;i<Top;++i)
    {
        stack[i]=tmp[i];
    }
    delete [] tmp;
    
    return tmp_ret;
}

template<class T>
bool Stack<T>::isEmpty() const
{
    return !Top;
}

template<class T>
void Stack<T>::push(const T & item)
{
    T* tmp=new T[Top];
    size_t i=0;
    for(;i<Top;++i)
    {
        tmp[i]=stack[i];
    }
    delete [] stack;
    stack=NULL;
    stack=new T[++Top+1];
    
    i=0;
    for(;i<Top-1;++i)
    {
        stack[i]=tmp[i];
    }
    delete [] tmp;
    stack[Top-1]=item;
}
