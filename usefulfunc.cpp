#include <iostream>

#include "usefulfunc.hpp"

/******************************************************************************************************
 * Accepts a stack of integers as a parameter and that          *
 * collapses it by replacing each successive pair of integers with the sum of the pair.               *
 * For example if the stack stores [7, 2, 8, 9, 4, 11, 7, 1, 42] such that 42 is at top and           *
 * 7 is at bottom, the first pair should be collapsed into 9 (7+2) , the second pair                  *
 * should be collapsed into 17 (8+9) and so on. If the stack stores and odd number of elements        *
 * the final element is not collapsed (such as the 42 in our example). So for this stack              *
 * your method would yield [9, 17, 15, 8, 42], where 9 is at bottom and 42 is at top.                 *
 * You can only use one queue as auxiliary storage.                                                   *
 * You are not allowed to use any other auxiliary data structures.                                    *
 ******************************************************************************************************/
void collapse(Stack<int>& s) {

    Queue<int> q;
    
    if(!s.isEmpty())
    {
        size_t length=s.size(),half=length/2,i=0;
        int num1, num2;
        
        if(length%2)
        {
            q.enqueue(s.pop());
        }

        for(;i<half;++i)
        {
            num1=s.pop();
            num2=s.pop();
            q.enqueue(num1+num2);
        }
        ++half;
        for(i=0;i<half;++i)
        {
            s.push(q.dequeue());
        }
        for(i=0;i<half;++i)
        {
            q.enqueue(s.pop());
        }
        for(i=0;i<half;++i)
        {
            s.push(q.dequeue());
        }
    }
}

/******************************************************************************************************
 * Accepts two stacks of integers as parameters and                 *
 * returns true if the two stacks are exactly the same sequence of integer values in the same order.  *
 * Your method must restore the two stacks to their original state before returning.                  *
 * Use one stack as auxiliary storage.                                                                *
 ******************************************************************************************************/
bool equals(Stack<int>& s1, Stack<int>& s2) {

    size_t size=s1.size();
    if(size!=s2.size()) return false;
    Stack<int> s3;
    size_t i=0,j=0;
    int num1=0,num2=0;
    
    for(;i<size;++i)
    {
        if(num1!=num2) break;
        num1=s1.pop();
        num2=s2.pop();
        s3.push(num1);
        s3.push(num2);
    }
    
    for(;j<i;++j)
    {
        num2=s3.pop();
        num1=s3.pop();
        s1.push(num1);
        s2.push(num2);
    }
    
    if(i==size) return true;
    return false;
}

/******************************************************************************************************
 * Accepts a queue of integers as a parameter and that             *
 * puts the integers into sorted (nondecreasing) order, assuming that the queue is already sorted     *
 * by absolute value. For example if the queue stores [1, 2, -2, 4, -5, 8, -8, 12, -15],              *
 * notice that the values appear in sorted order if you ignore the sign of the numbers.               *
 * Your method should reorder the values so that the queue stores [-15, -8, -5, -2, 1, 2, 4, 8, 12].  *
 * Use one stack as auxiliary storage.                                                                *
 ******************************************************************************************************/
void reorder(Queue<int>& q) {
    
    Stack<int> s;
    bool ordered=false;
    int num;
    size_t count, size=q.size();
    while(ordered==false)
    {
        ordered=true;
        for(count=0;count<size-1;++count)
        {
            if(!count) num=q.dequeue();
            
            if(num<=q.top())
            {
                s.push(num);
                num=q.dequeue();
            }
            else
            {
                ordered=false;
                s.push(q.dequeue());
            }
            
        }
        s.push(num);
        
        for(count=0;count<size;++count)
        {
            q.enqueue(s.pop());
        }
        for(count=0;count<size;++count)
        {
            s.push(q.dequeue());
        }
        for(count=0;count<size;++count)
        {
            q.enqueue(s.pop());
        }
        
    }
}

string binaryAdd(string s1,string s2)
{
    size_t max_length,min_length,i,c=0,s=0,diff;
    string result="",max_str,min_str;
    if(s1.length()<s2.length())
    {
        max_length=s2.length();
        min_length=s1.length();
        max_str=s2;
        min_str=s1;
    }
    else
    {
        max_length=s1.length();
        min_length=s2.length();
        max_str=s1;
        min_str=s2;
    }
    diff=max_length-min_length;
    
    for(i=min_length;i>0;--i)
    {
        if(max_str[i-1+diff]=='0' && min_str[i-1]=='0')
        {
            s=c;
            c=0;
        }
        else if(max_str[i-1+diff]=='1' && min_str[i-1]=='1')
        {
            s=c;
            c=1;
        }
        else if((max_str[i-1+diff]=='1' && min_str[i-1]=='0') || (max_str[i-1+diff]=='0' && min_str[i-1]=='1'))
        {
            if(c)
            {
                s=0;
            }
            else
            {
                s=1;
            }
            
        }
        if(s)
        {
            result='1'+result;
        }
        else
        {
            result='0'+result;
        }
    }
    for(i=diff;i>0;--i)
    {
        if(max_str[i-1]=='0')
        {
            s=c;
            c=0;
        }
        
        else if(max_str[i-1]=='1')
        {
            if(c)
            {
                s=0;
            }
            else
            {
                s=1;
            }
        }
        if(s)
        {
            result='1'+result;
        }
        else
        {
            result='0'+result;
        }
    }
    if(c)
    {
        result='1'+result;
    }

    return result;
}


int main()
{

	cout << addBinary("1010100","10010") << endl;



}




