lflags=-lncurses -lm

caesarencrypt:
	gcc -g -ggdb3 -Wall -Wextra -Wconversion -pedantic -std=gnu11 en-decrypt.h usefulfunc.h usefulfunc.c en-decrypt.c caesarencrypt.c -o caesarencrypt $(lflags)
	
polyencrypt:
	gcc -g -ggdb3 -Wall -Wextra -Wconversion -pedantic -std=gnu11 en-decrypt.h usefulfunc.h usefulfunc.c en-decrypt.c polyencrypt.c -o polyencrypt $(lflags)	

decrypt:	
	gcc -g -ggdb3 -Wall -Wextra -Wconversion -pedantic -std=gnu11 en-decrypt.h usefulfunc.h usefulfunc.c en-decrypt.c caesardecrypt.c -o caesardecrypt $(lflags)
	
piling:
	gcc -g usefulfunc.h usefulfunc.c piling.c -o piling $(lflags)
	
clean:
	rm -f caesarencrypt
	rm -f polyencrypt
	rm -f caesardecrypt
	rm -f piling
