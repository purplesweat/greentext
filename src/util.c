#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "util.h"

int rand_int(int min, int max) {
    return min + (rand() % (max-min));
}

double rand_double(double min, double max) {
    return min + (rand() * (max-min)) / RAND_MAX;
}

void randomize() {
    srand((unsigned) time(0));
}
