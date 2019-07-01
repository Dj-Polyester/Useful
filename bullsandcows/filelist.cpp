#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string word_in_line(string str,size_t index) //returns nth index word in a line
{
	if(str=="") return "";
	
	string word;
	size_t count=0,i=0;
	bool enable=true;
	char ch;
	
	do
    	{
    		ch=str[i++];
    	
    		if((ch>90 || ch<65) && (ch>122 || ch<97)) continue;
    		enable=false;
    		do
    		{
    			if(count==index) word.append(&ch);
    			ch=str[i++];
    		}while((ch<91 && ch>64) || (ch<123 && ch>96));
    		
    		++count;
    		
    	}while(str[i] || enable==true);
	
	
	if(enable==true) return "";
	return word;
}

string line_in_file(string name,size_t n) //returns nth line in a file
{
	if(name=="") return "";
	
	string line;
	size_t count=0;
	
	ifstream file;
	file.open(name);
	
	if (!(file.is_open()))
	{
		perror("Cannot open the file");
		exit(1);
	}
	
	while(getline(file,line))
	{
		++count;
		if(count==n) return line;
	
	}
	
	file.close();
	return "";
}

string word_in_file(string name,size_t m,size_t n)
{
	return word_in_line(line_in_file(name,m),n);  
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

size_t countWords(string str) //word count of a line
{ 
    size_t i=0,count=0;
    char ch;
    
    if(!str.size()) return 0;
    do
    {
    	ch=str[i++];
    	
    	if((ch>90 || ch<65) && (ch>122 || ch<97)) continue;
    	
    	do
    	{
    		ch=str[i++];
    	}while((ch<91 && ch>64) || (ch<123 && ch>96));
    	
    	++count;
    	
    }while(str[i]);
    
    return count;
} 

size_t countWords(string str,size_t* total_letter) //word and letter count of a line
{ 
    size_t i=0,count=0,word_letter;
    char ch;
    *total_letter=0;
    
    if(!str.size()) return 0;
    do
    {
    	ch=str[i++];
    	
    	if((ch>90 || ch<65) && (ch>122 || ch<97)) continue;
    	
    	word_letter=0;
    	
    	do
    	{
    		ch=str[i++];
    		++word_letter;
    		
    		
    	}while((ch<91 && ch>64) || (ch<123 && ch>96));
    	
    	++count;
    	(*total_letter)+=word_letter;
  	
    }while(str[i]);
    
    return count;
} 

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

size_t fcountWords(string name,size_t n) //word count at nth line
{
	string line;
	size_t i=0;
	
	ifstream file;
	file.open(name);
	
	if (!(file.is_open()))
	{
		perror("Cannot open the file");
		exit(1);
	}
	while (getline(file, line))
	{
		++i;
		if(i==n) break;
	}
	file.close();		
	return countWords(line);
}

size_t fcountWords(string name,size_t n,size_t* total_letter) //word and letter count at nth line
{
	string line;
	size_t i=0;
	
	ifstream file;
	file.open(name);
	
	if (!(file.is_open()))
	{
		perror("Cannot open the file");
		exit(1);
	}
	while (getline(file, line))
	{
		++i;
		if(i==n) break;
	}
	file.close();		
	return countWords(line,total_letter);
}

size_t fcountWords(string name,size_t start,size_t end) //count every word between start-end
{
	string line;
	size_t words=0,i=0,sum=0;
	
	ifstream file;
	file.open(name);
	
	if (!(file.is_open()))
	{
		perror("Cannot open the file");
		exit(1);
	}
	while (getline(file, line))
	{
		++i;
		if(i>=start && i<=end)
		{
			if(line.size())
			{
				words=countWords(line);
				sum+=words;
			}
		
		}
		else if(i>end) break;
	}
	file.close();
	return sum;
}


size_t fcountWords(string name,size_t start,size_t end,size_t* total_letter) //count every word and letter between start-end
{
	string line;
	size_t words=0,i=0,sum=0,line_letter;
	
	*total_letter=0;
	ifstream file;
	file.open(name);
	
	if (!(file.is_open()))
	{
		perror("Cannot open the file");
		exit(1);
	}
	while (getline(file, line))
	{
		++i;
		if(i>=start && i<=end)
		{
			if(line.size())
			{
				words=countWords(line,&line_letter);
				(*total_letter)+=line_letter;
				sum+=words;
			}
		
		}
		else if(i>end) break;
	}
	file.close();
	return sum;
}
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////



/*
int main()
{
	size_t data1,data2,start,end;
	size_t m,n;
	cout << "write coordinates:"; cin >> m >> n;cout << word_in_file("words.txt",m,n);
	size_t i;int ch;
	srand((unsigned int) time(NULL));
	while((ch=getchar())!=27)
	{
		cout << "write numero: ";
	
		choose("words.txt",ch);
		
	}
	
	cout << "index: ";
	cin >> start >> end;
	
	cout << "1)))))))))" << endl;
	cout << fcountWords("words.txt",start) << endl;
	
	cout << "2)))))))))" << endl;
	cout << fcountWords("words.txt",start,end) << endl;
	
	cout << "3)))))))))" << endl;
	cout << fcountWords("words.txt",start,&data1) << endl;
	cout << data1 << endl;
	
	cout << "4)))))))))" << endl;
	cout << fcountWords("words.txt",start,end,&data2) << endl;
	cout << data2 << endl;
	
	return 0;
}

*/










