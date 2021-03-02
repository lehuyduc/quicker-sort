#pragma once
#include "included.hpp"

void gen_random(int n, double a[]) {
	for (int i = 0; i < n; i++) a[i] = randomed();
}

void gen_increasing(int n, double a[]) {
	a[0] = randomed();
	for (int i = 1; i < n; i++) a[i] = a[i - 1] + abs(randomed_int()) % 100;
}

void gen_decreasing(int n, double a[]) {
	a[0] = randomed();
	for (int i = 1; i < n; i++) a[i] = a[i - 1] - abs(randomed_int()) % 100;
}

void gen_equal(int n, double a[]) {
	a[0] = randomed();
	for (int i = 1; i < n; i++) a[i] = a[0];
}

void gen_test_hard(int n, double a[])
{

	int remaining = n, index = 0, toosmall = std::max(n / 100, 10);
	while (remaining > toosmall) {
		int nsmall = std::min(randomed_int() % 100, remaining);//abs(randomed_int()) % (remaining / 4) + 1;
		int type = abs(randomed_int()) % 100;

		if (type < 50) gen_random(nsmall, &a[index]);
		else if (type < 24) gen_increasing(nsmall, &a[index]);
		else if (type < 24) gen_decreasing(nsmall, &a[index]);
		else gen_equal(nsmall, &a[index]);


		index += nsmall;
		remaining -= nsmall;
	}
	gen_random(remaining, &a[index]);
}

void gen_test(int n, double a[], int type)
{
	if (type == 0) {
		cout << "making test random\n";
		gen_random(n, a);
	}
	else if (type == 1) {
		cout << "making test increasing\n";
		gen_increasing(n, a);
	}
	else if (type == 2) {
		cout << "making test decreasing\n";
		gen_decreasing(n, a);
	}
	else if (type == 3) {
		cout << "making test equal\n";
		gen_equal(n, a);
	}
	else if (type == 4) {
		cout << "making test hard\n";
		gen_test_hard(n, a);
	}
}

