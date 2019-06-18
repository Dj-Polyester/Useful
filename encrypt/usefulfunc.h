#ifndef USEFULFUNC
#define USEFULFUNC

int in_intarray(int item,int* array,int length);
int in_charray(char item,char* array,int length);
char* strip(char* str,int length);
char make_numeric(char ch);
char* gen_file_name(char* filename,char* format);
char* gen_rand_name(int len,int count,...);
char *name_file(char *filename);
char* itos(int a);
int charindex(char* array,char ch);
int gcd(int a,int b);
int lcm(int a,int b);
int isprime(int num);
int kbhit();
int kbwait(char k);
int min(int *array,int count);
int max(int *array,int count);
void invert_array(int* array,const int count);
void swap(int *a,int *b);
char* getIn();
int len(char* array);
int nmax(int *array,int count);

#endif
