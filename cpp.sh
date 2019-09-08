#!/bin/bash

filenames=("$@")

echo "Enter headers' names (n to refuse): "

read -a headers

if [ headers != "n" ];
then
	
	for filename in ${filenames[@]};
	do
  		echo "#include <iostream>" >> ${filename}.cpp
  		
  		for header in ${headers[@]};
  		do
  			echo "#include <${header}>" >> ${filename}.cpp
  		done
  		
  		printf "\nusing namespace std;\n\nint main()\n{\n\n	return 0;\n}" >> ${filename}.cpp
  		gedit ${filename}.cpp &
	done

else
	for filename in ${filenames[@]};
	do
  		echo "#include <iostream>" >> ${filename}.cpp
  		
  		printf "\nusing namespace std;\n\nint main()\n{\n\n	return 0;\n}" >> ${filename}.cpp
  		gedit ${filename}.cpp &
	done
		
fi
	

