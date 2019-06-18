#include <stdio.h>
#include <stdlib.h>
#include "en-decrypt.h"
#include "usefulfunc.h"
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>




int main()
{

	
	char *finder,*holder,*keyword,chshift,chinit,choice,chlen_keyword,*tmp;
	char *filename=NULL,*inp,answer;
	int shift,init,len_filename,i=0,len_keyword,char_max=0,rand_finder;
	FILE *newfile=NULL;
	time_t t; srand((unsigned) time(&t));
	
	/*INIT*/
	init=rand()%9+1;
	choice=rand()%4;
	/*printf("%d\n",choice);*/
	if(choice==0) chinit=init+64;
	else if (choice==1) chinit=init+96;
	else if (choice==2) chinit=init+32;
	else chinit=init+48;
	
	/*SHIFT*/
	shift=rand()%9+1;
	choice=rand()%4;
	if(choice==0) chshift=shift+64;
	else if (choice==1) chshift=shift+96;
	else if (choice==2) chshift=shift+32;
	else chshift=shift+48;
	
	/*KEYWORD 1 (CHKEYWORD)*/
	printf("Keyword: ");
	keyword=getIn();
	len_keyword=strlen(keyword);
	choice=rand()%4;
	if(choice==0)  chlen_keyword=len_keyword+64;
	else if (choice==1) chlen_keyword=len_keyword+96;
	else if (choice==2) chlen_keyword=len_keyword+32;
	else chlen_keyword=len_keyword+48;
	
	/*FINDER CHAR_MAX*/
	finder=calloc(len_keyword+1,1);
	holder=calloc(len_keyword+1,1);
	
	for(i=0;i<len_keyword;++i)
	{
		do
		{
			rand_finder=rand()%9+1;
			finder[i]=rand_finder+48;
		}while(finder[i] && in_charray(finder[i],holder,len_keyword)>-1);
		 
		
		if(rand_finder>char_max) char_max=rand_finder;
		holder[i]=finder[i];
	}
	
	printf("%s\n",finder);
	printf("%s\n",holder);
	
	if(holder) free(holder);
	holder=NULL;
	
	/*FILENAME KEYWORD 2*/
	len_filename=rand()%(len_keyword*init)+(len_keyword*(init+1)+char_max+2);
	filename=gen_rand_name(len_filename,4,chinit,0,chlen_keyword,len_filename-1,chshift,len_filename-1-len_keyword);
	filename=gen_file_name(filename,".txt");
	
	i=0;
	while(finder[i])
	{
		filename[len_keyword*init+finder[i]-48]=keyword[i]+shift;
		
		choice=rand()%4;
		/*printf("%d\n",choice);*/
		if(choice==0)  finder[i]+=16;
		else if (choice==1) finder[i]+=48;
		else if (choice==2) finder[i]-=16;
		
		filename[(i+1)*init]=finder[i];
		++i;
	}

	filename=name_file(filename);
	
	if(finder) free(finder);
	finder=NULL;
	
	
	/*NEWFILE*/
	if(!(newfile=fopen(filename,"ab+")))
	{
		perror("Error");
		if(filename) free(filename);
		exit(1);
	}
	
	printf("Write now? (y/n): ");
	
	while(1)
	{	
		
		scanf("%c",&answer);
		getchar();
		if(answer!='y' && answer!='n') 
		{
			printf("Invalid answer\n");
			printf("Write now? (y/n): ");
		}
		else break;
	}
	if(answer=='y')
	{
		while(1)
		{
			inp=getIn();
			if(!inp)
			{
				printf("Could not allocate memory\n");
				if(filename) free(filename);
				exit(1);
			}
			else if(*inp==0)
			{
				free(inp);
				break;
			}
			else
			{
				tmp=polyalphabetic_encrypt(inp, keyword);
				free(inp);
				inp=NULL;
				inp=tmp;
				tmp=NULL;
				if(!inp)
				{
					printf("Could not allocate memory\n");
					if(filename) free(filename);
					exit(1);
				}
				fprintf(newfile,"%s\n",inp);
				
				free(inp);
				inp=NULL;
			}
		}
		
	}
	if(keyword) free(keyword);
	if(filename) free(filename);
	fclose(newfile);
	return 0;
}


