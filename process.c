#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "utils.h"

/// Gera uma lista de processos com dados fixos (para testes ou simulação controlada)
Process* generate_static_processes(int count) {
    Process* list = malloc(sizeof(Process) * count);
    if (list == NULL) {
        perror("Erro ao alocar memória para processos estáticos");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        list[i].id = i;
        list[i].arrival_time = i * 2;
        list[i].burst_time = 5 + (i % 4);         // 5 a 8
        list[i].remaining_time = list[i].burst_time;
        list[i].priority = (i % 5) + 1;           // 1 a 5
        list[i].deadline = list[i].arrival_time + 10;
        list[i].period = 0; // só para tempo real
    }

    return list;
}


Process* generate_random_processes(int count, double lambda_arrival, double lambda_burst, int max_priority) {
    Process* list = malloc(sizeof(Process) * count);
    if (list == NULL) {
        perror("Erro ao alocar memória para processos aleatórios");
        exit(EXIT_FAILURE);
    }

    int current_time = 0;

    for (int i = 0; i < count; i++) {
        list[i].id = i;

        // Arrival time com Poisson
        int interval = generate_poisson(lambda_arrival);
        current_time += interval;
        list[i].arrival_time = current_time;

        // Burst time com Exponencial
        int burst = (int)generate_exponential(lambda_burst);
        list[i].burst_time = burst > 0 ? burst : 1;  // garantir que é >= 1
        list[i].remaining_time = list[i].burst_time;

        list[i].priority = rand() % max_priority + 1;
        list[i].deadline = list[i].arrival_time + (rand() % 11 + 5);
        list[i].period = 0;
    }

    return list;
}


/// Mostra os processos gerados no terminal (debug)
void print_processes(Process* processes, int count) {
    printf("ID\tArrival\tBurst\tRemain\tPriority\tDeadline\tPeriod\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
            processes[i].id,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].remaining_time,
            processes[i].priority,
            processes[i].deadline,
            processes[i].period
        );
    }
}

/// Liberta memória alocada para os processos
void free_processes(Process* processes) {
    free(processes);
}
