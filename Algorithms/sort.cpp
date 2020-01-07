#include <iostream>
#include <limits>


//print the array
template <class T>
void print(const T arr, int n)
{
    for(int i=0;i<n;++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
//swap items
template < class Object>
void swap( Object &lhs, Object &rhs )
{
	Object tmp = lhs;
	lhs = rhs;
	rhs = tmp;
}
//merge arrays for mergesort
const int MAX_SIZE = 10;
template <class DataType>
void merge(DataType theArray[], int first, int mid, int last)
{
   DataType tempArray[MAX_SIZE]; 	// temporary array
   int first1 = first; 	// beginning of first subarray
   int last1 = mid; 	// end of first subarray
   int first2 = mid + 1;	// beginning of second subarray
   int last2 = last;	// end of second subarray
   int index = first1; // next available location in tempArray

   for ( ; (first1 <= last1) && (first2 <= last2); ++index)
      if (theArray[first1] < theArray[first2])  
         tempArray[index] = theArray[first1++];
      else  
          tempArray[index] = theArray[first2++]; 
        // finish off the first subarray, if necessary
   for (; first1 <= last1; ++first1, ++index)
      tempArray[index] = theArray[first1];

   // finish off the second subarray, if necessary
   for (; first2 <= last2; ++first2, ++index)
      tempArray[index] = theArray[first2];

   // copy the result back into the original array
   for (index = first; index <= last; ++index)
      theArray[index] = tempArray[index];
}

template <class DataType>
void partition(DataType theArray[], int first, int last, int &pivotIndex) 
{

//    int pIndex = choosePivot(theArray, first, last);

//    // put pivot at position first
//    swap(theArray[pIndex], theArray[first]);

    DataType pivot = theArray[first]; // copy pivot


    int lastS1 = first;           // index of last item in S1
   int firstUnknown = first + 1; //index of 1st item in unknown

   // move one item at a time until unknown region is empty
   for (; firstUnknown <= last; ++firstUnknown) {
      if (theArray[firstUnknown] < pivot){		   
         ++lastS1;
         swap(theArray[firstUnknown], theArray[lastS1]);
      }
   }

   // place pivot in proper position and mark its location
   swap(theArray[first], theArray[lastS1]);
   pivotIndex = lastS1;
}




//////////////////////////////////////////////////////////////////////////////////
///////////SORTING ALGORITHMS/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


template <class Item>
void selectionSort(Item a[], int n) {
  for (int i = 0; i < n-1; i++) {
    int min = i;
    for (int j = i+1; j < n; j++)
       if (a[j] < a[min]) min = j;
    swap(a[i], a[min]);
  }
}

template <class Item>
void insertionSort(Item a[], int n)
{
   for (int i = 1; i < n; i++)
   { 
      Item tmp = a[i]; // the element to be inserted
      int j;
      for (j=i; j>0 && tmp < a[j-1]; j--)
         a[j] = a[j-1]; // shift elements
      a[j] = tmp; // insert
   }
}

template <class Item>
void bubbleSort(Item a[], int n)
{
   bool sorted = false; 
   int last = n-1;
      
   for (int i = 0; (i < last) && !sorted; i++){
      sorted = true;
      for (int j=last; j > i; j--)
         if (a[j-1] > a[j])
         {
            swap(a[j],a[j-1]);
            sorted = false; // signal exchange
         }
    }
}

template <class DataType>
void mergeSort(DataType theArray[], int first, int last) {
   if (first < last) { // more than one item
      int mid = (first + last)/2; 	// index of midpoint
      mergeSort(theArray, first, mid);
      mergeSort(theArray, mid+1, last);

      // merge the two halves
      merge(theArray, first, mid, last);
   }
}  // end mergeSort

template <class DataType>
void quickSort(DataType theArray[], int first, int last) {

   int pivotIndex;
   if (first < last) {
      
      partition(theArray, first, last, pivotIndex);

      // sort regions S1 and S2
      quickSort(theArray, first, pivotIndex-1);
      quickSort(theArray, pivotIndex+1, last);
   }
}

int main(const int argc,const char** argv) 
{
    int length=argc-1, * arr=new int[length];

    for(int i=0;i<length;++i)
    {
        arr[i] = atoi(argv[i+1]);
    } 

//////SORT ALGORITH HERE//////////

    quickSort(arr,0,length-1);

////////////////////////////////
    print(arr, length);


    delete [] arr;
    return 0;
}