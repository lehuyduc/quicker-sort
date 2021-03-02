#pragma once
#include "included.hpp"
#include "gen_test.hpp"
#include "cluster.h"

extern "C" {
#include "mysort.h"
}

//*****************
void check_result(int n, double a[], int predict[], int truth[])
{
	bool ok = true;
	for (int i = 0; i < n; i++) if (a[predict[i]] != a[truth[i]]) {
		ok = false;
	}
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
void test_sort_index(int array_size = -1, int test_type = -1, int nbig_test = 20, int test_per_big = 2, int nsmall_test = 0, int test_per_small = 1)
{
	const int MAXN = 10000000, MINN = 1000000;
	double* a, * predict, * truth;
	int* predict_index, * truth_index;
	a = new double[MAXN + MINN + 2];
	predict = new double[MAXN + MINN + 2];
	truth = new double[MAXN + MINN + 2];
	predict_index = new int[MAXN + MINN + 2];
	truth_index = new int[MAXN + MINN + 2];
	MyTimer timer;
	int n, number_of_test, type;
	myint64 total_n = 0;
	double guess1, guess2, fast_time, normal_time, total_fastsort = 0, total_normalsort = 0;


	for (int siz = 1; siz <= nbig_test + nsmall_test; siz++) {
		n = MINN + abs(randomed_int()) % MAXN;
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
			fastsort_index(n, predict, predict_index);		
			fast_time = timer.getCounter();

			timer.startCounter();
			cluster_sort_index(n, truth, truth_index);
			normal_time = timer.getCounter();

			//*******
			cout << "time fast sort index = " << fast_time << "\n";
			cout << "time biopython index = " << normal_time << "\n";
			check_result(n, a, predict_index, truth_index);
					
			total_n += n;
			total_fastsort += fast_time;
			total_normalsort += normal_time;
			cout << "\n";
		}
	}

	cout << "faster sort speed = " << double(total_n) / total_fastsort << " elements/ms\n";
	cout << "normal sort speed = " << double(total_n) / total_normalsort << " elements/ms\n";
	cout << "\n****************\n\n";

	delete[] a;
	delete[] predict;
	delete[] truth;
	delete[] predict_index;
	delete[] truth_index;
}