#include  <string.h>
#include "usefulfunc.h"
#include "en-decrypt.h"
#include <stdlib.h>
#include <stdio.h>

int mod(int a,int b)
{
	if(!a) return 0;
	if(a>0) return a%b;
	
	while(a<0)
	{
		a+=b;
	}
	
	return a;
	
}

char *caesar_encrypt(char *message_to_encrypt, void *shift)
{	
	int length=strlen(message_to_encrypt),i;
	char* encrypted_message;
	
	if(!message_to_encrypt) return NULL;
	
	if(!(encrypted_message=calloc(length+1,sizeof(char)))) return NULL;
	
	for(i=0;i<length;++i)
	{
		encrypted_message[i]=mod((message_to_encrypt[i]-33+*((int*)shift)),94)+33;
	}
	
	return encrypted_message;
}	

char *caesar_decrypt(char *message_to_decrypt, void *shift)
{	
	int length=strlen(message_to_decrypt),i;
	char* decrypted_message;
	
	if(!message_to_decrypt) return NULL;
	
	if(!(decrypted_message=calloc(length+1,sizeof(char)))) return NULL;
	
	for(i=0;i<length;++i)
	{
		decrypted_message[i]=mod((message_to_decrypt[i]-33-*((int*)shift)),94)+33;
	}
	
	return decrypted_message;
}	

char *polyalphabetic_encrypt(char *message_to_encrypt, void *key_string)
{
	
	int length=strlen(key_string),i,k,length2;
	char* encrypted_message,*key_string2;
	
	if(!message_to_encrypt) return NULL;
	
	if(!(key_string2=calloc(length+1,sizeof(char)))) return NULL;
	
	for(i=0;i<length;++i) key_string2[i]=*((char*)key_string+i);
	
	length2=strlen(message_to_encrypt);
	
	if(!(encrypted_message=calloc(length2+1,sizeof(char))))  return NULL;
	
	for(i=0,k=0;i<length2;++i)
	{
		
		encrypted_message[i]=mod((message_to_encrypt[i]-33+key_string2[k%length]),94)+33;
		++k;
	}
	
	if(key_string2) free(key_string2);
	return encrypted_message;	
}

char *polyalphabetic_decrypt(char *message_to_decrypt, void *key_string)
{
	
	int length=strlen(key_string),addvalue,i,k,length2;
	char* decrypted_message,*key_string2;
	
	if(!message_to_decrypt) return NULL;
	
	if(!(key_string2=calloc(length+1,sizeof(char)))) return NULL;
	
	for(i=0;i<length;++i) key_string2[i]=*((char*)key_string+i);
	
	length2=strlen(message_to_decrypt);
	
	if(!(decrypted_message=calloc(length2+1,sizeof(char))))  return NULL;
	
	for(i=0,k=0;i<length2;++i)
	{
		
		decrypted_message[i]=mod((message_to_decrypt[i]-33-key_string2[k%length]),94)+33;
		++k;
	}
	
	if(key_string2) free(key_string2);
	return decrypted_message;	
}



char **combine_strings(char **messages, int n_messages, int grouping, char *salt)
{
	int i,j,k=0,len_max=-1,length,padding_max;
	char** encrypted_messages,**encrypted_messages2;
	
	for(i=0;i<n_messages;++i)
	{
		if(!messages[i]) return NULL;
		length=strlen(messages[i]);
		if(len_max<length) len_max=length;
	}
	padding_max=n_messages*grouping*(len_max/(n_messages*grouping)+1);
	
	/*form encrypted_messages*/
	encrypted_messages=(char**)malloc(n_messages*sizeof(char*));
	for(i=0;i<n_messages;++i)
	{
		encrypted_messages[i]=calloc(padding_max+1,sizeof(char));
		length=strlen(messages[i]);
		for(j=0;j<length;j++)
		{
			encrypted_messages[i][j]=messages[i][j];
		}
		k=0;
		while(j<padding_max)
		{
			encrypted_messages[i][j]=salt[k%4];
			++j;
			++k;
		}
		
	}
	
	/*form encrypted_messages2*/
	encrypted_messages2=(char**)malloc(n_messages*sizeof(char*));
	j=0;
	for(i=0;i<n_messages;++i)
	{
		encrypted_messages2[i]=calloc(padding_max+1,sizeof(char));
		for(k=0;k<padding_max;++k)
		{
			encrypted_messages2[i][k]=encrypted_messages[j][k];
			if(k%grouping==grouping-1) ++j;
			if(j==n_messages) j-=n_messages;
		}
		++j;
	}
	
	/*free 	encrypted_messages*/
	for(i=0;i<n_messages;++i) free(encrypted_messages[i]);
	free(encrypted_messages);
	
	return encrypted_messages2;
}

/*
int main() {

	char **messages,**encrypted_messages,**decrypted_messages,*salt;
	int n_messages,grouping=4,a,i; 
	void* shift=&a;
	
	printf("n_messages: ");
	scanf("%d",&n_messages);
	getchar();
	printf("shift: ");
	scanf("%d",&a); //getchar after scanf
	getchar();
	
	if(!(messages=malloc(n_messages*sizeof(char*)))) printf("not allocated"); 
	if(!(encrypted_messages=malloc(n_messages*sizeof(char*)))) printf("not allocated"); 
	if(!(decrypted_messages=malloc(n_messages*sizeof(char*)))) printf("not allocated"); 
	
	//salt=getIn();
	
	for(i=0;i<n_messages;++i)
	{
		messages[i]=getIn();
		encrypted_messages[i]=caesar_encrypt(messages[i], shift);
		decrypted_messages[i]=caesar_decrypt(encrypted_messages[i], shift);
	}
	
	printf("\n");
	
	for(i=0;i<n_messages;++i)
	{
		printf("%s\n",encrypted_messages[i]);
	}
	
	printf("\n");
	
	for(i=0;i<n_messages;++i)
	{
		printf("%s\n",decrypted_messages[i]);
	}
	
	printf("\n");
	
	for(i=0;i<n_messages;++i)
	{
		free(messages[i]);
	}
	free(messages);
	
	for(i=0;i<n_messages;++i)
	{
		free(encrypted_messages[i]);
	}
	free(encrypted_messages);
	
	for(i=0;i<n_messages;++i)
	{
		free(decrypted_messages[i]);
	}
	free(decrypted_messages);
	
	//free(salt);
	return 0;
}

*/


	
	

