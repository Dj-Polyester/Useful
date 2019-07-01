#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <ctime>

using namespace std;


class clock
{
	size_t time;

	public:
		void timer(size_t x);
		void chronometer(size_t x);
		
		clock();
		~clock();
		

};

void clock::timer(size_t x)
{
	time=x;
	while(time)
	{
		
	
	}


}

void clock::chronometer(size_t x)
{



}
clock::clock(bool choice,size_t nanosecs,size_t tick_count)
{
	if(choice)
	{
		timer(nanosecs*tick_count);
	}
	else
	{	
		chronometer(nanosecs*tick_count);
	}
}

clock::~clock()
{




}



int main()
{
	timespec ts;
	getchar();
	size_t Time=time(NULL);
	size_t nanotime= clock_gettime(CLOCK_REALTIME, &ts);
	getchar();
	
	cout << Time << endl;
	cout << nanotime << endl;
	
	return 0;
}





