#include <iostream>

template <class T>
class linkedlist
{
    private:
        template <class U>
        class node
        {
            public:
                U data;
                node<U>* next;
                node(U x, node<U>* n): data(x), next(n) {}
                node(U x): data(x), next(NULL) {}
                node(): next(NULL) {}
        };
        std::ostream& print(std::ostream& out, const linkedlist<T> &List) const;
        node<T>* head;
        

    public:
        linkedlist();
        linkedlist(const linkedlist<T> &rhs);
        ~linkedlist();

        void insert(T data,int index);
        size_t insert_sorted(T data);
        
        void nremove(int index);
        void del();//clear the list completely

        template<class U>
        friend std::ostream& operator<<(std::ostream& out, const linkedlist<U> &List);

        T& operator[](size_t index);
        linkedlist<T>& operator=(const linkedlist<T> &rhs);
};

template <class T>
linkedlist<T>::linkedlist()
{
    head=NULL;
}

template <class T>
linkedlist<T>::~linkedlist()
{
    this->del();
}

template<class T>
size_t linkedlist<T>::insert_sorted(T val)
{
    int index=0;
    node<T>* curr=this->head, *pre=NULL;    
    if (curr)
    {
        while(curr && curr->data < val)
        {
            pre=curr;
            curr=curr->next;
            ++index;
        }

        node<T>* newnode = new node<T>(val, curr);
        if(pre) pre->next=newnode;
        else this->head=newnode;
    }
    else
    {
        node<T>* newnode = new node<T>(val);
        this->head=newnode;
    }
    
    return index;
}

template<class T>
void linkedlist<T>::insert(T data,int index)
{
    node<T>* curr=this->head,*pre=NULL;
    
    if (curr)
    {
        while (curr && index)
        {
            pre=curr;
            curr=curr->next;
            --index;
        }
        
        node<T>* newnode = new node<T>(data,curr);
        if(pre) pre->next=newnode;
        else this->head=newnode;
    }
    else
    {
        node<T>* newnode = new node<T>(data);
        this->head=newnode;
    }
}

template<class T>
void linkedlist<T>::del()
{
	while(this->head)
    {
        node<T>* curr=this->head;
        this->head=this->head->next;
        delete [] curr;
    }
}

template<class T>
void linkedlist<T>::nremove(int index)
{
    node<T>* curr=this->head, *pre=NULL;
    
    while (curr && index)
    {
        pre=curr;
        curr=curr->next;
        --index;
    }
    if (curr)
    {
        if(pre) pre->next=pre->next->next;
        else this->head=this->head->next;
        delete [] curr;
    }
}

template<class T>
std::ostream& linkedlist<T>::print(std::ostream& out, const linkedlist<T> &List) const
{
    node<T> *curr=List.head;
    
    while(curr)
    {
        out << curr->data << " ";
        curr=curr->next;         
    }

    return out;
}
template<class T>
std::ostream& operator<<(std::ostream& out, const linkedlist<T> &List)
{
    return List.print(out, List);
}

template<class T>
T& linkedlist<T>::operator[](size_t index)
{
    node<T>* curr=this->head,*pre=NULL;
    
    while (curr && index)
    {
        pre=curr;
        curr=curr->next;
        --index;
    }

    return curr->data;
}

template<class T>
linkedlist<T>::linkedlist(const linkedlist<T> &rhs)
{
    *this=rhs;
}

template<class T>
linkedlist<T>& linkedlist<T>::operator=(const linkedlist<T> &rhs)
{
    this->del();
    node<T>* curr1, curr2=rhs.head, *newnode;

    if (curr2)
    {
        newnode=new node<T>(curr2->data);
        this->head=newnode;
        curr1=this->head;
        curr2=curr2->next;
    }
    
    while (curr2)
    {
        newnode=new node<T>(curr2->data);
        curr1->next=newnode;
        curr1=curr1->next;
        curr2=curr2->next;
    }

    return *this;
}