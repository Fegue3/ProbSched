// scheduler_multicore.c
#include "algorithms.h"
#include <pthread.h>

typedef struct {
    Process* processes;
    int count;
    int algoritmo;
    int quantum;
    int sim_time;
    Stats result;
} ThreadArgs;

void* run_simulation(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    switch (args->algoritmo) {
        case 1: args->result = simulate_fcfs(args->processes, args->count); break;
        case 2: args->result = simulate_sjf(args->processes, args->count); break;
        case 3: args->result = simulate_rr(args->processes, args->count, args->quantum); break;
        case 4: args->result = simulate_priority_np(args->processes, args->count); break;
        case 5: args->result = simulate_priority_p(args->processes, args->count); break;
        case 6: args->result = simulate_edf(args->processes, args->count, args->sim_time); break;
        case 7: args->result = simulate_rate_monotonic(args->processes, args->count, args->sim_time); break;
        case 8: args->result = simulate_mlq(args->processes, args->count, args->quantum); break;
        default: break;
    }
    pthread_exit(NULL);
}

Stats simulate_multicore(Process* processes, int count, int algoritmo, int quantum, int sim_time, int n_cores) {
    pthread_t threads[n_cores];
    ThreadArgs args[n_cores];

    int chunk = count / n_cores;
    int remainder = count % n_cores;
    int start = 0;

    for (int i = 0; i < n_cores; i++) {
        int this_count = chunk + (i < remainder ? 1 : 0);
        args[i].processes = &processes[start];
        args[i].count = this_count;
        args[i].algoritmo = algoritmo;
        args[i].quantum = quantum;
        args[i].sim_time = sim_time;

        pthread_create(&threads[i], NULL, run_simulation, &args[i]);
        start += this_count;
    }

    for (int i = 0; i < n_cores; i++) {
        pthread_join(threads[i], NULL);
    }

    // Combinar estatísticas
    Stats final = {0};
    int total_processes = 0;

    for (int i = 0; i < n_cores; i++) {
        final.avg_waiting_time += args[i].result.avg_waiting_time * args[i].count;
        final.avg_turnaround_time += args[i].result.avg_turnaround_time * args[i].count;
        final.cpu_utilization += args[i].result.cpu_utilization * args[i].count;
        final.throughput += args[i].result.throughput * args[i].count;
        final.missed_deadlines += args[i].result.missed_deadlines;
        total_processes += args[i].count;
    }

    final.avg_waiting_time /= total_processes;
    final.avg_turnaround_time /= total_processes;
    final.cpu_utilization /= total_processes;
    final.throughput /= total_processes;

    return final;
}
