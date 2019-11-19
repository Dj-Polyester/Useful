#include <iostream>

#define INT_MIN INT16_MIN
#define INT_MAX INT16_MAX
#define STR_MIN ""
#define STR_MAX "zzzzzzzzzzzzzzzzzzz"


template <class T>
class Node {
    public:
        T data; // data stored at this node
        Node *left;    // reference to left subtree
        Node *right;   // reference to right subtree
       // int height;
        
        
        // Constructs a leaf node with the given data.
        Node(T val) 
        {
	        data = val;
            left= NULL;
            right= NULL;
        }

        // Constructs a branch node with the given data and links.
        Node(Node<T> &l, T &val) {
            add(l, val);
            data = val;
	        left= &l;
            right= NULL;
        }

        // Constructs a branch node with the given data and links.
        Node(T &val, Node<T> &r) {
	        add(val,r);
            data = val;
	        left= NULL;
            right= &r;
        }

        // Constructs a branch node with the given data and links.
        Node(Node<T> &l, T &val, Node<T> &r) {
	        

            add(l,val,r);
            Node<T>* tmpL=&l,* tmpR=&r;
            data = val;
	        left= &l;
            right= tmpR;
        }
};

template <class T>
class binarytree {
    private:
        size_t order=0;
        size_t Mode=0;
        Node<T> *root;   // null for an empty tree

        std::ostream& print_inorder(std::ostream& out, const Node<T>* r);
        std::ostream& print_preorder(std::ostream& out, const Node<T>* r);
        std::ostream& print_postorder(std::ostream& out, const Node<T>* r);
        std::ostream& print_sideways(std::ostream& out,const Node<T> *r, std::string indent);
        T max(Node<T>* r);
        T min(Node<T>* r);
        T sum(Node<T>* &r);
        T leaves(Node<T>* &r);
        void insert(Node<T>* &r, T &val);
        void insert( const T& x, Node<T> *& t );
        void remove(Node<T> *& r, T &val);
        void remove( const T& x, Node<T> *& t );
        void rotateL( Node<T> *& k2 );
        void rotateR( Node<T> *& k2 );
        void rotateRL( Node<T> *& k2 );
        void rotateLR( Node<T> *& k2 );

        int height(Node<T>* &r);
        bool contains(Node<T>* &r, T val);

    public:
        binarytree(Node<T> &n): root(&n) {}
        binarytree(T &n): root(&n) {}
        binarytree(): root(NULL) {}
        binarytree(const binarytree<T> &obj);
        ~binarytree();
        binarytree<T> *find(Node<T> *&r, const T &val);

        //~binarytree();
        
        template <class U>
        friend std::ostream& operator<<(std::ostream& out, binarytree<U> &tree);
        binarytree<T> &operator=(const binarytree<T> &rhs);
        T max();
        T min();
        T sum();
        T leaves();
        void insert(T val);
        void remove(T val);
        void remove_all(Node<T> *&r);
        void set_print(std::string ord);
        void mode(std::string mod);
        void copyTree(Node<T> *&curr_r, const Node<T> *source_r);
        bool contains(T val);
        int height();
};

template <class T>
binarytree<T> *binarytree<T>::find(Node<T> *&r, const T &val) {
    /* TODO */
    if (r == NULL || r->data == val) return r;
    else if (r->data > val) return find(r->left,val);
    else return find(r->right,val);
}

template <class T>
binarytree<T>::binarytree(const binarytree<T> &obj) {
    /* TODO */
    copyTree(this->root, obj.root);

}

template <class T>
binarytree<T>::~binarytree() {
    /* TODO */
    this->remove_all(this->root);
}


template <class T>
binarytree<T> &binarytree<T>::operator=(const binarytree<T> &rhs) {
    /* TODO */
    this->remove_all(this->root);
    copyTree(this->root, rhs.root);

    return *this;
}

template <class T>
void binarytree<T>::remove_all(Node<T> *&r) 
{
    /* TODO */
    if (r == NULL)  
        return;
    else   
    {
        remove_all(r->left);
        remove_all(r->right);
        
        Node<T> * oldNode =r;  // only  R or L child
           
        r = (r->left != NULL)? r->left : r->right;
        delete oldNode;
    }
}


template <class T>
void binarytree<T>::copyTree(Node<T> *&curr_r, const Node<T> *source_r)
{
    if(source_r == NULL)
    {
        curr_r = NULL;
    }
    else
    {
        curr_r = new Node<T>(source_r->data);
        copyTree(curr_r->left, source_r->left);
        copyTree(curr_r->right, source_r->right);
    }
}

template <class T>
void binarytree<T>::mode( std::string mod )
{
    Mode=(mod=="AVL"? 1 : 0);
}

template <class T>
void binarytree<T>::rotateL( Node<T> *& k2 )
{
    
    Node<T> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    // k2->height = height(k2);
    // k1->height = height(k1);
    k2 = k1;
}

template <class T>
void binarytree<T>::rotateR( Node<T> *& k2 )
{
    Node<T> *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    // k2->height = height(k2);
    // k1->height = height(k1);
    k2 = k1;
}

template <class T>
void binarytree<T>::rotateRL( Node<T> *& k3 )
{
   rotateR( k3->left );
   rotateL( k3 );
}

template <class T>
void binarytree<T>::rotateLR( Node<T> *& k3 )
{
   rotateL( k3->right );
   rotateR( k3 );
}

template<class T>
std::ostream& binarytree<T>::print_inorder(std::ostream& out, const Node<T>* r)
{
    if (r != NULL) 
    {
        // recursive case: print left, center, right
        print_inorder(out, r->left);
        out << r->data << " ";
        print_inorder(out, r->right);
    }
      return out;
}

template<class T>
std::ostream& binarytree<T>::print_preorder(std::ostream& out, const Node<T>* r)
{
    if (r != NULL) 
    {
        // recursive case: print left, center, right
        out << r->data << " ";
        print_preorder(out, r->left);
        print_preorder(out, r->right);
    }
      return out;
}

template<class T>
std::ostream& binarytree<T>::print_postorder(std::ostream& out, const Node<T>* r)
{
    if (r != NULL) 
    {
        // recursive case: print left, center, right
        print_postorder(out, r->left);
        print_postorder(out, r->right);
        out << r->data << " ";
    }
      return out;
}

template<class T>
std::ostream& operator<<(std::ostream& out, binarytree<T> &r)
{
    const binarytree<T>* tp=&r;
    
    if(!r.order) return print_sideways(out,tp->root, "");
    if(r.order==1) return r.print_inorder(out ,tp->root);
    if(r.order==2)return r.print_preorder(out ,tp->root);
    return r.print_postorder(out ,tp->root);
}

template<class T>
void binarytree<T>::set_print(std::string ord)
{
    if(ord=="side") order=0;
    else if(ord=="in") order=1;
    else if(ord=="pre") order=2;
    else if(ord=="post") order=3;
}

template<class T>
T binarytree<T>::max()
{
    return max(root);
}

template<class T>
T binarytree<T>::max(Node<T>* r){
   if(Mode==2)
   {
        T root_val, left, right, max;
       
        /*if(std::is_same<T,std::string>::value) max = STR_MIN;
        else */max=INT_MIN;

        if (r!= NULL) 
        {
            root_val = r ->data;
            left = this->max(r->left);
            right = this->max(r->right);
            // Find the largest of the three vals.
            if (left > right)
               max = left;
            else
               max = right;
            if (root_val > max)
               max = root_val;
        }
        return max;
   }
   else//binarytree
   {
       while(r->right)
            r=r->right;
       return r->data; 
   }  
}

template<class T>
T binarytree<T>::min()
{
    return min(root);
}

template<class T>
T binarytree<T>::min(Node<T>* r){
    if(Mode==2)
    {
        T root_val, left, right, min;
        
        /*if(std::is_same<T,std::string>::value) min = STR_MAX;
        else /*/min=INT_MAX;

        if (r!= NULL) 
        {
            root_val = r ->data;
            left = this->min(r->left);
            right = this->min(r->right);
            // Find the largest of the three vals.
            if (left > right)
               min = right;
            else
               min = left;
            if (root_val < min)
               min = root_val;
        }
        return min;
    }
    //binarytree
    else
    {
        
        while(r->left)
             r=r->left;
        return r->data; 
    }  
}

template<class T>
T binarytree<T>::sum()
{
    return sum(root);
}

template<class T>
T binarytree<T>::sum(Node<T>* &r){
   if (r==NULL)
      return 0;
   else 
      return r->data + sum(r->left) + sum(r->right);
}

template<class T>
T binarytree<T>::leaves()
{
    return leaves(root);
}

template<class T>
T binarytree<T>::leaves(Node<T>* &r){
    if (r->right==NULL && r->left==NULL) return 1; 
    else if(r->right) return leaves(r->right);
    else if(r->left) return leaves(r->left);
    return leaves(r->left) + leaves(r->right);
}

template<class T>
std::ostream& print_sideways(std::ostream& out,const Node<T> *r, std::string indent) {
    if (r != NULL) {
        print_sideways(out,r->right, indent + "    ");
        out << indent << r-> data << std::endl;
        print_sideways(out,r->left, indent + "    ");
    }
    return out;
}

template<class T>
int binarytree<T>::height()
{
    return height(root);
}

template<class T>
int binarytree<T>::height(Node<T>* &r) {
    if(r==NULL) return -1;
    int right_h=height(r->right), left_h=height(r->left), max_h;
    
    max_h=(right_h < left_h) ? left_h : right_h;

    return max_h+1;
}

template<class T>
bool binarytree<T>::contains(T val)
{
    return contains(root, val);
}

template<class T>
bool binarytree<T>::contains(Node<T>* &r, T val){
    if (r == NULL)
        return false;
    else {
        if (r->data == val)
            return true;
        else if (r->data > val)
            return contains(r->left,val);
        else return contains(r->right,val);
  }
}



template<class T>
void binarytree<T>::insert(T val)
{
    if(Mode) insert(val ,root);
    else insert(root, val);

}

template<class T>
void binarytree<T>::insert(Node<T>* &r, T& val)
{
    if (r == NULL)
        r=new Node<T>(val);
    else if (r->data > val)
        insert(r->left,val);
    else if(r->data < val) 
        insert(r->right,val);  
}

template <class T>
void binarytree<T>::insert( const T& x, Node<T> *& t )
{
//    int max_h;
   if( t == NULL )
     t = new Node<T>(x);
   else if( x < t->data )
   {
     insert( x, t->left );
     if( height( t->left ) - height( t->right ) == 2 )
     {
        if( x < t->left->data )
           rotateL( t );  
        else
           rotateRL( t );
     }
         
   }
   else if( t->data < x )
   {
       insert( x, t->right );
       if( height( t->right ) - height( t->left ) == 2 )
       {
           if( t->right->data < x )
             rotateR( t );  
           else
             rotateLR( t );
       }
            
    }
    // else Duplicate do nothing
    // max_h = (height( t->left ) < height( t->right )? height( t->right ): height( t->left ));
    // h->height = max_h + 1;
}

template<class T>
void binarytree<T>::remove(T val)
{
    if(Mode) remove(val ,root);
    else remove(root, val);
}

template<class T>
void binarytree<T>::remove(Node<T> *& t, T& val) {
    if (t == NULL)  
        return;
    else if (t->data > val)
    {
        remove(t->left, val);     
    }
        
    else if (t->data < val)
    {
        remove(t->right , val);   
    }  
        
    else    // r->data == val; remove this node
    {
        if (t->left !=NULL && t->right != NULL) {
            // both children; replace w/ min from R
            t->data = min(t->right); 
            remove(t->right, t->data);
        }
        else {
           Node<T> * oldNode =t;  // only  R or L child
           t = (t->left != NULL)? t->left : t->right;
           delete oldNode;
        }
    }
        
}

template <class T>
void binarytree<T>::remove( const T& val, Node<T> *& t )
{
    if (t == NULL)  
        return;
    else if (t->data > val)
    {
        remove(val, t->left);

        if( height( t->right ) - height( t->left ) == 2 )
        {
            if(t->right->right) rotateR( t );
            else rotateLR( t ); 
        }
    }
        
    else if (t->data < val)
    {
        remove(val, t->right);

        if( height( t->left ) - height( t->right ) == 2 )
        {
            if(t->left->left) rotateL( t );
            else rotateRL( t );
        }
    }  
        
    else    // r->data == val; remove this node
    {
        if (t->left !=NULL && t->right != NULL) {
            // both children; replace w/ min from R
            t->data = min(t->right); 
            remove(t->data, t->right);

            if( height( t->right ) - height( t->left ) == 2 )
            {
                    if(t->right->right) rotateR( t );
                    else rotateLR( t ); 
            }
            if( height( t->left ) - height( t->right ) == 2 )
            {
                    if(t->left->left) 
                    {
                        rotateL( t );
                    }
                    
                    else rotateRL( t );
            }

        }
        else {
           Node<T> * oldNode =t;  // only  R or L child
           t = (t->left != NULL)? t->left : t->right;
           delete oldNode;
        }
    }
        
    
}


int main()
{
    
    binarytree<int> t;
    t.mode("AVL");
    t.set_print("side");

    for(size_t i=0;i<15;++i) t.insert(i);
    std::cout << t << std::endl;
    
    t.remove(8);
    t.remove(9);
    t.remove(10);
    t.remove(11);
    t.remove(12);
    t.remove(13);
    t.remove(14);

    std::cout << "t last:" << std::endl << std::endl << std::endl;
    std::cout << t << std::endl;


    binarytree<int> t1=t;

    std::cout << "t1 first:" << std::endl << std::endl << std::endl;
    std::cout << t1 << std::endl;

    t1.mode("AVL");
    t1.remove(3);

    std::cout << "t1 last:" << std::endl << std::endl << std::endl;
    std::cout << t1 << std::endl;

    std::cout << "t lastest:" << std::endl << std::endl << std::endl;
    std::cout << t << std::endl;



    binarytree<int> t2;
    t2.mode("AVL");

    for(size_t i=0;i<15;++i) t2.insert(i);
    std::cout << "t2 first:" << std::endl << std::endl << std::endl;
    std::cout << t2 << std::endl;

    t2=t;

    std::cout << "t2 last:" << std::endl << std::endl << std::endl;
    std::cout << t2 << std::endl;




    


    

    return 0;
}