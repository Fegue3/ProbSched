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
    printf("0. Voltar atrás\n");
}

void print_stats(Stats s) {
    printf("Espera média: %.2f\n", s.avg_waiting_time);
    printf("Turnaround médio: %.2f\n", s.avg_turnaround_time);
    printf("Utilização da CPU: %.2f%%\n", s.cpu_utilization * 100);
    printf("Throughput: %.2f processos/unidade de tempo\n", s.throughput);
    if (s.missed_deadlines > 0)
        printf("Deadlines perdidas: %d\n", s.missed_deadlines);
}


int main() {
    srand(time(NULL));
    int count = 5;
    double lambda_arrival = 3.0;
    double lambda_burst = 0.5;
    int max_priority = 5;
    int quantum = 2;

    int running = 1;
    while (running) {
        int tipo_dados = -1;

        // Escolher tipo de dados ou sair
        printf("\n=== ProbSched - Simulador de Escalonamento ===\n");
        printf("1. Usar Processos Estáticos\n");
        printf("2. Usar Processos Aleatórios\n");
        printf("0. Sair\n");
        printf("Escolha o tipo de dados: ");
        scanf("%d", &tipo_dados);

        if (tipo_dados == 0) {
            printf("Saindo...\n");
            break;
        }

        Process* processos = NULL;
        if (tipo_dados == 1)
            processos = generate_static_processes(count);
        else if (tipo_dados == 2)
            processos = generate_random_processes(count, lambda_arrival, lambda_burst, max_priority);
        else
            continue;

        print_processes(processos, count);

        int opcao = -1;
        while (1) {
            show_menu_algoritmos();
            printf("Escolha: ");
            scanf("%d", &opcao);

            if (opcao == 0) break;  // Voltar ao menu anterior

            switch (opcao) {
                case 1: {
                    Stats s = simulate_fcfs(processos, count);
                    print_stats(s);
                    break;
                }
                case 2: {
                    Stats s = simulate_sjf(processos, count);
                    print_stats(s);

                    break;
                }
                case 3: {
                    Stats s = simulate_rr(processos, count, quantum);
                    print_stats(s);
                    break;
                }
                case 4: {
                    Stats s = simulate_priority_np(processos, count);
                    print_stats(s);
                    break;
                }
                case 5: {
                    Stats s = simulate_priority_p(processos, count);
                    print_stats(s);
                    break;
                }
                case 6: {
                    Stats s = simulate_edf(processos, count);
                    print_stats(s);
                    break;
                }
                case 7: {
                    int sim_time = 20;
                    Stats rs = simulate_rate_monotonic(processos, count, sim_time);
                    print_stats(rs);
                    break;
                }
                case 8: {
                    Stats s = simulate_mlq(processos, count, quantum);
                    print_stats(s);
                    break;
                }
                default:
                    printf("Opção inválida!\n");
            }
        }

        free_processes(processos);
    }

    return 0;
}
