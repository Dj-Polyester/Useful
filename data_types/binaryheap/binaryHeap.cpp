#include <iostream>
#include <cmath>

const char* UnderFlowException()
{
  return "UnderFlowException: Cannot delete. The heap is empty.";
}

template <class T>
class BinaryHeap
{
  public:
    BinaryHeap(size_t capa, std::string mode);
    BinaryHeap(std::string mode="min",size_t capacity = 100);
    BinaryHeap(size_t capacity = 100);
    BinaryHeap(BinaryHeap<T>& rhs);
    BinaryHeap(T*& rhs);
    ~BinaryHeap();
    
    T min() {return array[1];}
    T pop();
    
    template <class U>
    friend void heapsort( U arr[], size_t n, std::string order  );

    void insert( const T & x );
    void set_print(std::string ord);
    size_t Size() {return size;}

    BinaryHeap<T> operator=(BinaryHeap<T>& rhs);
    template <class U>
    friend std::ostream& operator<<(std::ostream& out, BinaryHeap<U> &tree);

    std::ostream& print_sideways(std::ostream& out,const size_t i, std::string indent);
    std::ostream& print_levelorder(std::ostream& out);
  private:
    bool Mode=0;//Max if 1, min if 0
    bool Order=0;//printing Order, level-Order if 0, tree if 1
    size_t size;  // Number of elements in heap
    size_t capacity; // Capacity of the array
    T* array;   // The heap array
    void percDown(size_t hole);
    void resize(size_t newSize);
};

template<class T>
void BinaryHeap<T>::set_print(std::string ord)
{
    if(ord=="tree") Order=1;
    else Order=0;
}

template<class T>
std::ostream& operator<<(std::ostream& out, BinaryHeap<T> &heap)
{
  if (heap.size)
  {
    if (heap.Order)
    {

      heap.print_sideways(out,1, "");

    }
    else
    {
      heap.print_levelorder(out);
    }

  }
  
  return out;
  
}

template <class T>
std::ostream& BinaryHeap<T>::print_levelorder(std::ostream& out)
{
  for (size_t i = 1; i <= size; i++)
  {
    out << array[i] << " ";
  }

  return out;
}

template<class T>
std::ostream& BinaryHeap<T>::print_sideways(std::ostream& out,const size_t i, std::string indent) {
    if (i <= size) {
        print_sideways(out,2*i+1, indent + "    ");
        out << indent << array[i] << std::endl;
        print_sideways(out,2*i, indent + "    ");
    }
    return out;
}

template <class T>
BinaryHeap<T>::BinaryHeap(size_t capa, std::string mode)
{
  if(mode=="max") Mode=1;
  capacity=capa;
  size=0;
  array=new T[capacity];
}
template <class T>
BinaryHeap<T>::BinaryHeap(std::string mode, size_t capa)
{
  if(mode=="max") Mode=1;
  capacity=capa;
  size=0;
  array=new T[capacity];
}
template <class T>
BinaryHeap<T>::BinaryHeap(size_t capa)
{
  Mode=0;
  capacity=capa;
  size=0;
  array=new T[capacity];
}

template <class T>
BinaryHeap<T>::BinaryHeap(BinaryHeap<T>& rhs)
{
  *this=rhs;
}

template <class T>
BinaryHeap<T> BinaryHeap<T>::operator=(BinaryHeap<T>& rhs)
{
  array=new T[rhs.capacity];
  size=rhs.size;
  
  for (size_t i = 1; i <= size; ++i)
  {
    array[i] = rhs[i];
  }
}

template <class T>
BinaryHeap<T>::~BinaryHeap()
{
  delete [] array;
}

// Insert item x into the priority queue, maintaining heap Order.
// Duplicates are allowed.
template <class T>
void BinaryHeap<T>::insert( const T & x )
{
    
    if( ++size == capacity )//resize if full
        resize( capacity * 2 + 1 );

    array[0]=x;
    // Percolate up
    size_t hole = size;

    if (Mode)//max-heap
    {
      for( ; x > array[ hole / 2 ]; hole /= 2 )
      {
        array[ hole ] = array[ hole / 2 ];

      }
        
    }
    else//min-heap
    {
      for( ; x < array[ hole / 2 ]; hole /= 2 )
        array[ hole ] = array[ hole / 2 ];
    }
    
    array[ hole ] = x;
}

template <class T>
void BinaryHeap<T>::resize(size_t capa)
{
  
  T* oldArray=array;
  array=NULL;
  array=new T[capa];
  for (size_t i = 0; i < size; i++)
  {
    array[i]=oldArray[i];
  }
  delete [] oldArray;
  oldArray=NULL;

  capacity=capa;
}

// Remove the smallest item from the priority queue, if min-heap, else largest.
// Throw UnderflowException if empty.
template <class T>
T BinaryHeap<T>::pop()//delMax if max-heap, delMin else
{
    if (size)
    {
      T tmp = array[1];
      array[ 1 ] = array[ size-- ];
      percDown( 1 );

      return tmp;
    }
    
    return T();
}

// Internal method to percolate down in the heap.
// hole is the index at which the percolate begins.
template <class T>
void BinaryHeap<T>::percDown( size_t hole )
{
  size_t child;
  T tmp = array[ hole ];

  if (Mode)
  {
    for( ; hole * 2 <= size; hole = child )
    {
      child = hole * 2;
      if( child != size && array[child + 1] > array[child])
         child++;
      if( array[ child ] > tmp )
         array[ hole ] = array[ child ];
      else
         break;
    }
  }
  else
  {
    for( ; hole * 2 <= size; hole = child )
    {
      child = hole * 2;
      if( child != size && array[child + 1] < array[child])
         child++;
      if( array[ child ] < tmp )
         array[ hole ] = array[ child ];
      else
         break;
    }
  }
  
  array[ hole ] = tmp;
}

template <class T>
void heapsort( T arr[], size_t n, std::string order="normal" )
{
  BinaryHeap<T> a(n+1, (order=="reverse" ? "min":"max") );
  
  a.size=n;
  //copy array into heap
  for (size_t i = 1; i <= n; i++)
  {
    a.array[i]=arr[i-1];
  }
  
  for( size_t i = a.size / 2; i > 0; --i )  /* buildHeap */
    a.percDown(i);

  while (a.size)
  {
    arr[a.size-1]=a.pop();/* delMax if max-heap, delMin if min-heap, then 
                                reverse Order if max-heap, sorted orted if min-heap*/
  }

}

int main()
{
  // BinaryHeap<int> yoman(4);
  // yoman.set_print("tree");
  // yoman.insert(9);
  // yoman.insert(4);
  // yoman.insert(5);
  // yoman.insert(2);
  // std::cout << yoman << "   size:" << yoman.Size() << std::endl;
  // yoman.insert(6);
  // std::cout << yoman << "   size:" << yoman.Size()<< std::endl;
  
  int yoman[9]={23,52,67,67,2,6,2,8,3};

  heapsort(yoman, 9);
  
  for (size_t i = 0; i < 9; i++)
  {
    std::cout << yoman[i] << " " ;
  }
  std::cout << std::endl;

  return 0;
}