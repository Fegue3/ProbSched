#include <stdlib.h>
#include <math.h>
#include "utils.h"

/// Gera um número com distribuição exponencial (ex: tempo entre chegadas)
double generate_exponential(double lambda) {
    double u;
    do {
        u = rand() / (double)RAND_MAX; // gera U em (0,1)
    } while (u == 0); // evitar log(0)
    
    return -log(u) / lambda;
}

/// Gera um número com distribuição de Poisson (ex: nº de chegadas num tempo)
int generate_poisson(double lambda) {
    double L = exp(-lambda);
    double p = 1.0;
    int k = 0;

    do {
        k++;
        double u = rand() / (double)RAND_MAX;
        p *= u;
    } while (p > L);

    return k - 1;
}
