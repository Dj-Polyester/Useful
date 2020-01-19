#ifndef matrix
#define matrix

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <utility>

//limits for random matrix
#define LIMIT_M 10
#define LIMIT_N 10
#define LIMIT 100

//M is Matrix
#define M(x) x**
//V is vector
#define V(x) x*

template <class T>
class Matrix
{
	size_t m,n;
	M(T) ma=NULL;//the Matrix array
	M(T) mult_matrices(const M(T)& m1,const M(T)& m2);

	public:
		//getters
		size_t rows() const {return m;}
		size_t columns() const {return n;}

		//constructors
		Matrix();
		Matrix(size_t x, size_t y);
		Matrix(const M(T)& arr,size_t x, size_t y);
		Matrix(const Matrix & rhs);//copy constructor
		Matrix(std::string rnd,size_t rows=0, size_t columns=0);//random matrix constructor
		//destructor
		~Matrix();
		
		//operators
		template<class U>
        friend std::ostream& operator<<(std::ostream& out, const Matrix<U> &ma);
		template<class U>
        friend Matrix<U> operator+(const Matrix<U>& m1, const Matrix<U>& m2);
		template<class U>
        friend Matrix<U> operator*(const Matrix<U>& m1, const Matrix<U>& m2);
		
		Matrix<T> operator[](int index);
		Matrix<T>& operator=(const Matrix& rhs);
		T& operator()(int index1,int index2);

		//other methods
		Matrix<T> solve();

};

template<class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T> &mat)
{
	for(size_t i=0;i<mat.rows();++i)
	{
		for(size_t j=0;j<mat.columns();++j)
		{
			out << mat.ma[j][i] << " ";
		}
		out << std::endl;
	}

	return out;
}

template <class T>
Matrix<T>::Matrix(std::string rnd,size_t rows, size_t columns)
{
	time_t t;
	double num, pow_rnd;

	srand((unsigned) time(&t));
	
	if(!columns)
	{
		this->n=rand()%LIMIT_N+1;
	}
	if(!rows)
	{
		this->m=rand()%LIMIT_M+1;
	}
	if (columns && rows)
	{
		this->m=rows;
		this->n=columns;
	}
	//prepare this->ma
	this->ma=new V(T)[this->n];

	for (size_t i = 0; i < this->n; ++i)
	{
		this->ma[i]=new T[this->m];
	}

	for(size_t i=0;i<this->n;++i)
	{
		for(size_t j=0;j<this->m;++j)
		{
			pow_rnd=(double)(rand()%2);
			num=pow(-1,pow_rnd)*(double)(rand()%LIMIT);
			this->ma[i][j]=num;
		}
	}
}

template <class T>
Matrix<T>::Matrix()
{
	ma=NULL;
}

template <class T>
Matrix<T>::Matrix(size_t x, size_t y)
{
	this->m=x; this->n=y;
	this->ma=new V(T)[this->n];

	for (size_t i = 0; i < this->n; ++i)
	{
		this->ma[i]=new T[this->m];
	}
}

template <class T>
Matrix<T>::~Matrix()//destructor
{
	for (size_t i = 0; i < n; ++i)
	{
		delete ma[i];
	}
	delete [] ma;
	
}

template <class T>
Matrix<T>::Matrix(const Matrix & rhs)//copy constructor
{
	*this=rhs;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& rhs)//assignment operator
{
	delete [] this->ma;
	this->ma=NULL;
	
	this->m=rhs.m;
	this->n=rhs.n;
	this->ma=new V(T)[this->n];

	for (size_t i = 0; i < this->n; ++i)
	{
		this->ma[i]=new T[this->m];
		for (size_t j = 0; j < this->m; ++j)
		{
			this->ma[i][j]=rhs.ma[i][j];
		}	
	}
	
	return *this;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& m1, const Matrix<T>& m2)
{
	if (m1.n!=m2.m)
	{
		std::cerr << "SizeException: sizes does not match" << std::endl;
		std::exit(1);
	}
	
	Matrix<T> tmp;
	tmp.m=m1.m;
	tmp.n=m2.n;

	//prepare tmp.ma
	tmp.ma=new V(T)[m2.columns()];
	for (size_t i = 0; i < m2.columns(); ++i)
	{
		tmp.ma[i]=new T[m2.rows()];
	}

	T sum;
	
	for(size_t i=0;i<m2.columns();++i)
	{
		for(size_t j=0;j<m1.rows();++j)
		{
			sum=0;
			for(size_t k=0;k<m2.rows();k++)
			{
				sum+=m2.ma[i][k]*m1.ma[k][j];
			}
			tmp.ma[i][j]=sum;
		}
	}
	
	return tmp;
}

template <class T>
Matrix<T> operator+(const Matrix<T>& m1, const Matrix<T>& m2)
{
	if (m1.m!=m2.m || m1.n!=m2.n)
	{
		std::cerr << "SizeException: sizes does not match" << std::endl;
		std::exit(1);
	}
	
	Matrix<T> tmp;
	tmp.m=m1.m;
	tmp.n=m2.n;

	//prepare tmp.ma
	tmp.ma=new V(T)[m2.columns()];
	for (size_t i = 0; i < m2.columns(); ++i)
	{
		tmp.ma[i]=new T[m2.rows()];
	}

	for(size_t i=0;i<tmp.n;++i)
	{
		for(size_t j=0;j<tmp.m;++j)
		{
			tmp.ma[i][j]=m1.ma[i][j]+m2.ma[i][j];
		}
	}
	
	return tmp;
}

template <class T>
T& Matrix<T>::operator()(int index1,int index2)
{
	return this->ma[index1][index2];
}

template <class T>
Matrix<T>  Matrix<T>::operator[](int index)
{
	Matrix<T> tmp(this->m,1);
	
	for (size_t i = 0; i < this->m; ++i)
	{
		tmp.ma[0][i]=this->ma[index][i];
	}
	
	return tmp;
}

template <class T>
Matrix<T> Matrix<T>::solve()
{
	T tmp1,tmp2;
	Matrix<T> soln=*this;
	
	for(size_t k=0;k<this->n-1;++k)
	{
		for(size_t j=0;j<this->m;++j)
		{
			if(j==k) 
			{
				continue;
			}
			tmp1=soln.ma[k][k];  
			tmp2=soln.ma[k][j];
			
			if(!tmp1 || (tmp1==1 && !tmp2)) continue;
			for(size_t i=k;i<n;++i)
			{
				soln.ma[i][k]/=tmp1;
				soln.ma[i][j]-=soln.ma[i][k]*tmp2;
				
				// print();
			}
		}
		if(!tmp1 || (tmp1 && !tmp2)) continue;
	}
	
	return soln;
}

template <class T>
M(T) exclude(size_t m,size_t n, size_t x, size_t y, M(T) ma)
{
	M(T) tmp_ma; T tmp_T;

	for(size_t i=0;i<n;++i)
	{
		if(i!=x)
		{
			V(T) tmp;
			for(size_t j=0;j<m;++j)
			{
				if(j!=y) 
				{
					tmp_T=ma[i][j];
					tmp.push_back(tmp_T);
				}
			}
			tmp_ma.push_back(tmp);
		}
	}

	return tmp_ma;
}

#endif