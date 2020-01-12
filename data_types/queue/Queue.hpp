
#include <iostream>
#include "linkedlist.hpp"

using namespace std;

template <class T>

class Queue {

public:

    Queue(); // Default constructor; copy constructor and destructor are supplied by the compiler.
    ~Queue();
    bool isEmpty(); // Determines if queue is empty.

    void enqueue(const T& newItem); // Adds an item to the end of queue.

    T dequeue(); // Removes and returns the item at the beginning of queue.

    T peek(); // Returns the item at the beginning of queue without removing it.

    int size() const {return queue.len;}; // Returns the number of items in queue.

    list<T>& get_queue() {return queue;};

    template <class U>
    friend std::ostream& operator<<(std::ostream& out, const list<U> &List);
private:
    list<T> queue; // array of queue items
};
