#include <iostream>
#include "linkedlist.h"

using namespace std;

int main()
{
    
    linkedlist<int> List; 

    cout << List.insert_sorted( 1 ) << endl;
    cout << List.insert_sorted( 5 ) << endl;
    cout << List.insert_sorted( 2 ) << endl;
    cout << List.insert_sorted( 12 ) << endl;
    cout << List.insert_sorted( 19 ) << endl;
    cout << List.insert_sorted( 19 ) << endl;
    cout << List.insert_sorted( 7 ) << endl;
    cout << List.insert_sorted( 19 ) << endl;
    cout << List.insert_sorted( 1 ) << endl;
   
    cout << List << endl;
    cout << List[8] << endl;

    List.insert(31,3);
    cout << "INSERT:\n";
    cout << List << endl;

    List.insert(3,9);
    cout << "INSERT:\n";
    cout << List << endl;

    List.nremove(0);
    cout << "NREMOVE:\n";
    cout << List << endl;
    
    List.nremove(2);
    cout << "NREMOVE:\n";
    cout << List << endl;

    List.nremove(9);
    cout << "NREMOVE:\n";
    cout << List << endl;
 
    List.del();
    cout << "DEL:\n";
    cout << List << endl;

    return 0;
}