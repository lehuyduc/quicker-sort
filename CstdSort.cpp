// CstdSort.cpp: This file contains the 'main' function. Program execution begins and ends there.
//

#include "included.hpp"
#include "test_sort.hpp"
#include "test_sort_index.hpp"
using namespace std;

int string2int(string s)
{
    if (s == "-1") return -1;
    int number = s[0] - 48;
    if (number < 0 || number > 9) return 0;
    else return number;
}

/*
types of test:    
    0 = random data
    1 = sorted (increasing) data
    2 = reversed sorted (decreasing) data 
    3 = all data are equals
    4 = completely random mixture of all the aboves (hard test)
    -1: randomly one above

*/

// in test_sort_index.hpp, we compare fastsort_index vs current biopython implementation (cluster_sort_index).
// in test_sort.hpp, we compare fastsort vs std::sort and C qsort()

ofstream fo;

int main()
{   
    //test_sort_index(-1, -1, 0, 0, 1000, 100);   // test all array sizes from 1 -> 1000, each size performs 100 tests. Use to test small array speed
    //getchar();

   // test_sort_index(5000000, 0, 100, 2, 0, 0);
   // getchar();

  //  test_sort_index(-1, -1, 100, 2, 0, 0);
  //  getchar();

    //test_sort(5000000, 0, 100, 2, 0, 0);    // test arrays with 10^6 - 10^7 random elements; perform 20 * 2 tests in total
    //getchar();

    test_sort(-1, 0, 10, 2, 0, 0);    // test arrays with 10^6 - 10^7 mixed element; perform 20 * 2 tests in total
    //getchar();

    
  
    return 0;
}