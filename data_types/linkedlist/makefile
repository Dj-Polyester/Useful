CXXFLAGS = -g -Wall -Wextra -Wpedantic
MAIN = linkedlist
main: 
	clear
	make clean
	if make $(MAIN); then ./$(MAIN); fi

linkedlist:
	g++ $(CXXFLAGS) linkedlist.h linkedlist.cpp -o linkedlist

clean:
	rm -f linkedlist
	