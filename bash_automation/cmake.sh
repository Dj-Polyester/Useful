#!/bin/bash

filenames=("$@")
LFLAGS="-lncurses -lm"
CFLAGS="-ggdb3 -Wall -Wextra -Wconversion -pedantic-errors"


echo "Enter headers' names(n to refuse): "

read -a headers


if [ headers != "n" ];
then
	for filename in ${filenames[@]};
	do
	#if exists, removes the file for redoability
	if [ -f $filename ];
	then
		rm -f ${filename}
	fi
	
  		gcc -g ${filename}.c -o ${filename} ${headers[@]} ${CFLAGS} ${LFLAGS}
	done

	#this is also doable
	#for i in ${!filenames[@]};
	#do
	#  gcc -g ${filenames[$i]}.cpp -o ${filenames[$i]} ${headers[@]} ${CFLAGS} ${LFLAGS}
	#done

	
fi








