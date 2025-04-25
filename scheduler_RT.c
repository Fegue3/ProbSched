#include <stdio.h>
#include <limits.h>
#include "algorithms.h"

Stats simulate_rate_monotonic(Process* processes, int count, int simulation_time) {
    int time = 0;
    int completed = 0;
    int missed_deadlines = 0;
    int cpu_busy_time = 0;

    double total_wait = 0;
    double total_turnaround = 0;

    int* remaining = malloc(sizeof(int) * count);
    int* arrival = malloc(sizeof(int) * count);
    int* next_arrival = malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++) {
        arrival[i] = processes[i].arrival_time;
        remaining[i] = processes[i].burst_time;
        next_arrival[i] = processes[i].arrival_time + processes[i].period;
    }

    while (time < simulation_time) {
        // Gerar novas instâncias
        for (int i = 0; i < count; i++) {
            if (time == next_arrival[i]) {
                if (remaining[i] > 0) {
                    missed_deadlines++;
                    // Agora não cancelamos a instância anterior
                    // Ela pode terminar, e a nova espera pelo próximo ciclo
                }

                arrival[i] = time;
                remaining[i] = processes[i].burst_time;
                next_arrival[i] += processes[i].period;
            }
        }

        // Selecionar processo com menor período (desempate por chegada)
        int selected = -1;
        int min_period = INT_MAX;

        for (int i = 0; i < count; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                if (processes[i].period < min_period ||
                    (processes[i].period == min_period && arrival[i] < arrival[selected])) {
                    min_period = processes[i].period;
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            int start_time = time;
            remaining[selected]--;
            cpu_busy_time++;

            if (remaining[selected] == 0) {
                int end_time = time + 1;
                int turnaround = end_time - arrival[selected];
                int wait = turnaround - processes[selected].burst_time;
                total_turnaround += turnaround;
                total_wait += wait;
                completed++;

                printf("Processo %d: Chegada=%d, Início=%d, Fim=%d, Espera=%d, Turnaround=%d\n",
                       processes[selected].id, arrival[selected], start_time, end_time, wait, turnaround);
            }
        }

        time++;
    }

    free(remaining);
    free(arrival);
    free(next_arrival);

    Stats s;
    s.avg_waiting_time = completed > 0 ? total_wait / completed : 0;
    s.avg_turnaround_time = completed > 0 ? total_turnaround / completed : 0;
    s.cpu_utilization = (double)cpu_busy_time / simulation_time;
    s.throughput = (double)completed / simulation_time;
    s.missed_deadlines = missed_deadlines;

    return s;
}
