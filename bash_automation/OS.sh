# Linux
if [[ "$OSTYPE" == "linux-gnu" ]];
then
program=gedit
# Mac OSX
elif [[ "$OSTYPE" == "darwin"* ]];
then
program=open -a Xcode
# Windows       
elif [[ "$OSTYPE" == "cygwin" ]] || [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "win32" ]];
then
program=code
# Other OS (not defined here-Error)
else
echo "Error: did not recognise the operating system"
fi
