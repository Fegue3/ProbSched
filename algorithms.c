#include "algorithms.h"
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

Stats simulate_sjf(Process* processes, int count) {
    int time = 0;
    int completed = 0;
    int cpu_busy_time = 0;
    int* done = calloc(count, sizeof(int));
    double total_wait = 0;
    double total_turnaround = 0;

    while (completed < count) {
        int idx = -1;
        int min_burst = 1e9;

        for (int i = 0; i < count; i++) {
            if (!done[i] && processes[i].arrival_time <= time && processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                idx = i;
            }
        }

        if (idx == -1) {
            time++; 
            continue;
        }

        int start_time = time;
        cpu_busy_time += processes[idx].burst_time; 
        time += processes[idx].burst_time;
        int wait = start_time - processes[idx].arrival_time;
        int turnaround = time - processes[idx].arrival_time;

        total_wait += wait;
        total_turnaround += turnaround;

        printf("Processo %d: Chegada = %d,Inicio=%d, Fim = %d, Espera = %d, Turnaround = %d\n",
               processes[idx].id, processes[idx].arrival_time,start_time, time, wait, turnaround);

        done[idx] = 1;
        completed++;
    }

    free(done);

    Stats s;
    s.avg_waiting_time = total_wait / count;
    s.avg_turnaround_time = total_turnaround / count;
    s.cpu_utilization = (double)cpu_busy_time / time;
    s.throughput = (double)count / time;
    return s;
}
