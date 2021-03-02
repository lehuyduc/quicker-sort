#pragma once
#include "included.hpp"
#include "gen_test.hpp"

static int
compare(const void* a, const void* b)
{
	const double term1 = *(const double*)a;
	const double term2 = *(const double*)b;

	if (term1 < term2) return -1;
	if (term1 > term2) return +1;
	return 0;
}

extern "C" {
	#include "mysort.h"
}

//*****************
void check_result(int n, double a[], double predict[], double truth[])
{
	bool ok = true;
	for (int i = 0; i < n; i++) if (predict[i] != truth[i])  ok = false;
	if (ok) return;

	cout << "error at N = " << n << "\n";
	std::ofstream fo("debug.txt");
	fo << std::fixed << std::setprecision(1);
	fo << n << "\n";
	for (int i = 0; i < n; i++) fo << a[i] << " "; fo << "\n";
	for (int i = 0; i < n; i++) fo << predict[i] << " ";
	fo.close();
	exit(-1);
}

// array_size <= 0 means randomize 
void test_sort(int array_size = -1, int test_type = -1, int nbig_test = 20, int test_per_big = 2, int nsmall_test = 0, int test_per_small = 1)
{
	const int MAXN = 10000000, MINN = 1000000;
	double* a, * predict, * truth;
	a = new double[MAXN + MINN + 2];
	predict = new double[MAXN + MINN + 2];
	truth = new double[MAXN + MINN + 2];
	MyTimer timer;
	int n, number_of_test, type;
	myint64 total_n = 0;
	double guess1, guess2, fast_time, normal_time, total_fastsort = 0, total_normalsort = 0;


	for (int siz = 1; siz <= nbig_test + nsmall_test; siz++) {
		n = MINN + abs(randomed_int()) % MAXN;	
		n = 1000000;
		if (array_size > 0) n = array_size;

		if (siz <= nsmall_test) {
			n = siz;
			number_of_test = test_per_small;
		}
		else number_of_test = test_per_big;

		//*****
		for (int t = 1; t <= number_of_test; t++)
		{
			cout << "n = " << n << "\n";
			type = randomed_int() % 5;
			if (test_type >= 0) type = test_type;

			gen_test(n, a, type);					
			memcpy(predict, a, n * sizeof(double));
			memcpy(truth, a, n * sizeof(double));
			cout << "begin running\n";

			flush_cache();	// we do this to ensure the accuracy of speed measurement. comment this if you think it's unnecessary
			//******************		
			timer.startCounter();
			fastsort(n, predict);
			fast_time = timer.getCounter();
			
			timer.startCounter();
			std::sort(truth, truth + n);
			//qsort((void*)truth, n, sizeof(double), compare);
			normal_time = timer.getCounter();
					
			//*******
			check_result(n, a, predict, truth);					
			cout << "time fastsort = " << fast_time << "\n";
			cout << "time std:sort = " << normal_time << "\n";
		
			total_n += n;
			total_fastsort += fast_time;
			total_normalsort += normal_time;
			cout << "\n";
		}
	}

	cout << "faster sort speed = " << double(total_n) / total_fastsort << " elements/ms\n";
	cout << "normal sort speed = " << double(total_n) / total_normalsort  << " elements/ms\n";
	
	delete[] a;
	delete[] predict;
	delete[] truth;
}