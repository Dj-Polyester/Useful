#ifndef filelist_h
#define filelist_h

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string word_in_line(string str,size_t index);
string line_in_file(string name,size_t n);
string word_in_file(string name,size_t m,size_t n);

size_t countWords(string str);
size_t countWords(string str,size_t* total_letter);
size_t fcountWords(string name,size_t n);
size_t fcountWords(string name,size_t n,size_t* total_letter);
size_t fcountWords(string name,size_t start,size_t end);
size_t fcountWords(string name,size_t start,size_t end,size_t* total_letter);

#endif
