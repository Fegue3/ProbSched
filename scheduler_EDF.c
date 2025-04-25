#include "algorithms.h"
#include <stdlib.h>
#include <stdio.h>

Stats simulate_edf(Process* processes, int count) {
    int time = 0;
    int completed = 0;
    int cpu_busy_time = 0;
    int* remaining = malloc(sizeof(int) * count);
    int* finished = calloc(count, sizeof(int));
    int* started = calloc(count, sizeof(int)); // 0 = ainda não começou
    int* start_time = malloc(sizeof(int) * count);

    for (int i = 0; i < count; i++) {
        remaining[i] = processes[i].burst_time;
        start_time[i] = -1;
    }

    double total_wait = 0;
    double total_turnaround = 0;
    int missed_deadlines = 0;

    while (completed < count) {
        // Encontrar o processo com deadline mínimo que já chegou e não terminou
        int selected = -1;
        for (int i = 0; i < count; i++) {
            if (!finished[i] && processes[i].arrival_time <= time) {
                if (selected == -1 || processes[i].deadline < processes[selected].deadline) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            time++; // idle
            continue;
        }

        // Marcar início da execução na 1ª vez
        if (!started[selected]) {
            start_time[selected] = time;
            started[selected] = 1;
        }

        printf("Tempo %d: Processo %d em execução\n", time, processes[selected].id);
        time++;
        remaining[selected]--;
        cpu_busy_time++;

        if (remaining[selected] == 0) {
            finished[selected] = 1;
            completed++;

            int turnaround = time - processes[selected].arrival_time;
            int waiting = turnaround - processes[selected].burst_time;
            total_turnaround += turnaround;
            total_wait += waiting;

            printf("    Processo %d finalizado — Chegada=%d, Início=%d, Fim=%d, Espera=%d, Turnaround=%d\n\n",
                   processes[selected].id,
                   processes[selected].arrival_time,
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

    Stats s;
    s.avg_waiting_time = total_wait / count;
    s.avg_turnaround_time = total_turnaround / count;
    s.cpu_utilization = (double)cpu_busy_time / time;
    s.throughput = (double)count / time;
    s.missed_deadlines = missed_deadlines;
    return s;
}
