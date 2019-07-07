#include "clock.h"

using namespace std;

extern size_t max_x,max_y,mid_x,mid_y;

clock_time::clock_time(size_t x,size_t y,size_t z,size_t t){set( x, y, z, t);if(is_file)myfile.open("count.txt");}
clock_time::clock_time(size_t y,size_t z,size_t t){set(y, z, t);if(is_file)myfile.open("count.txt");}
clock_time::clock_time(size_t z,size_t t){set( z, t);if(is_file)myfile.open("count.txt");}
clock_time::clock_time(size_t t){set( t);if(is_file)myfile.open("count.txt");}
clock_time::clock_time(){set();if(is_file)myfile.open("count.txt");}

clock_time::~clock_time(){set();if(is_file)myfile.close();}


void clock_time::set(size_t x,size_t y,size_t z,size_t t){h=x;min=y;sec=z;split_sec=t;}
void clock_time::set(size_t y,size_t z,size_t t){h=0;min=y;sec=z;split_sec=t;}
void clock_time::set(size_t z,size_t t){h=0;min=0;sec=z;split_sec=t;}
void clock_time::set(size_t t){h=0;min=0;sec=0;split_sec=t;}
void clock_time::set(){h=0;min=0;sec=0;split_sec=0;}

void clock_time::forward(){flow=true;}
void clock_time::backward(){flow=false;}

void clock_time::Timer(size_t x,size_t y,size_t z,size_t t,bool p) {set( x, y, z, t);backward();Time(p);}
void clock_time::Timer(size_t y,size_t z,size_t t,bool p) {set( y, z, t);backward();Time(p);}
void clock_time::Timer(size_t z,size_t t,bool p){set( z, t);backward();Time(p);}
void clock_time::Timer(size_t t,bool p){set( t);backward();Time(p);}
void clock_time::Timer(bool p){backward();Time(p);}
void clock_time::Timer(size_t x,size_t y,size_t z,size_t t,bool p,WINDOW* win) {set( x, y, z, t);backward();Time(p,win);}
void clock_time::Timer(size_t y,size_t z,size_t t,bool p,WINDOW* win) {set( y, z, t);backward();Time(p,win);}
void clock_time::Timer(size_t z,size_t t,bool p,WINDOW* win){set( z, t);backward();Time(p,win);}
void clock_time::Timer(size_t t,bool p,WINDOW* win){set( t);backward();Time(p,win);}
void clock_time::Timer(bool p,WINDOW* win){backward();Time(p,win);}

void clock_time::chronomtr(size_t x,size_t y,size_t z,size_t t,bool p){set( x, y, z, t);forward();Time(p);}
void clock_time::chronomtr(size_t y,size_t z,size_t t,bool p){set( y, z, t);forward();Time(p);}
void clock_time::chronomtr(size_t z,size_t t,bool p){set( z, t);forward();Time(p);}
void clock_time::chronomtr(size_t t,bool p){set( t);forward();Time(p);	}
void clock_time::chronomtr(bool p){forward();Time(p);}
void clock_time::chronomtr(size_t x,size_t y,size_t z,size_t t,bool p,WINDOW* win){set( x, y, z, t);forward();Time(p,win);}
void clock_time::chronomtr(size_t y,size_t z,size_t t,bool p,WINDOW* win){set( y, z, t);forward();Time(p,win);}
void clock_time::chronomtr(size_t z,size_t t,bool p,WINDOW* win){set( z, t);forward();Time(p,win);}
void clock_time::chronomtr(size_t t,bool p,WINDOW* win){set( t);forward();Time(p,win);	}
void clock_time::chronomtr(bool p,WINDOW* win){forward();Time(p,win);}

void clock_time::print(WINDOW* win)
{
        wrefresh(win);
        mvwprintw( win, 1, 1, "%02d:", h );
	mvwprintw( win, 1, 4, "%02d:", min );
	mvwprintw( win, 1, 7, "%02d:", sec );
	mvwprintw( win, 1, 10, "%02d", split_sec );
	
}

void clock_time::print() {FILE << h << ':' << min << ':' << sec << ':' << split_sec << endl;}

#ifdef _WIN32
    void time_wait(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    void time_wait(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif


void clock_time::Time(bool p,WINDOW* win)
{
	size_t ch;
	
	nodelay(win, TRUE);
	cbreak();
	while((ch=wgetch(win))!=pause)//stop or continue
	{
		if(ch==lap) myfile << h <<":"<< min <<":"<< sec <<":"<< split_sec << endl;
		if(flow)//forward
		{
			++split_sec;
			time_wait(100);
			if(split_sec>9) { split_sec=0; ++sec; }
			if(sec>TICK-1) { sec=0; ++min; }
			if(min>TICK-1) { min=0; ++h; }
			if(p) print(win);
		}
		else//backward
		{
			
			time_wait(100);
			if(h==0 && min==0 && sec==0 && split_sec<0)
			{
				myfile << "     STOP\n";
				
				break;
			}
			if(split_sec==0 && sec>0) { split_sec=9; --sec; }
			if(sec==0 && min>0) { sec=TICK-1; --min; }
			if(min==0 && h>0) { min=TICK-1; --h; }
			
			
			if(p) print(win);
			--split_sec;
			
		}
	}
	
	nodelay(win, FALSE);
}
void clock_time::Time(bool p)
{
	while(val)//stop or continue
	{
		if(flow)//forward
		{
			++split_sec;
			time_wait(100);
			if(split_sec==10) { split_sec=0; ++sec; }
			if(sec==TICK) { sec=0; ++min; }
			if(min==TICK) { min=0; ++h; }
			if(p) print();
		}
		else//backward
		{
			--split_sec;
			time_wait(100);
			if(split_sec==0) { split_sec=10; --sec; }
			if(sec==0) { sec=TICK; --min; }
			if(min==0) { min=TICK; --h; }
			if(p) print();
			if(!h) break;
		}
	
	}
}
