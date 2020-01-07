#!/bin/bash
CXXFLAGS="-g -Wall -Wextra -Wpedantic"

array=("$@")

clear
g++ $CXXFLAGS $1.cpp -o $1
./$@



# for item in ${array[@]};
# 	do
#   		echo "#include <stdio.h>" >> ${filename}.c
  		
#   		for header in ${headers[@]};
#   		do
#   			echo "#include <${header}>" >> ${filename}.c
#   		done
  		
#   		printf "\nint main()\n{\n\n	return 0;\n}" >> ${filename}.c
#   		${program} ${filename}.c &
# 	done
