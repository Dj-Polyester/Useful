#include "Stack.hpp"

template <class T>
std::ostream& operator<<(std::ostream& out, Stack<T> &s)
{
    list<T> &curr=s.get_stack();
    cout << curr << endl;
}

template <class T>
Stack<T>::Stack()
{}
template <class T>
Stack<T>::~Stack()
{}

template <class T>
bool Stack<T>::isEmpty()// Determines if stack is empty.
{
    if(this->get_stack().head->next==this->get_stack().tail)
    {
        return true;
    }
    return false;
}

template <class T>
void Stack<T>::push(const T& newItem) // Adds an item to the top of a stack.
{
    this->get_stack().append(newItem);
}
template <class T>
T Stack<T>::pop() // Removes and returns the top of a stack.
{
    return this->get_stack().pop();
}
template <class T>
T Stack<T>::peek() // Retrieves top of stack.
{
    return (this->get_stack())[-1];
}
