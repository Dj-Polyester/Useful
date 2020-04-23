CXXFLAGS = -g -Wall -Wextra -Wpedantic
MAIN = dfa
main: 
	clear
	make clean
	if make $(MAIN); then ./$(MAIN); fi
dfa:
	g++ $(CXXFLAGS) dfa.h dfa.cpp -o dfa
	
clean:
	rm -f $(MAIN)
	