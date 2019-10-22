#ifndef linkedlist
#define linkedlist

#include <iostream>

template <class T>
class node
{
    public:
        T data;
        node* next;
        node* pre;

        node(T x, node* p, node* n): data(x), pre(p), next(n) {}
        node(): pre(NULL), next(NULL) {}
};

template <class T>
class list
{
    public:
        int len;
        node<T>* head;
        node<T>* tail;

        list();
        ~list();

        void insert(T data,int index);
        void append(T data );
        
        void nremove(int index);
        void removefirst(T data);
        void removelast(T data);
        void removeall(T data);

        void print();
        void printReverse();
        
        void swap(T &a,T &b);
        void invert();
        T pop(int index);
        int max();
        int min();
        void removelist();
        void freelist();

        template<class U>
        friend std::ostream& operator<<(std::ostream& out, const list<U> &List);
        T & operator [] (size_t index);
};

template<class T>
T & list<T>::operator [] (size_t index)
{
        int length=this->len;
        node<T>* curr;
        size_t i;
        //index negative
        if (index<0)
            index+=length+1;

        //index bigger than length
        if(length-1 < index)
            index=length;

        //close to head
        if(index<length/2)
        {
            curr = this->head;
            
            for(i=0; i<=index; i++)
            {
                curr=curr->next;
            }
        }
        //close to tail
        else
        {
            curr = this->tail;
            i=0;
            for(i=0; i<length-index; i++)
            {
                curr=curr->pre;
            }
        }

        return curr->data;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const list<T> &List)
{
    node<T> *curr=List.head->next;
    size_t length=List.len;
    size_t i=0;
    for(;i<length;++i)
    {
        out << curr->data << " ";
        curr=curr->next;         
    }

    return out;
}


template<class T>
list<T>::list()
{
    this->head = new node<T>;
    this->tail = new node<T>;

    this->head->next=this->tail;
    this->tail->next=NULL;
    this->tail->pre=this->head;
    this->head->pre=NULL;

    this->len=0;
}

template<class T>
list<T>::~list()
{
    this->removelist();
    this->freelist();
}

template<class T>
void list<T>::print()
{
    node<T> *curr=this->head->next;
    size_t length=this->len;
    size_t i=0;
    for(;i<length;++i)
    {
        std::cout << curr->data << " ";
        curr=curr->next;         
    }
    std::cout << std::endl;
}
template<class T>
void list<T>::printReverse()
{
    node<T> *curr=this->tail->pre;
    size_t length=this->len;
    size_t i=0;
    for(;i<length;++i)
    {
        std::cout << curr->data << " ";
        curr=curr->pre;         
    }
    std::cout << std::endl;
}

template<class T>
void list<T>::append(T data)
{
    
    node<T>* newnode = new node<T>(data,this->tail->pre,this->tail);
	
    newnode->pre->next=newnode;
    tail->pre=newnode;

    this->len++;
}

template<class T>
void list<T>::insert(T data,int index)
{
    
        int length=this->len;
        node<T>* curr;
        node<T>* newnode = new node<T>(data,NULL,NULL);
        size_t i;
        //index negative
        if (index<0)
            index+=length+1;

        //index bigger than length
        if(length-1 < index)
            index=length;

        //close to head
        if(index<length/2)
        {
            curr = this->head;

            for(i=0; i<=index; i++)
            {
                curr=curr->next;
            }
        }
        //close to tail
        else
        {
            curr = this->tail;
            for(i=0; i<length-index; i++)
            {
                curr=curr->pre;
            }
        }
        newnode->next=curr;
        newnode->pre=curr->pre;
        curr->pre->next=newnode;
        curr->pre=newnode;

        this->len++;
    

}

template<class T>
void list<T>::removefirst(T data)
{
    if (this->len!=0)
    {
        int length=this->len;
        node<T>* curr=this->head->next;
        size_t i=0;
        for(; i<length; ++i)
        {
            if (curr->data==data)
            {
                curr->pre->next=curr->next;
                curr->next->pre=curr->pre;
                delete [] curr;
                this->len--;
                break;
            }
            curr = curr->next;
        }
    }
}

template<class T>
void list<T>::removelast(T data)
{
    if (this->len!=0)
    {
        int length=this->len;
        node<T>* curr=this->tail->pre;
        size_t i=0;
        for(; i<length; ++i)
        {
            if (curr->data==data)
            {
                curr->pre->next=curr->next;
                curr->next->pre=curr->pre;
                delete [] curr;
                this->len--;
                break;
            }
            curr = curr->pre;
        }
    }
}

template<class T>
void list<T>::removeall(T data)
{
    if (this->len!=0)
    {
        int length=this->len;
        node<T>* current=this->head->next;
        node<T>* currentfree;
        size_t index=0;
        for(; index<length; index++)
        {
            if (current->data==data)
            {

                current->pre->next=current->next;
                current->next->pre=current->pre;
                currentfree=current;
                current = current->pre;
                delete [] currentfree;

                this->len--;
            }
            current = current->next;
        }
    }
}

template<class T>
void list<T>::nremove(int index)
{
    if (this->len!=0)
    {
        node<T>* current;
        int length=this->len;
        size_t i;

        //index negative
        if (index<0)
            index+=length;

        //index bigger than length
        if(length-1 < index)
            index=length;

        //close to head
        if(index<length/2)
        {
            current = this->head;

            for(i=0; i<=index; i++)
                current=current->next;
        }
        //close to tail
        else
        {
            current = this->tail;

            for(i=0; i<length-index; i++)
                current=current->pre;

        }
        current->pre->next=current->next;
        current->next->pre=current->pre;
        delete [] current;
        this->len--;
    }
}

template<class T>
void list<T>::invert()
{
    
        node<T>* currentnext=this->head->next;
        node<T>* currentpre=this->tail->pre;
        size_t i=0;
        int length=this->len;
        for(;i<length/2;i++)
        {
            swap(currentnext->data,currentpre->data);
            currentnext=currentnext->next;
            currentpre=currentpre->pre;
        }
    
}

template<class T>
void list<T>::swap(T &a,T &b)
{
    T tmp=a;
    a=b;
    b=tmp;
}
/*
template<class T>
int min()
{
    if (this->len!=0)
    {
        node<T>* current=this->head->next;
        int minimum=current->data;
        for(int i=0;i<this->len-1;i++)
        {
            current=current->next;
            int data=current->data;
            if(data<minimum) minimum=data;
        }
        return minimum;
    }
    return INT_MAX;
}

int max(LIST* list)
{
    if (list!=NULL && list->len!=0)
    {
        NODE* current=list->head->next;
        int maximum=current->data;
        for(int i=0;i<list->len-1;i++)
        {
            current=current->next;
            int data=current->data;
            if(data>maximum) maximum=data;
        }
        return maximum;
    }
    return INT_MIN;
}
*/

template<class T>
T list<T>::pop(int index)
{
    if (this->len!=0)
    {
        node<T>* current;
        int length=this->len;

        //index negative
        if (index<0)
            index+=length;

        //index bigger than length
        if(length-1 < index)
            index=length;

        //close to head
        if(index<length/2)
        {
            current = this->head;
            size_t i=0;
            for(; i<=index; i++)
                current=current->next;
        }
        //close to tail
        else
        {
            current = this->tail;

            for(int i=0; i<length-index; i++)
                current=current->pre;

        }
        current->pre->next=current->next;
        current->next->pre=current->pre;
        T popdata=current->data;
        delete [] current;
        this->len--;
        return popdata;
    }
    return 0;
}

template<class T>
void list<T>::removelist()
{
	if (this->len!=0)
    {
        int length=this->len;
        node<T>* current=this->head->next;
        node<T>* currentfree;
        size_t index=0;
        for(; index<length; index++)
        {
            current->pre->next=current->next;
            current->next->pre=current->pre;
            currentfree=current;
            current = current->pre;
            delete [] currentfree;

            this->len--;
            
            current = current->next;
        }
    }
	
       
}

template<class T>
void list<T>::freelist()
{
	delete [] this->head;
    delete [] this->tail;
}



#endif
