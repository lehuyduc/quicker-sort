The sort functions are completely useable in raw C, not C++.

Main file: CstdSort.cpp

Types of test:    
    0 = random data
    1 = sorted (increasing) data
    2 = reversed sorted (decreasing) data 
    3 = all data are equals
    4 = completely random mixture of all the aboves (hard test)
    -1: randomly one above

In test_sort_index.hpp, we compare fastsort_index vs current biopython implementation (cluster_sort_index).
In test_sort.hpp, we compare fastsort vs std::sort and C qsort()
