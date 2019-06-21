#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>


#define LIMIT 10
#define LIMIT_M 10
#define LIMIT_N 10

using namespace std;

typedef double no;
typedef vector<vector<no> > M;
typedef vector<no> V;


void print_matrix(M vec2d);

M solve_sys(M ma)
{
	size_t m=ma[0].size();
	size_t n=ma.size();
	no tmp1,tmp2;
	
	for(size_t k=0;k<n-1;++k)
	{
		for(size_t j=0;j<m;++j)
		{
			if(j==k) 
			{
				continue;
			}
			tmp1=ma[k][k];  
			tmp2=ma[k][j];
			
			if(!tmp1 || (tmp1==1 && !tmp2)) continue;
			for(size_t i=k;i<n;++i)
			{
				ma[i][k]/=tmp1;
				ma[i][j]-=ma[i][k]*tmp2;
				
				print_matrix(ma);
			}
		}
		if(!tmp1 || (tmp1 && !tmp2)) continue;
	}
	
	return ma;
}

M mult_matrices(M m1, M m2)
{
	M m3;
	no sum;
	size_t l=m1.size();
	size_t m=m1[0].size();
	size_t n=m2.size();
	
	for(size_t i=0;i<m;++i)
	{
		V tmp;
		for(size_t j=0;j<n;j++)
		{
			sum=0;
			for(size_t k=0;k<l;k++)
			{
				sum+=m2[i][k]*m1[k][j];
			}
			tmp.push_back(sum);
		}
		m3.push_back(tmp);
	}
	
	return m3;
}

M add_matrices(M m1, M m2)
{
	M m3;
	size_t length1=m1.size();
	
	for(size_t i=0;i<length1;++i)
	{
		size_t length2=m1[i].size();
		V tmp;
		
		for(size_t j=0;j<length2;j++)
		{
			tmp.push_back(m1[i][j]+m2[i][j]);
		}
		m3.push_back(tmp);
	}
	
	return m3;
}

void print_matrix(M vec2d)
{
	size_t length1=vec2d[0].size();
	for(size_t i=0;i<length1;++i)
	{
		size_t length2=vec2d.size();
		for(size_t j=0;j<length2;j++)
		{
			cout << vec2d[j][i] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


M matrix(int m,int n, ...)
{
	M vec2d;
	va_list iter;
	va_start(iter,n);
	no* vec;
	
	for(int i=0;i<m;++i)
	{
		V tmp;
		vec=va_arg(iter, no*);
		
		for(int j=0;j<n;j++)
		{
			tmp.push_back(vec[j]);
		}
		
		vec2d.push_back(tmp);
	}
	
	
	return vec2d;
}

M matrix_rnd(int count,...)
{
	M vec2d;
	time_t t;
	int m,n;
	no num,pow_rnd;
	
	srand((unsigned) time(&t));
	
	if(!count)
	{
		m=rand()%LIMIT_M;
		n=rand()%LIMIT_N;
	}
	else 
	{
		va_list iter;
		va_start(iter,count);
		if(count==1)
		{
			m=va_arg(iter, int);
		}
		else
		{
			m=va_arg(iter, int);
			n=va_arg(iter, int);
		}
	}
	for(int i=0;i<n;++i)
	{
		V tmp;
		
		for(int j=0;j<m;j++)
		{
			pow_rnd=(no)(rand()%2);
			num=pow(-1,pow_rnd)*(no)(rand()%LIMIT);
			tmp.push_back(num);
		}
		
		vec2d.push_back(tmp);
	}
	
	
	return vec2d;

}

int main()
{
	M m1=matrix_rnd(2,5,6);
	
	print_matrix(m1);
	
	solve_sys(m1);
	
	
	
	
	
	return 0;
}

