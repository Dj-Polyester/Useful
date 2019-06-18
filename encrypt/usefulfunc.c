#include <stdio.h>
#include <stdlib.h>
#include "usefulfunc.h"
#include <ncurses.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

int in_charray(char item,char* array,int length)
{
	int i;
	for(i=0;i<length;++i)
	{
		if(array[i]==0) continue;
		if(array[i]==item) return i;
	}
	
	return -1;
}

int in_intarray(int item,int* array,int length)
{
	int i;
	for(i=0;i<length;++i)
	{
		if(array[i]==item) return i;
	}
	
	return -1;
}

char* gen_file_name(char* filename,char* format)
{
	char* tmp;
	int len_filename=strlen(filename), len_format=strlen(format),i;
	
	if(!(tmp=realloc(filename,len_filename+len_format+1))) return NULL;
	
	filename=tmp;
	tmp=NULL;
	
	for(i=0;i<len_format;++i) filename[i+len_filename]=format[i];
	
	filename[len_filename+len_format]=0;
	
	return filename;

}

char make_numeric(char ch)
{
	if(ch<91 && ch>63) return ch-16;
	if(ch<123 && ch>95) return ch-48;
	if(ch<58 && ch>47) return ch;
	return ch+16;
}

char* strip(char* str,int length)
{
	char *start=str,*end=&str[length-1];
	
	while(*start>0 && *start<33 || *start==127) ++start;
	if(!*start) return start;
	
	while(*end>=0 && *end<33 || *end==127) --end;
	++end;
	*end=0;
	
	return start;

}


char* gen_rand_name(int len,int count,...)
{
	int i,assigner;
	char* rand_name=calloc(len+1,1),assignee;
	va_list va_args;
	time_t t;
	
	srand((unsigned) time(&t));
	va_start(va_args, count);
	
	for(i=0;i<len;++i)
	{
		rand_name[i]=(char)(rand()%94+33);
	}
	
	if(!count) return rand_name;
	
	for(i=0;i<count;++i)
	{
		if(i%2)
		{
			assigner=va_arg(va_args, int);
			rand_name[assigner]=assignee;
		}
		else
		{
			assignee=(char)va_arg(va_args, int);
		}
	}

	va_end(va_args);

	return rand_name;
}

char *name_file(char *filename)
{
	if(!filename) return NULL;
	
	int count=1,lenfilename=0,lensofi,lenformat,i;
	char *tmp=NULL,*sofi=NULL,*format=NULL,*format_tmp;
	
	while(filename[lenfilename]!='.') ++lenfilename;

	format=&filename[lenfilename];
	lenformat=strlen(format);
	
	if(!(tmp=calloc(lenformat+1,1))) return NULL;
	format_tmp=tmp;
	tmp=NULL;
	
	strcpy(format_tmp,format);
	format=NULL;
		
	while(!access(filename,F_OK))
	{
		
		sofi=itos(count);
		lensofi=strlen(sofi);
		
		if(!(tmp=realloc(filename,lenfilename+lenformat+lensofi+3))) return NULL;
		filename=tmp;
		tmp=NULL;
		
		if(count==1) filename[lenfilename]='(';
		filename[lenfilename+lensofi+1]=')';
		
		for(i=0;i<lensofi;++i) filename[i+lenfilename+1]=sofi[i];
		filename[lenfilename+lensofi+2]=0;
		strcat(filename,format_tmp);
		
		++count;
	}
	
	if(format_tmp) free(format_tmp);
	return filename;
}

char* itos(int a)
{
	char *digitlist=NULL, *tmp=NULL;
	int digit,i=0,decimal=10,count=1;
	
	if(a)
	{
		while(a/decimal)
		{
			decimal*=10;
			++count;
		}
	}
	
	if(!(tmp=calloc(count+1,sizeof(char))))
	{
		if(digitlist) free(digitlist);
		return NULL;
	}
	digitlist=tmp;
	
	for(i=0;i<count;++i)
	{
		
		digit=a%decimal/(decimal/10);
		digitlist[i]=digit+48;
		decimal/=10;
	}
	
	return digitlist;
}

int gcd(int a,int b)
{
	
	while (a-b) 
	{
		if(a<b) b-=a;
	
		else if(b<=a) a-=b;
	
	}
	return a;

}
int lcm(int a,int b)
{
	int num1=a;
	int num2=b;
	while (a-b) 
	{
		if(a<b) b-=a;
	
		else if(b<=a) a-=b;
	
	}
	
	return num1*num2/a;
}
int isprime(int num)
{
	int i;
	/*float fum;
	fum=(float)num;*/
	for(i=2;i<sqrt(num);++i)
	{
		if (!(num%i)) return 0;
	}
	return 1;
}
int kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

int kbwait(char k) 
{
    char c;
    
   initscr ();
  	noecho ();

    while (1)
    {
      c = getch ();
   
      if (c == k)
      {
        break;
      }
    }

 	echo ();
  	endwin ();
    return 0;
}

int min(int *array,int count)
{
    int min;
    for(int i=0;i<count;i++)
    {
        if (i==0 || array[i] < min) min=array[i];

    }
    return min;
}

int nmin(int *array,int count)
{
    int min,index;
    for(int i=0;i<count;i++)
    {
        if (i==0 || array[i] < min)
        {
            index=i;
            min=array[i];
        }
    }
    return index;
}

int max(int *array,int count)
{
    int max;
    for(int i=0;i<count;i++)
    {
        if (i==0 || array[i] > max)  max=array[i];
    }
    return max;
}
int nmax(int *array,int count)
{
    int max,index;
    for(int i=0;i<count;i++)
    {
        if (i==0 || array[i] > max)
        {
            index=i;
            max=array[i];
        }
    }
    return index;
}

void invert_array(int* array,const int count)
{
    for(int i=0;i<count/2;i++) swap(&array[i],&array[count-1-i]);
}

void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

char* getIn() 
{
    char *line = NULL, *tmp = NULL;
    size_t size = 0, index = 0;
    int ch = EOF;

    while (ch) {
        ch = getc(stdin);

        /* Check if we need to stop. */
        if (ch == EOF || ch == '\n')
            ch = 0;

        /* Check if we need to expand. */
        if (size <= index) {
            size += sizeof(char);
            tmp = realloc(line, size);
            if (!tmp) {
                free(line);
                line = NULL;
                break;
            }
            line = tmp;
        }

        /* Actually store the thing. */
        line[index++] = ch;
    }

    return line;
}

int len(char* array)
{
	int i=0;
	while (array[i]) i++;
	
	return i;
	
}

int charindex(char* array,char ch)
{
	int i=0;
	while(array[i])
	{
		if (array[i]==ch) return i;
		++i;
	}
	return -1;
}


