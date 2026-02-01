#include "Rng.h"

using namespace std;

int randomNumberGenerator(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}