#include "algorithms.h"
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
        list[i].deadline = list[i].arrival_time + 5;
        list[i].period = list[i].burst_time + 4;
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
        list[i].deadline = list[i].arrival_time + (rand() % 4 + 5);
        list[i].period = (rand() % 7) + 4;
    }

    return list;
}

Process* generate_periodic_processes(int count, int periods[], int bursts[]) {
    Process* list = malloc(sizeof(Process) * count);
    for (int i = 0; i < count; i++) {
        list[i].id = i;
        list[i].arrival_time = 0; // Todos começam em tempo zero
        list[i].burst_time = bursts[i];
        list[i].remaining_time = bursts[i];
        list[i].period = periods[i];
        list[i].deadline = periods[i]; // Deadline = período em RT
        list[i].priority = 0; // Não usado no RT clássico (Rate Monotonic define prioridade pelo período)
    }
    return list;
}

Process* generate_static_periodic_processes(int count) {
    Process* list = malloc(sizeof(Process) * count);
    if (list == NULL) {
        perror("Erro ao alocar memória para processos estáticos periódicos");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        list[i].id = i;
        list[i].arrival_time = 0; // Todos começam no tempo 0

        // Definir burst_time de forma determinística
        list[i].burst_time = 1 + (i % 3); // Exemplo: 1,2,3,1,2,3,...

        list[i].remaining_time = list[i].burst_time;

        list[i].priority = (i % 5) + 1; // Se quiseres manter o campo priority (não usado no RM)

        // Deadlines e períodos definidos estaticamente:
        list[i].period = 4 + (i % 4); // Exemplo: períodos 4,5,6,7 cíclico
        list[i].deadline = list[i].period; 
    }

    return list;
}


Process* generate_random_periodic_processes(int count, double lambda_burst, int max_priority) {
    Process* list = malloc(sizeof(Process) * count);
    if (list == NULL) {
        perror("Erro ao alocar memória para processos periódicos");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        list[i].id = i;
        list[i].arrival_time = 0; // SEMPRE zero para processos periódicos

        int burst = (int)generate_exponential(lambda_burst);
        list[i].burst_time = burst > 0 ? burst : 1;
        list[i].remaining_time = list[i].burst_time;

        list[i].priority = rand() % max_priority + 1;
        list[i].period = 4 + rand() % 10; // Podes melhorar depois
        list[i].deadline = list[i].period;     // Períodos realistas (4-11)
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

void print_normal_processes(Process* processes, int count) {
    printf("ID\tArrival\tBurst\tPriority Deadline\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\t%d\t %d\n",
            processes[i].id,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].priority,
            processes[i].deadline
        );
    }
}

void print_periodic_processes(Process* processes, int count) {
    printf("ID\tArrival\tBurst\tPeriod\tDeadline\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n",
            processes[i].id,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].period,
            processes[i].deadline
        );
    }
}


/// Liberta memória alocada para os processos
void free_processes(Process* processes) {
    free(processes);
}
