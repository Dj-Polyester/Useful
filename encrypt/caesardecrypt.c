#include <stdio.h>
#include <stdlib.h>
#include "en-decrypt.h"
#include "usefulfunc.h"
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{

	int shift,len_chshift,init,len_filename,i=0;
	char *chshift,*line=NULL,*decrypted_line,*stripped_line,chinit,chlen_chshift;
	char *filename=NULL,*newfilename=NULL;
	FILE *oldfile=NULL;
	FILE *newfile=NULL;
	size_t lenline,len=0;
	
	
	/*printf("-9");*/
	/*FILENAME*/
	printf("Enter the file name: ");
	/*printf("-8");*/
	filename=getIn();
	/*printf("-7");*/
	if(!access(filename,F_OK))
	{
		len_filename=strlen(filename);
		/*printf("-6");*/
		i=len_filename;
		while(filename[i]!='.') --i;		
		chlen_chshift=filename[i-1];
		chlen_chshift=make_numeric(chlen_chshift);
		len_chshift=chlen_chshift-48;
		/*printf("-5");*/
		chshift=calloc(len_chshift+1,1);
		/*NEWFILENAME*/
		newfilename=calloc(i+1,1);
		/*printf("-4");*/
		strncpy(newfilename,filename,i);
		/*printf("-3");*/
		newfilename=gen_file_name(newfilename,"(decrypted).txt");
		/*printf("-2");*/
		chinit=make_numeric(filename[0]);
		init=chinit-48;
		/*SHIFT*/
		i=0;
		/*printf("-1");*/
		while(i!=len_chshift)
		{
			chshift[i]=make_numeric(filename[(i+1)*init]);
			++i;
		}
		/*printf("0");*/
		shift=atoi(chshift);
		
		/*printf("1");*/
		if(!(oldfile=fopen(filename,"r")))
		{
			perror("Error");
			if(newfilename) free(newfilename);
			if(filename) free(filename);
			if(chshift) free(chshift);
			exit(1);
		}
		/*printf("2");*/
		
		if(!(newfile=fopen(newfilename,"ab+")))
		{
			perror("Error");
			if(newfilename) free(newfilename);
			if(filename) free(filename);
			if(chshift) free(chshift);
			fclose(oldfile);
			exit(1);
		}
		while ((lenline = getline(&line, &len, oldfile)) != -1)
		{
			stripped_line=strip(line,lenline);
			decrypted_line=caesar_decrypt(stripped_line, &shift);
			if(!decrypted_line)
			{
				printf("Could not allocate memory\n");
				if(newfilename) free(newfilename);
				if(filename) free(filename);
				if(chshift) free(chshift);
				exit(1);
			}
			
			fprintf(newfile,"%s\n",decrypted_line);
			
			if(decrypted_line) free(decrypted_line);
			decrypted_line=NULL;
			
			free(line);
			line=NULL;
			stripped_line=NULL;
			decrypted_line=NULL;
		}
		free(line);
		line=NULL;
	}
	else
	{
		printf("Cannot access the file.");
		if(filename) free(filename);
		exit(0);
	}
	
	if(newfilename) free(newfilename);
	if(filename) free(filename);
	if(chshift) free(chshift);
	fclose(oldfile);
	fclose(newfile);
	return 0;
}


