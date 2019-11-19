CXXFLAGS = -g -Wall -Wextra -Wpedantic

define f
$(1).hpp $(1).cpp
endef

linkedlist:
	g++ $(CXXFLAGS) linkedlist.hpp linkedlist.cpp -o linkedlist

usefulfunc:
	g++  $(call f, usefulfunc) -o use

main: complex string

clean:
	rm -f string
	rm -f complex
	rm -f linkedlist
	rm -f use
