#include "stack_array.h"

using namespace std;


int main()
{
    Stack<float> yoman;

    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;
    
    yoman.push(31);

    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    yoman.push(56);

    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    yoman.push(56);

    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    cout << yoman.pop() << endl;
    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    cout << yoman.pop() << endl;
    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    cout << yoman.pop() << endl;
    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    cout << yoman.pop() << endl;
    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    cout << yoman.pop() << endl;
    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    yoman.push(69);

    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    yoman.push(72);

    cout << yoman.length() << endl;
    cout << yoman.isEmpty() << endl;
    cout << yoman << endl;

    return 0;
}