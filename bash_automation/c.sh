#!/bin/bash

filenames=("$@")

source OS.sh

echo "Enter headers' names (n to refuse): "

read -a headers

if [ headers != "n" ];
then
	
	for filename in ${filenames[@]};
	do
  		echo "#include <stdio.h>" >> ${filename}.c
  		
  		for header in ${headers[@]};
  		do
  			echo "#include <${header}>" >> ${filename}.c
  		done
  		
  		printf "\nint main()\n{\n\n	return 0;\n}" >> ${filename}.c
  		${program} ${filename}.c &
	done

else
	for filename in ${filenames[@]};
	do
  		echo "#include <iostream>" >> ${filename}.cpp
  		
  		printf "\nint main()\n{\n\n	return 0;\n}" >> ${filename}.c
  		${program} ${filename}.c &
	done
		
fi
	

