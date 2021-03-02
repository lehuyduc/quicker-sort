* C qsort() is very slow, much slower than C++ std::sort().
* This is because qsort() doesn't utilize data-type information at compile time,
* and it has redundant pointer dereference since it requires a compare function.
* For projects that use old C, it's impossible to convert to C++/newer C.
* 
* So we implement a simple quicksort that is 25% faster than C++ std::sort()
* with mostly random data, and much faster with structured/sorted data 

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
