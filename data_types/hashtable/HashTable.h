#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"

// Do not modify the public interface of this class.
// Otherwise, your code will note compile!
template <class T>
class HashTable {
    struct Entry {
        std::string Key;             // the key of the entry
        T Value;   // the value of the entry
        bool Deleted;        // flag indicating whether this entry is deleted
        bool Active;         // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket {
        Entry entries[3];
    };

    int _capacity; // INDICATES THE SIZE OF THE TABLE
    int _size; // INDICATES THE NUMBER OF ITEMS IN THE TABLE
    Bucket* _table; // HASH TABLE
    
    // You can define private methods and variables
    //iter methods for avg probes
    int iterUnSucc(int hashed_index);
    int iterSucc(std::string key);
public:
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    HashTable(const HashTable<T>& rhs);
    HashTable<T>& operator=(const HashTable<T>& rhs);
    ~HashTable();

    
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. 
    // IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    void Insert(std::string key, const T& value);

    // DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
    // IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
    // HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
    void Delete(std::string key);

    // IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
    // IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
    T Find(std::string key) const;

    // AFTER THIS FUNCTION IS EXECUTED THE TABLE CAPACITY MUST BE
    // EQUAL TO newCapacity AND ALL THE EXISTING ITEMS MUST BE REHASHED
    // ACCORDING TO THIS NEW CAPACITY.
    // WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    void Resize(int newCapacity);
    
    
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
    double AvgSuccProbe();
    
    
    // RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
    double AvgUnSuccProbe();

    // THE IMPLEMENTATION OF THESE FUNCTIONS ARE GIVEN TO YOU
    
    int Capacity() const;
    int Size() const;
};

template <class T>
HashTable<T>::HashTable() {
// CONSTRUCTOR
    ;
    
    this->_capacity=1;//no of buckets
    this->_size=0;//no of active elements
    this->_table=new Bucket[1];
    

}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& rhs) {
// COPY CONSTRUCTOR
    
    this->_table=NULL;

    this->_capacity=rhs.Capacity();
    this->_size=rhs.Size();
    _table=new Bucket[this->_capacity];

    int j;
    for (j = 0; j < this->_capacity; ++j)
    {
        size_t i;
        for(i=0;i<3;++i)
        {
            (this->_table[j].entries)[i]= (rhs._table[j].entries)[i];
        }
    }
}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& rhs) {
// OPERATOR=
    delete [] this->_table;
    this->_table=NULL;
    
    this->_capacity=rhs.Capacity();
    this->_size=rhs.Size();
    _table=new Bucket[this->_capacity];
    int j;
    for (j = 0; j < this->_capacity; ++j)
    {
        size_t i;
        for(i=0;i<3;++i)
        {
            (this->_table[j].entries)[i]= (rhs._table[j].entries)[i];
        }
    }

    return *this;
}

template <class T>
HashTable<T>::~HashTable() {
// DESTRUCTOR
    delete [] this->_table;
    this->_table=NULL;
}

template <class T>
void HashTable<T>::Delete(std::string key) {

// DELETE THE ENTRY WITH THE GIVEN KEY FROM THE TABLE
// IF THE GIVEN KEY DOES NOT EXIST IN THE TABLE, JUST RETURN FROM THE FUNCTION
// HINT: YOU SHOULD UPDATE ACTIVE & DELETED FIELDS OF THE DELETED ENTRY.
    int hashed_index=Hash(key)%this->_capacity, j=1;
    
    do
    {
        //iterate within the bucket
        size_t i;
        for(i=0;i<3;++i)
        {
            if( ((this->_table[hashed_index].entries)[i]).Active==true //there is an element
             && ((this->_table[hashed_index].entries)[i]).Key==key )//the key is equal, delete
            {
                ((this->_table[hashed_index].entries)[i]).Deleted=true;
                ((this->_table[hashed_index].entries)[i]).Active=false;
                --this->_size;
                
                return; 
            }
            else if( ((this->_table[hashed_index].entries)[i]).Active==false &&
                     ((this->_table[hashed_index].entries)[i]).Deleted==false ) //stop when empty 
            {
                return;
            }
        }
        
        hashed_index=(hashed_index+2*j-1)%this->_capacity;
        ++j;
    }while (true);

}

template <class T>
void HashTable<T>::Insert(std::string key, const T& value) {

// INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
// IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES THE ALREADY EXISTING ONE.
// IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5, RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.
    
    double load_factor= (double)this->_size/ (3.*(double)this->_capacity);
    
    if(load_factor > 0.5)//resize
    {
        int new_capacity=NextCapacity(this->_capacity);
        this->Resize(new_capacity);
    }
    
    int hashed_index=Hash(key)%this->_capacity, j=1;
    
    do
    {
        //iterate within the bucket
        size_t i;
        for(i=0;i<3;++i)
        {
            if( ((this->_table[hashed_index].entries)[i]).Active==false )//empty or deleted
            {
                ((this->_table[hashed_index].entries)[i]).Key=key;
                ((this->_table[hashed_index].entries)[i]).Value=value;
                ((this->_table[hashed_index].entries)[i]).Active=true;
                ((this->_table[hashed_index].entries)[i]).Deleted=false;
                ++this->_size;
                
                return;
            }
            else if ( ((this->_table[hashed_index].entries)[i]).Key==key )//not empty but element with the same key,
            {                                                             //  overwrite the value
                ((this->_table[hashed_index].entries)[i]).Value=value;

                return;
            }
        }
        
        hashed_index=(hashed_index+2*j-1)%this->_capacity;
        ++j;
    }while (true);
}

template <class T>
void HashTable<T>::Resize(int newCapacity) {
 AFTER THIS FUNCTION IS EXECUTED
// THE TABLE CAPACITY MUST BE EQUAL TO newCapacity AND ALL THE
// EXISTING ITEMS MUST BE REHASHED ACCORDING TO THIS NEW CAPACITY.
// WHEN CHANGING THE SIZE, YOU MUST REHASH ALL OF THE ENTRIES FROM 0TH ENTRY TO LAST ENTRY
    
    //swap values old table and this table
    int oldCapacity=this->_capacity, j;
    Bucket* old_table=this->_table;
    this->_table=NULL;
    this->_table=new Bucket[newCapacity];

    this->_size=0;
    this->_capacity=newCapacity;

    for (j = 0; j < oldCapacity; ++j)
    {
        size_t i;
        for(i=0;i<3;++i)
        {
            if( ((old_table[j].entries)[i]).Active==true ) //there is an element, rehash
            {
                this->Insert( ((old_table[j].entries)[i]).Key, ((old_table[j].entries)[i]).Value );
            }
        }
    }
    
    delete [] old_table;
}

template <class T>
T HashTable<T>::Find(std::string key) const {
 IT SHOULD RETURN THE VALUE THAT
// IT SHOULD RETURN THE VALUE THAT CORRESPONDS TO THE GIVEN KEY.
// IF THE KEY DOES NOT EXIST, THIS FUNCTION MUST RETURN T()
    int hashed_index=Hash(key)%this->_capacity, j=1;
    
    do
    {
        //iterate within the bucket
        size_t i;
        for(i=0;i<3;++i)
        {
            if( ((this->_table[hashed_index].entries)[i]).Active==true //there is an element
            && ((this->_table[hashed_index].entries)[i]).Key==key )//the key is equal
            {
                return ((this->_table[hashed_index].entries)[i]).Value;   
            }
            else if( ((this->_table[hashed_index].entries)[i]).Active==false &&
                     ((this->_table[hashed_index].entries)[i]).Deleted==false ) //stop when empty
            {
                return T();
            }
        }
        
        hashed_index=(hashed_index+2*j-1)%this->_capacity;
        ++j;
    }while (true);
    
    return T();

}

template <class T>
int HashTable<T>::iterUnSucc(int hashed_index)
{
    int total_probes=0, j=1;
   
    do
    {
        ++total_probes;
        //iterate within the bucket
        size_t i;
        for(i=0;i<3;++i)
        {
            if( ((this->_table[hashed_index].entries)[i]).Active==false &&
                ((this->_table[hashed_index].entries)[i]).Deleted==false ) //stop when empty
            {
                return total_probes;
            }
        }
        
        hashed_index=(hashed_index+2*j-1)%this->_capacity;
        ++j;
    }while (true);

    return total_probes;
}

template <class T>
double HashTable<T>::AvgUnSuccProbe() {

// RETURNS THE AVERAGE NUMBER OF PROBES FOR UNSUCCESSFUL SEARCH
    int total_probes=0, sum=0;
    int j;
    for (j = 0; j < this->_capacity; ++j)
    {  
        total_probes=this->iterUnSucc(j);
        sum+=total_probes;
    }
    return ((double)sum) / ((double)this->_capacity);
}

template <class T>
int HashTable<T>::iterSucc(std::string key)
{
    int hashed_index=Hash(key) % this->_capacity, total_probes=0, j=1;
   
    do
    {
        ++total_probes;
        //iterate within the bucket
        size_t i;
        for(i=0;i<3;++i)
        {
            if( ((this->_table[hashed_index].entries)[i]).Active==true //there is an element
            && ((this->_table[hashed_index].entries)[i]).Key==key )//the key is equal
            {
                return total_probes;   
            }
            else if( ((this->_table[hashed_index].entries)[i]).Active==false &&
                     ((this->_table[hashed_index].entries)[i]).Deleted==false ) //stop when empty
            {
                return 0;
            }
        }
        
        hashed_index=(hashed_index+2*j-1)%this->_capacity;
        ++j;
    }while (true);

    return total_probes;
}

template <class T>
double HashTable<T>::AvgSuccProbe() {

// RETURNS THE AVERAGE NUMBER OF PROBES FOR SUCCESSFUL SEARCH
    int total_probes=0, sum=0;
    int j;
    for (j = 0; j < this->_capacity; ++j)
    {   
        int i;
        for(i=0;i<3;++i)
        {
            if(((this->_table[j].entries)[i]).Active==true)//there is an element
            {
                total_probes=this->iterSucc( ((this->_table[j].entries)[i]).Key);
                sum+=total_probes;
            }
        }
    }
    return ((double)sum) / ((double)this->_size);
}

template <class T>
int HashTable<T>::Capacity() const {
    return _capacity;
}

template <class T>
int HashTable<T>::Size() const {
    return _size;
}

#endif
