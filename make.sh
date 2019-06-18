#!/bin/bash

filenames=("$@")
CFLAGS="-Wall -Werror -pedantic-errors"

len=$(( $# - 1 ))

for filename in ${filenames[@]};
do
  
  g++ -g ${filename}.cpp -o ${filename} ${CFLAGS}
done


#this is also doable
#for i in ${!filenames[@]};
#do
#  g++ -g ${filenames[$i]}.cpp -o ${filenames[$i]} ${CFLAGS}
#done



