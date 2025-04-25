#include "algorithms.h"
#include <stdlib.h>
#include <stdio.h>

Stats simulate_edf(Process* processes, int count, int simulation_time) {
    int time = 0;
    int completed = 0;
    int cpu_busy_time = 0;

    int* remaining = malloc(sizeof(int) * count);
    int* finished = calloc(count, sizeof(int));
    int* started = calloc(count, sizeof(int));
    int* start_time = malloc(sizeof(int) * count);
    int* arrival = malloc(sizeof(int) * count);
    int* next_arrival = malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++) {
        arrival[i] = processes[i].arrival_time;
        remaining[i] = processes[i].burst_time;
        next_arrival[i] = processes[i].arrival_time + processes[i].period;
        start_time[i] = -1;
    }

    double total_wait = 0;
    double total_turnaround = 0;
    int missed_deadlines = 0;

    while (time < simulation_time) {
        // Gerar novas instâncias periódicas
        for (int i = 0; i < count; i++) {
            if (time == next_arrival[i]) {
                if (remaining[i] > 0) {
                    missed_deadlines++;
                }
                arrival[i] = time;
                remaining[i] = processes[i].burst_time;
                next_arrival[i] += processes[i].period;
                started[i] = 0;
                start_time[i] = -1;
            }
        }

        // Encontrar o processo com deadline mais próximo
        int selected = -1;
        for (int i = 0; i < count; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                if (selected == -1 || processes[i].deadline < processes[selected].deadline) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            time++; // CPU idle
            continue;
        }

        // Marcar início na primeira execução
        if (!started[selected]) {
            start_time[selected] = time;
            started[selected] = 1;
        }

        printf("Tempo %d: Processo %d em execução\n", time, processes[selected].id);
        time++;
        remaining[selected]--;
        cpu_busy_time++;

        if (remaining[selected] == 0) {
            completed++;
            int turnaround = time - arrival[selected];
            int waiting = turnaround - processes[selected].burst_time;
            total_turnaround += turnaround;
            total_wait += waiting;

            printf("    Processo %d finalizado — Chegada=%d, Início=%d, Fim=%d, Espera=%d, Turnaround=%d\n\n",
                   processes[selected].id,
                   arrival[selected],
                   start_time[selected],
                   time,
                   waiting,
                   turnaround);

            if (time > processes[selected].deadline) {
                missed_deadlines++;
            }
        }
    }

    free(remaining);
    free(finished);
    free(started);
    free(start_time);
    free(arrival);
    free(next_arrival);

    Stats s;
    s.avg_waiting_time = (completed > 0) ? (total_wait / completed) : 0;
    s.avg_turnaround_time = (completed > 0) ? (total_turnaround / completed) : 0;
    s.cpu_utilization = (double)cpu_busy_time / simulation_time;
    s.throughput = (double)completed / simulation_time;
    s.missed_deadlines = missed_deadlines;
    return s;
}
