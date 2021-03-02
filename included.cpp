#include "included.hpp"

static std::random_device randDev;
static std::minstd_rand0 twister(randDev());
static std::uniform_real_distribution<double> dist(-10000000, 10000000);
double randomed() {
    return dist(twister);
}

static std::random_device randDev3;
static std::minstd_rand0 twister3(randDev3());
static std::uniform_int_distribution<int> dist3(0, 10000000);
int randomed_int() {
    return dist3(twister3);
}



//************
static int* flusher;

int flush_cache()
{
    const int n = 1000 * 100;
    const int base = 100 * 1000 * 1000 + 7; // 10^8 + 7 prime number
    flusher = new int[n + 1];

    flusher[0] = rand() % 1000 + 1;
    for (int i = 1; i < n; i++) {
        flusher[i] = flusher[i - 1] * 13 + 17;
        if (flusher[i] > base) flusher[i] %= base;
    }

    myint64 res = 0, sign = 1;
    for (int i = 0; i < n; i++) {
        res += flusher[i] * sign;
        sign *= -1;
    }

    delete[] flusher;
    return res % base;
}