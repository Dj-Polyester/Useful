#include <iostream>
#include "linkedlist.hpp"

using namespace std;

template <class T>
class Stack {

public:

    Stack(); // Default constructor; copy constructor and destructor are supplied by the compiler.
    ~Stack();
    bool isEmpty(); // Determines if stack is empty.

    void push(const T& newItem); // Adds an item to the top of a stack.

    T pop(); // Removes and returns the top of a stack.

    T peek(); // Retrieves top of stack.
    
    int size() const {return stack.len;}; // Returns the number of items in stack.

    list<T>& get_stack() {return stack;};

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const list<U> &List);
private:
    list<T> stack; // array of stack items
};




