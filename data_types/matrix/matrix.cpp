#include "matrix.h"


int main()
{
	Matrix<double> ma1("rnd",3,4);
	Matrix<double> ma2=ma1.solve();
	
	// ma2(0,0)=3;
	// ma2(0,1)=7;
	// ma2(1,0)=2;
	// ma2(1,1)=5;
	// ma2(2,0)=1;
	// ma2(2,1)=9;
	// ma2(3,0)=1;
	// ma2(3,1)=9;
	
	// ma2(0,0)=3;
	// ma2(0,1)=7;
	// ma2(0,2)=2;
	// ma2(1,0)=5;
	// ma2(1,1)=1;
	// ma2(1,2)=9;


	
	//Matrix<int> ma3=ma1*ma2;

	std::cout << ma1 << std::endl;
	std::cout << ma1[2] <<std::endl;
	std::cout << ma2 << std::endl;

	//std::cout << ma3 << std::endl;

	return 0;
}

