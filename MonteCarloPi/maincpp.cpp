#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>
#include <functional>

#define M_PI 3.14159265358979323846

void main()
{
	std::cout.precision(20);
	std::mt19937 gen[4];
	int allpts = 1000000000;
	int cpts = 0;
	for (int i = 0; i < 4; i++)
		gen[i].seed(time(NULL));


		gen[1].discard(allpts/2);

		gen[2].discard(allpts);
		gen[3].discard(allpts);
		gen[3].discard(allpts/2);


		clock_t startSeq = clock();
#pragma omp parallel num_threads(4)
		{	
	#pragma omp for reduction(+:cpts)
		for (int i = 0; i < allpts; i++)
		{
			double x, y;

			x = gen[omp_get_thread_num()]() /(double) gen[0].max();
			y = gen[omp_get_thread_num()]() /(double) gen[0].max();

			if (x*x + y*y < 1)
				cpts++;
		}
	}
	clock_t finishSeq = clock();


	double timeSeq = double(finishSeq - startSeq) / CLOCKS_PER_SEC;
	double calcPI = 4.0*(double)cpts / allpts;
	std::cout <<"PI Value: " <<calcPI << std::endl;
	std::cout << "Time: " << timeSeq << std::endl;
	std::cout << "Fault: " << M_PI - calcPI << std::endl;
	system("pause");
}