#include "algorithms.h"

Stats simulate_edf(Process* processes, int count) {
    int time = 0;
    int completed = 0;
    int* remaining = malloc(sizeof(int) * count);
    int* finished = calloc(count, sizeof(int));

    for (int i = 0; i < count; i++) {
        remaining[i] = processes[i].burst_time;
    }

    double total_wait = 0;
    double total_turnaround = 0;

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

        time++; // executar 1 unidade (preemptivo)
        remaining[selected]--;

        if (remaining[selected] == 0) {
            finished[selected] = 1;
            completed++;

            int turnaround = time - processes[selected].arrival_time;
            int waiting = turnaround - processes[selected].burst_time;
            total_turnaround += turnaround;
            total_wait += waiting;

            printf("Processo %d: Fim=%d, Espera=%d, Turnaround=%d\n",
                   processes[selected].id, time, waiting, turnaround);
        }
    }

    free(remaining);
    free(finished);

    Stats s;
    s.avg_waiting_time = total_wait / count;
    s.avg_turnaround_time = total_turnaround / count;
    return s;
}
