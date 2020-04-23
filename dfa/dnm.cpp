#include <iostream>

// template <class T>
// class Set
// {
//     private:
//     T* set;
//     size_t size;
//     public:
//     Set();
//     ~Set();
//     void insert(T setlm);
// };

// template <class T>
// Set<T>::Set()
// {

// }

// template <class T>
// Set<T>::~Set()
// {

// }

// template <class T>
// void Set<T>::insert(T setlm)
// {
//     for (size_t i = 0; i < this->size; i++)
//     {
//         if (this->set[i]==setlm)
//             return;
//     }
    
// }


class dnm
{
private:
    size_t id;
public:
    dnm(size_t Id);
    ~dnm();
};

dnm::dnm(size_t Id)
{
    this->id=Id;
}

dnm::~dnm()
{
}

const char* yoboi(char const*& p)
{
    return p;
}

void afunc(const char somestr[],const size_t n)
{
    const char* p=somestr;
    for (size_t i = 0; i < n; i++)
    {
        std::cout << yoboi(p) << std::endl;
        ++p;
    }
    

}

int main()
{
    afunc("sexboiii!!!",11);
    return 0;
}