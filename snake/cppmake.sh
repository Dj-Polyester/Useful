#!/bin/bash

filenames=("$@")

CFLAGS="-ggdb3 -Wall -Wextra -Wconversion -pedantic-errors -lncurses"


#echo "Enter headers' names(n to refuse): "

#read -a headers


if [ headers != "n" ];
then
	for filename in ${filenames[@]};
	do
	#if exists, removes the file for redoability
	if [ -f $filename ];
	then
		rm -f ${filename}
	fi
	
  		g++ -g ${filename}.cpp -o ${filename}  ${CFLAGS}
	done

	#this is also doable
	#for i in ${!filenames[@]};
	#do
	#  g++ -g ${filenames[$i]}.cpp -o ${filenames[$i]} ${headers[@]} ${CFLAGS}
	#done

	
fi








