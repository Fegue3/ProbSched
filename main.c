#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"

void show_menu_algoritmos() {
    printf("\n--- Escolha o Algoritmo de Escalonamento ---\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. Round Robin\n");
    printf("4. Priority (Não-Preemptivo)\n");
    printf("5. Priority (Preemptivo)\n");
    printf("6. EDF\n");
    printf("7. Rate Monotonic (RT)\n");
    printf("8. Multilevel Queue\n");
}

void print_stats(Stats s) {
    printf("\n--- Estatísticas ---\n");
    printf("Espera média: %.2f\n", s.avg_waiting_time);
    printf("Turnaround médio: %.2f\n", s.avg_turnaround_time);
    printf("Utilização da CPU: %.2f%%\n", s.cpu_utilization * 100);
    printf("Throughput: %.2f processos/unidade de tempo\n", s.throughput);
    if (s.missed_deadlines > 0)
        printf("Deadlines perdidas: %d\n", s.missed_deadlines);
}

int main() {
    srand(time(NULL));

    int algoritmo = -1;
    int tipo_dados = -1;
    int count = 0;
    int sim_time = 0;
    int quantum = 0;
    double lambda_arrival = 3.0;
    double lambda_burst = 0.5;
    int max_priority = 5;

    printf("\n=== ProbSched - Simulador de Escalonamento ===\n");

    // 1. Escolher Algoritmo
    show_menu_algoritmos();
    do {
        printf("Escolha o algoritmo: ");
        scanf("%d", &algoritmo);
    } while (algoritmo < 1 || algoritmo > 8);

    printf("Número de processos a simular: ");
    scanf("%d", &count);

    if (algoritmo == 7) {
        printf("Tempo máximo de simulação: ");
        scanf("%d", &sim_time);
    }

    // 3. Se precisar de quantum
    if (algoritmo == 3 || algoritmo == 8) { // Round Robin ou MLQ
        printf("Introduza o Quantum: ");
        scanf("%d", &quantum);
    }

    // 4. Escolher tipo de dados
    printf("\n--- Tipo de Processos ---\n");
    printf("1. Lista Estática\n");
    printf("2. Gerar Processos Aleatórios\n");
    do {
        printf("Escolha: ");
        scanf("%d", &tipo_dados);
    } while (tipo_dados != 1 && tipo_dados != 2);

    Process* processos = NULL;

    if (tipo_dados == 1) {
        processos = generate_static_processes(count);
    } else if (tipo_dados == 2) {
        printf("Lambda para Arrival Time (Exponencial): ");
        scanf("%lf", &lambda_arrival);

        printf("Lambda para Burst Time (Exponencial): ");
        scanf("%lf", &lambda_burst);

        printf("Máximo da Prioridade (1 a N): ");
        scanf("%d", &max_priority);

        processos = generate_random_processes(count, lambda_arrival, lambda_burst, max_priority);
    }

    print_processes(processos, count);

    // 5. Executar simulação
    Stats stats;
    switch (algoritmo) {
        case 1:
            stats = simulate_fcfs(processos, count);
            break;
        case 2:
            stats = simulate_sjf(processos, count);
            break;
        case 3:
            stats = simulate_rr(processos, count, quantum);
            break;
        case 4:
            stats = simulate_priority_np(processos, count);
            break;
        case 5:
            stats = simulate_priority_p(processos, count);
            break;
        case 6:
            stats = simulate_edf(processos, count);
            break;
        case 7:
            stats = simulate_rate_monotonic(processos, count, sim_time);
            break;
        case 8:
            stats = simulate_mlq(processos, count, quantum);
            break;
        default:
            printf("Algoritmo inválido!\n");
            free_processes(processos);
            return 1;
    }

    // 6. Mostrar estatísticas
    print_stats(stats);

    // 7. Libertar memória
    free_processes(processos);

    return 0;
}
