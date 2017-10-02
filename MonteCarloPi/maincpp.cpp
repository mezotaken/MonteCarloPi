#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>



void main()
{
	std::cout.precision(10);
	
	int allpts = 100000000;
	int cpts = 0;
	clock_t startSeq = clock();
#pragma omp parallel shared(cpts)
	{

	#pragma omp for 
		for (int i = 0; i < allpts; i++)
		{
			double x, y;
			x = rand() % RAND_MAX / (double)RAND_MAX;
			y = rand() % RAND_MAX / (double)RAND_MAX;
			if (x*x + y*y < 1)
			{
				#pragma omp atomic
				cpts++;
			}
		}
	}
	clock_t finishSeq = clock();
	double timeSeq = double(finishSeq - startSeq) / CLOCKS_PER_SEC;
	std::cout << 4.0*(double)cpts/allpts<< std::endl;
	std::cout << "Sequential time: " << timeSeq << std::endl;
	system("pause");
}