#!/bin/bash

filenames=("$@")

source OS.sh

for filename in ${filenames[@]};
	do
  		printf "<!DOCTYPE html>\n<html lang='en'>\n<head>\n\t<meta charset='UTF-8'>\n\t<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n\t<meta http-equiv="X-UA-Compatible" content="ie=edge">\n\t<title>Document</title>\n<head>\n<body>\n\n</body>\n</html>" >> ${filename}.html
  		${program} ${filename}.html &
	done