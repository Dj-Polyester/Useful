CXXFLAGS = -g -Wall -Wextra -Wpedantic
MAIN = binarytree
main: 
	clear
	make clean
	if make $(MAIN); then ./$(MAIN); fi

stack_queue:
	g++ $(CXXFLAGS) linkedlist.hpp stack_queue.hpp stack_queue.cpp -o stack_queue
	
linkedlist:
	g++ $(CXXFLAGS) linkedlist.hpp linkedlist.cpp -o linkedlist
	
binarytree:
	g++ $(CXXFLAGS) binarytree.cpp -o binarytree

clean:
	rm -f linked_list_circle
	rm -f stack_queue
	rm -f linkedlist
	rm -f binarytree