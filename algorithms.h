#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
    double avg_waiting_time;
    double avg_turnaround_time;
    double cpu_utilization;
    double throughput;
    int missed_deadlines;
} Stats;

typedef struct {
    int id;               // ID do processo (único e sequencial)
    int arrival_time;     // Tempo de chegada
    int burst_time;       // Tempo total de CPU necessário
    int remaining_time;   // Tempo restante (útil para RR ou preemptivos)
    int priority;         // Prioridade (para Priority Scheduling)

    int deadline;         // Deadline (para EDF)
    int period;           // Período (para Rate Monotonic)
} Process;


Stats simulate_fcfs(Process* processes, int count);

Stats simulate_rr(Process* processes, int count, int quantum);

Stats simulate_sjf(Process* processes, int count);

Stats simulate_edf(Process* processes, int count);

Process* generate_static_processes(int count);

Process* generate_random_processes(int count, double lambda_arrival, double lambda_burst, int max_priority);

void print_processes(Process* processes, int count);

void free_processes(Process* processes);

double generate_exponential(double lambda);

int generate_poisson(double lambda);

Stats simulate_priority_np(Process* processes, int count);

Stats simulate_priority_p(Process* processes, int count);

Stats simulate_rate_monotonic(Process* processes, int count, int simulation_time);

Stats simulate_mlq(Process* processes, int count, int quantum);