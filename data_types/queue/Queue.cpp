#include "Queue.hpp"

template <class T>
std::ostream& operator<<(std::ostream& out, Queue<T> &q)
{
    list<T> &curr=q.get_queue();
    cout << curr << endl;
}

template <class T>
Queue<T>::Queue()
{}
template <class T>
Queue<T>::~Queue()
{}

template <class T>
bool Queue<T>::isEmpty() // Determines if stack is empty.
{
    if(this->get_queue().head->next==this->get_queue().tail)
    {
        return true;
    }
    return false;
}

template <class T>
void Queue<T>::enqueue(const T& newItem)  // Adds an item to the end of queue.
{
    this->get_queue().push(newItem);
}
template <class T>
T Queue<T>::dequeue() // Removes and returns the item at the beginning of queue.
{
    return this->get_queue().pop();
}
template <class T>
T Queue<T>::peek() // Returns the item at the beginning of queue without removing it.
{
    return (this->get_queue())[-1];
}


void mystery2(Queue<int>& q) {

        int size = q.size();

        for(int i = 0; i < size; i++) {

            int n = q.dequeue();

            if (n > 0)

                q.enqueue(-n);

        }

        while(!q.isEmpty())

            cout << q.dequeue() << " " ;

        cout << "#";

    }
