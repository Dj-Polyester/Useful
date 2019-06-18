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

	int shift,len_chshift,init,len_filename,i=0;
	char *chshift,chinit,choice,chlen_chshift,*tmp;
	char *filename=NULL,*inp,answer;
	FILE *newfile=NULL;
	time_t t; srand((unsigned) time(&t));
	
	/**/
	init=rand()%9+1;
	
	choice=rand()%4;
	/*printf("%d\n",choice);*/
	if(choice==0)  chinit=init+64;
	else if (choice==1) chinit=init+96;
	else if (choice==2) chinit=init+32;
	else chinit=init+48;
	
	printf("Shift: ");
	
	scanf("%d",&shift);
	getchar();
	
	chshift=itos(shift);
	len_chshift=strlen(chshift);
	
	choice=rand()%4;
	/*printf("%d\n",choice);*/
	if(choice==0)  chlen_chshift=len_chshift+64;
	else if (choice==1) chlen_chshift=len_chshift+96;
	else if (choice==2) chlen_chshift=len_chshift+32;
	else chlen_chshift=len_chshift+48;
	/**/
	
	len_filename=rand()%(len_chshift*init)+(len_chshift*init+2);
	
	/*printf("%d\n",len_filename);*/
	
	filename=gen_rand_name(len_filename,4,chinit,0,chlen_chshift,len_filename-1);
	filename=gen_file_name(filename,".txt");
	
	while(chshift[i])
	{
		choice=rand()%4;
		/*printf("%d\n",choice);*/
		if(choice==0)  chshift[i]+=16;
		else if (choice==1) chshift[i]+=48;
		else if (choice==2) chshift[i]-=16;
		
		filename[(i+1)*init]=chshift[i];
		++i;
	}
	
	filename=name_file(filename);
	
	free(chshift);
	
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
				tmp=caesar_encrypt(inp, &shift);
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
	if(filename) free(filename);
	fclose(newfile);
	return 0;
}


