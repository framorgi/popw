
#include "common.h"

// Funzione per generare un numero casuale tra min e max
double Random_double(double min, double max)
{
    return min + (max - min) * (rand() / (double)RAND_MAX);
}

int Random_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}
