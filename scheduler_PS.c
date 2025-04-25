#include "algorithms.h"
Stats simulate_priority_np(Process* processes, int count) {
    int time = 0, completed = 0;
    int* done = calloc(count, sizeof(int));
    double total_wait = 0, total_turnaround = 0;

    while (completed < count) {
        int idx = -1;
        int highest_priority = 9999;

        for (int i = 0; i < count; i++) {
            if (!done[i] && processes[i].arrival_time <= time && processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            time++; // CPU idle
            continue;
        }

        time += processes[idx].burst_time;
        int turnaround = time - processes[idx].arrival_time;
        int wait = turnaround - processes[idx].burst_time;

        total_turnaround += turnaround;
        total_wait += wait;

        printf("Processo %d: Chegada=%d, Fim=%d, Espera=%d, Turnaround=%d\n",
               processes[idx].id, processes[idx].arrival_time, time, wait, turnaround);

        done[idx] = 1;
        completed++;
    }

    free(done);
    Stats s;
    s.avg_turnaround_time = total_turnaround / count;
    s.avg_waiting_time = total_wait / count;
    return s;
}

Stats simulate_priority_p(Process* processes, int count) {
    int time = 0, completed = 0;
    int* remaining = malloc(sizeof(int) * count);
    int* done = calloc(count, sizeof(int));
    for (int i = 0; i < count; i++)
        remaining[i] = processes[i].burst_time;

    double total_wait = 0, total_turnaround = 0;

    while (completed < count) {
        int idx = -1;
        int highest_priority = 9999;

        for (int i = 0; i < count; i++) {
            if (!done[i] && processes[i].arrival_time <= time && processes[i].priority < highest_priority && remaining[i] > 0) {
                highest_priority = processes[i].priority;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        remaining[idx]--;
        time++;

        if (remaining[idx] == 0) {
            done[idx] = 1;
            completed++;
            int turnaround = time - processes[idx].arrival_time;
            int wait = turnaround - processes[idx].burst_time;

            total_turnaround += turnaround;
            total_wait += wait;

            printf("Processo %d: Chegada=%d, Fim=%d, Espera=%d, Turnaround=%d\n",
                   processes[idx].id, processes[idx].arrival_time, time, wait, turnaround);
        }
    }

    free(remaining);
    free(done);
    Stats s;
    s.avg_turnaround_time = total_turnaround / count;
    s.avg_waiting_time = total_wait / count;
    return s;
}
