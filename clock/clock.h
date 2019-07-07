#ifdef _WIN32
    #include <windows.h>
    #define ENTER 13

#else
    #include <unistd.h>
    #define ENTER 10
#endif

#ifndef clock_time_H
#define clock_time_H

#include <iostream>
#include <ncurses.h>
#include <fstream>

#define TICK 60
#define FILE cout
#define OPTIONS 2
#define MAX_LEN 12
#define SPRINTF(x)  "%-"#x"s"
using namespace std;


void time_wait(unsigned milliseconds);

class clock_time
{
	int h,min,sec,split_sec;
	bool val,flow,is_file=true;//will open-close file if true
	ofstream myfile;
	char lap='e',pause=32;
	
	/*1 for continue,0 for stop*//*1 if forward, 0 if backward*/
	
	public:
		clock_time(size_t x,size_t y,size_t z,size_t t);
		clock_time(size_t x,size_t y,size_t z);
		clock_time(size_t x,size_t y);
		clock_time(size_t x);
		clock_time();
		~clock_time();
		
		//set
		void set(size_t x,size_t y,size_t z,size_t t);
		void set(size_t y,size_t z,size_t t);
		void set(size_t z,size_t t);
		void set(size_t t);
		void set();
		
		//main
		void Time(bool p,WINDOW* win);
		void Time(bool p);
		void forward();
		void backward();
		//Timer
		void Timer(size_t x,size_t y,size_t z,size_t t,bool p);
		void Timer(size_t y,size_t z,size_t t,bool p);
		void Timer(size_t z,size_t t,bool p);
		void Timer(size_t t,bool p);
		void Timer(bool p);
		void Timer(size_t x,size_t y,size_t z,size_t t,bool p,WINDOW* win);
		void Timer(size_t y,size_t z,size_t t,bool p,WINDOW* win); 
		void Timer(size_t z,size_t t,bool p,WINDOW* win);
		void Timer(size_t t,bool p,WINDOW* win);
		void Timer(bool p,WINDOW* win);
		//chronometer
		void chronomtr(size_t x,size_t y,size_t z,size_t t,bool p);
		void chronomtr(size_t y,size_t z,size_t t,bool p);
		void chronomtr(size_t z,size_t t,bool p);
		void chronomtr(size_t t,bool p);
		void chronomtr(bool p);
		void chronomtr(size_t x,size_t y,size_t z,size_t t,bool p,WINDOW* win);
		void chronomtr(size_t y,size_t z,size_t t,bool p,WINDOW* win);
		void chronomtr(size_t z,size_t t,bool p,WINDOW* win);
		void chronomtr(size_t t,bool p,WINDOW* win);
		void chronomtr(bool p,WINDOW* win);
		
		//print
		void print();
		void print(WINDOW* win);
};

#endif
