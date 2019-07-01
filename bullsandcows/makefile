CFLAGS=-Wall -Werror -pedantic-errors

templates:
	g++ -g templates.cpp -o templates $(CFLAGS)

while:
	g++ -g while.cpp -o while $(CFLAGS)
	
bullsandcows:
	g++ -g filelist.h filelist.cpp bullsandcows.cpp -o bullsandcows $(CFLAGS)
	
clean:
	rm -f while
	rm -f bullsandcows
