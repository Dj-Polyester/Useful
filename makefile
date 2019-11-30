CC=g++ -g
CFLAGS=-ansi -Wall -pedantic-errors -o
MAIN=matrix

main:
	clear
	make clean
	if make $(MAIN); then ./$(MAIN); fi

#the below can be customized 
$(MAIN):
	$(CC) $(MAIN).cpp  $(CFLAGS) $(MAIN)

clean:
	rm -f $(MAIN)
	