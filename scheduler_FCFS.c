#include "algorithms.h"

Stats simulate_fcfs(Process* processes, int count) {
    int time = 0;
    double total_wait = 0;
    double total_turnaround = 0;

    for (int i = 0; i < count; i++) {
        if (time < processes[i].arrival_time) {
            time = processes[i].arrival_time;
        }
        int start_time = time;
        time += processes[i].burst_time;

        int wait = start_time - processes[i].arrival_time;
        int turnaround = time - processes[i].arrival_time;

        total_wait += wait;
        total_turnaround += turnaround;

        printf("Processo %d: Chegada = %d,Inicio = %d, Fim = %d, Espera = %d, Turnaround = %d\n",
               processes[i].id, processes[i].arrival_time, start_time ,time, wait, turnaround);
    }

    Stats s;
    s.avg_waiting_time = total_wait / count;
    s.avg_turnaround_time = total_turnaround / count;
    return s;
}