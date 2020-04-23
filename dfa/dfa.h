#include <iostream>
#include <utility>
#include <set>
#include <initializer_list>

#define PRINT bool willprint=true;

class State
{
    friend class DFA;
private:
    size_t id;
    std::set < std::pair < size_t, char > > adj;
public:
    State();
    ~State();
    
    friend std::ostream& operator<<(std::ostream& out,const State& rhs);
};

State::State()
{
}
State::~State()
{

}

std::ostream& operator<<(std::ostream& out,const State& rhs)
{
    
    out << rhs.id << ") ";
    for (auto i : rhs.adj)
    {
        out << "(" << i.first << "-" << i.second << ")" << ",";
    }
    return out;
}


class DFA
{
private:
    PRINT
    char* alphabet;
    State* states;
    size_t num_final;
    size_t num_states;
    size_t num_alpha;
    size_t* final;
public:
    DFA(size_t num_of_alpha,const char alpha[],size_t num_of_states,size_t num_of_final_states,std::initializer_list<size_t> final_states);
    ~DFA();
    void connect(size_t from,size_t to,char ch);
    bool test(const char str[], const size_t n);
    bool isFinal(size_t numero);
    void print();
    size_t length() {return num_states;};
    State* States() {return states;};
    
};

DFA::DFA(size_t num_of_alpha,const char alpha[],size_t num_of_states,size_t num_of_final_states,std::initializer_list<size_t> final_states)
{
    std::initializer_list<size_t>::iterator i;
    size_t j=0;

    this->alphabet=new char[num_of_alpha];
    this->num_alpha=num_of_alpha;
    for (j = 0; j < num_of_alpha; ++j)
    {
        this->alphabet[j]=alpha[j];
    }
        
    j=0;
    this->final=new size_t[num_of_final_states];
    this->num_final=num_of_final_states;
    for (i = final_states.begin(); i != final_states.end(); i++)
    {
        this->final[j]=*i;
        ++j;
    }
    
    j=0;
    this->states=new State[num_of_states];
    this->num_states=num_of_states;
    for (j = 0; j < num_of_states; j++)
    {
        this->states[j].id=j;
    }
}

DFA::~DFA()
{
    delete[] alphabet;
    
    delete[] final;

    delete[] states;  
}

void DFA::print()
{
    for (size_t i = 0; i < this->num_states; i++)
    {
        std::cout << this->states[i] << std::endl;
    } 
}

void DFA::connect(size_t from,size_t to,char ch)
{
    std::pair < size_t, char > tmp;
    tmp.first=to;
    tmp.second=ch;
    this->states[from].adj.insert(tmp);
}

bool DFA::isFinal(size_t numero)
{
    for (size_t i = 0; i < this->num_final; i++)
    {
        if (this->final[i]==numero)
            return true;
    }
    return false;
    
}

void strprint(char const* str, const size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        std::cout << *str;
        ++str;
    }  
}

bool DFA::test(const char str[], const size_t n)
{
    size_t current=0;
    size_t tmp;
    for (size_t i = 0; i < n; i++)
    {
        for (auto j : this->states[current].adj)
        {
            if (j.second==str[i])
            {
                tmp=current;
                current=j.first;
                if (this->willprint)
                {
                    std::cout << tmp << " yields " << current << " ";
                    strprint(&str[i],n-i);
                    std::cout << std::endl;
                }
                    
            }
            
        }  
    }
    
    return isFinal(current);
    
}