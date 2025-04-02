#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"

int main()
{
    srand(time(NULL)); // Inicializa a seed para aleatoriedade

    int count = 5;
    double lambda_arrival = 3.0; // controla frequência de chegada (Poisson)
    double lambda_burst = 0.5;   // controla variação de burst time (Exponencial)
    int max_priority = 5;
    int quantum = 2;

    printf("=== Processos Estáticos ===\n");
    Process *static_list = generate_static_processes(count);
    print_processes(static_list, count);
    free_processes(static_list);

    printf("\n=== Processos Aleatórios ===\n");
    Process* random_list = generate_random_processes(count, lambda_arrival, lambda_burst, max_priority);
    print_processes(random_list, count);
    free_processes(random_list);


    printf("\n=== Escalonamento FCFS (First Come First Serve) ===\n");
    Process* fcfs_list = generate_static_processes(count); // ou generate_random_processes
    print_processes(fcfs_list, count);

    Stats fcfs_stats = simulate_fcfs(fcfs_list, count);
    printf("Tempo médio de espera: %.2f\n", fcfs_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", fcfs_stats.avg_turnaround_time);
    free_processes(fcfs_list);


    printf("\n=== Escalonamento SJF (Shortest Job First) ===\n");
    Process* sjf_list = generate_static_processes(count); 
    print_processes(sjf_list, count);

    Stats sjf_stats = simulate_sjf(sjf_list, count);
    printf("Tempo médio de espera: %.2f\n", sjf_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", sjf_stats.avg_turnaround_time);
    free_processes(sjf_list);


    printf("\n=== Escalonamento Round-Robin (RR) ===\n");
    Process* rr_list = generate_static_processes(count); 
    print_processes(rr_list, count);

    Stats rr_stats = simulate_rr(rr_list, count, quantum);
    printf("Tempo médio de espera: %.2f\n", rr_stats.avg_waiting_time);
    printf("Tempo médio de turnaround: %.2f\n", rr_stats.avg_turnaround_time);
    free_processes(rr_list);

    return 0; 
}
