
#include "algorithms.h"

void show_menu_algoritmos() {
    printf("\n--- Escolha o Algoritmo de Escalonamento ---\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. Round Robin\n");
    printf("4. Priority (Nao-Preemptivo)\n");
    printf("5. Priority (Preemptivo)\n");
    printf("6. EDF\n");
    printf("7. Rate Monotonic (RT)\n");
    printf("8. Multilevel Queue\n");
    printf("0. Sair\n");
}

void print_stats(Stats s) {
    printf("\n--- Estatisticas ---\n");
    printf("Espera media: %.2f\n", s.avg_waiting_time);
    printf("Turnaround medio: %.2f\n", s.avg_turnaround_time);
    printf("Utilizacao da CPU: %.2f%%\n", s.cpu_utilization * 100);
    printf("Throughput: %.2f processos/unidade de tempo\n", s.throughput);
    if (s.missed_deadlines > 0 && (s.avg_turnaround_time < 1.0)) { 
        printf("Deadlines perdidas: %d\n", s.missed_deadlines);
    }
}

int main() {
    srand(time(NULL));

    int sair = 0;

    while (!sair) {
        int algoritmo = -1;
        int tipo_geracao = -1;
        int count = 0;
        int sim_time = 0;
        int quantum = 0;
        double lambda_arrival = 3.0;
        double lambda_burst = 0.5;
        int max_priority = 5;
        int processos_periodicos = 0;

        printf("\n=== ProbSched - Simulador de Escalonamento ===\n");

        // 1. Escolher Algoritmo
        show_menu_algoritmos();
        do {
            printf("Escolha o algoritmo: ");
            scanf("%d", &algoritmo);
            if (algoritmo == 0) {
                sair = 1;
                break;
            }
        } while (algoritmo < 1 || algoritmo > 8);

        if (sair) break;

        printf("Numero de processos a simular: ");
        scanf("%d", &count);

        if (algoritmo == 7 || algoritmo == 6) { // Rate Monotonic ou EDF
            printf("Tempo maximo de simulacao: ");
            scanf("%d", &sim_time);
        }

        if (algoritmo == 3 || algoritmo == 8) { // Round Robin ou MLQ
            printf("Introduza o Quantum: ");
            scanf("%d", &quantum);
        }

        // Determinar automaticamente se sao processos periodicos
        if (algoritmo == 6 || algoritmo == 7) { // EDF ou Rate Monotonic
            processos_periodicos = 1;
        }

        // 2. Escolher tipo de geracao
        printf("\n--- Tipo de Processos ---\n");
        printf("1. Introduzir manualmente\n");
        printf("2. Lista Estatica pre-definida\n");
        printf("3. Gerar Processos Aleatorios\n");
        do {
            printf("Escolha: ");
            scanf("%d", &tipo_geracao);
        } while (tipo_geracao < 1 || tipo_geracao > 3);
        
        Process* processos = NULL;
        
        if (tipo_geracao == 1) { // manual
            processos = input_manual_processes(count, processos_periodicos);
        } else if (tipo_geracao == 2) { // lista estática
            if (processos_periodicos) {
                processos = generate_static_periodic_processes(count);
            } else {
                processos = generate_static_processes(count);
            }
        } else if (tipo_geracao == 3) { // aleatórios
            if (processos_periodicos) {
                printf("Lambda para Burst Time (Exponencial): ");
                scanf("%lf", &lambda_burst);
        
                processos = generate_random_periodic_processes(count, lambda_burst, 1);
            } else {
                printf("Lambda para Arrival Time (Poisson): ");
                scanf("%lf", &lambda_arrival);
        
                printf("Lambda para Burst Time (Exponencial): ");
                scanf("%lf", &lambda_burst);
        
                printf("Maximo da Prioridade (1 a N): ");
                scanf("%d", &max_priority);
        
                processos = generate_random_processes(count, lambda_arrival, lambda_burst, max_priority);
            }
        }

        // 3. Imprimir processos corretamente
        if (processos_periodicos) {
            print_periodic_processes(processos, count);
        } else {
            print_normal_processes(processos, count);
        }

        // 4. Executar simulacao
        Stats stats = {0};
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
                stats = simulate_edf(processos, count, sim_time);
                break;
            case 7:
                stats = simulate_rate_monotonic(processos, count, sim_time);
                break;
            case 8:
                stats = simulate_mlq(processos, count, quantum);
                break;
            default:
                printf("Algoritmo invalido!\n");
                free_processes(processos);
                goto fim_simulacao;
        }

        // 5. Mostrar estatisticas
        print_stats(stats);

        // 6. Libertar memoria
        free_processes(processos);

        // 7. Perguntar se quer voltar ou sair
        int opcao_final;
        printf("\n--- O que deseja fazer? ---\n");
        printf("1. Voltar ao Inicio\n");
        printf("2. Sair\n");
        do {
            printf("Escolha: ");
            scanf("%d", &opcao_final);
            if (opcao_final == 2) sair = 1;
        } while (opcao_final != 1 && opcao_final != 2);

    fim_simulacao:;
    }

    printf("\nFim do simulador.\n");

    return 0;
}


Process* input_manual_processes(int count, int periodic) {
    Process* list = malloc(sizeof(Process) * count);
    if (!list) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        printf("\n--- Processo %d ---\n", i);
        list[i].id = i;

        printf("Arrival time: ");
        scanf("%d", &list[i].arrival_time);

        printf("Burst time: ");
        scanf("%d", &list[i].burst_time);
        list[i].remaining_time = list[i].burst_time;

        printf("Priority (menor = mais prioritário): ");
        scanf("%d", &list[i].priority);

        if (periodic) {
            printf("Period: ");
            scanf("%d", &list[i].period);

            printf("Deadline (ou mesmo valor do período): ");
            scanf("%d", &list[i].deadline);
        } else {
            list[i].period = 0;
            list[i].deadline = list[i].arrival_time + 5;
        }
    }

    return list;
}
