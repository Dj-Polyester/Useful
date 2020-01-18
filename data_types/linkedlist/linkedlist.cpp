#include <limits>
#include "linkedlist.hpp"

using namespace std;

int main()
{
    
    list<int> List; 

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
    cout << List[2] << endl;
    List.printReverse();

    List.insert(8,2);
    cout << "INSERT:\n";
    cout << List << endl;
    List.printReverse();

    List.insert(3,-1);
    cout << "INSERT:\n";
    cout << List << endl;
    List.printReverse();

    List.insert(3,16);
    cout << "INSERT:\n";
    cout << List << endl;
    List.printReverse();

    List.nremove(-3);
    cout << "NREMOVE:\n";
    cout << List << endl;
    List.printReverse();

    List.nremove(1);
    cout << "NREMOVE:\n";
    cout << List << endl;
    List.printReverse();

    List.removelast(19);
    cout << "REMOVELAST:\n";
    cout << List << endl;
    List.printReverse();

    List.removelast(19);
    cout << "REMOVELAST:\n";
    cout << List << endl;
    List.printReverse();

    List.removeall(19);
    cout << "REMOVEALL:\n";
    cout << List << endl;
    List.printReverse();

    List.invert();
    cout << "INVERT:\n";
    cout << List << endl;
    List.printReverse();


    // printf("MIN: %d\n",min(List));
    // printf("MAX: %d\n",max(List));
    // printf("POP: %d\n",pop(List,-1));
    // printList(List);
    // reverseprintList(List);
    
    
    return 0;
}

