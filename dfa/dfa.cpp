#include "dfa.h"

int main()
{
    DFA yoman(2,"ab",4,2,{2,3});

    yoman.connect(0,1,'a');
    yoman.connect(1,0,'a');

    yoman.connect(0,2,'b');
    yoman.connect(2,0,'b');

    yoman.connect(1,3,'b');
    yoman.connect(3,1,'b');

    yoman.connect(2,3,'a');
    yoman.connect(3,2,'a');

    for (size_t i = 0; i < yoman.length(); i++)
    {
        std::cout << yoman.States()[i] << std::endl;
    }

    std::cout << yoman.test("aabbabaa",9) << std::endl;
    
    
    return 0;
}