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

    while (time < simulation_time) {
        int selected = -1;
        int min_period = INT_MAX;

        // Escolher o processo com menor período e que está pronto
        for (int i = 0; i < count; i++) {
            if (processes[i].arrival_time <= time &&
                processes[i].remaining_time > 0 &&
                processes[i].period > 0) {
                if (processes[i].period < min_period) {
                    min_period = processes[i].period;
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            processes[selected].remaining_time--;
            cpu_busy_time++;

            if (processes[selected].remaining_time == 0) {
                completed++;
                int turnaround = time + 1 - (processes[selected].arrival_time);
                int wait = turnaround - processes[selected].burst_time;
                total_turnaround += turnaround;
                total_wait += wait;
            }
        }

        // Verifica deadlines e gera nova instância se necessário
        for (int i = 0; i < count; i++) {
            if (processes[i].period > 0 && (time + 1) % processes[i].period == 0) {
                if (processes[i].remaining_time > 0) {
                    missed_deadlines++;
                }

                // Nova instância
                processes[i].arrival_time = time + 1;
                processes[i].remaining_time = processes[i].burst_time;
            }
        }

        time++;
    }

    Stats s;
    s.avg_waiting_time = completed > 0 ? total_wait / completed : 0;
    s.avg_turnaround_time = completed > 0 ? total_turnaround / completed : 0;
    s.cpu_utilization = (double)cpu_busy_time / simulation_time;
    s.throughput = (double)completed / simulation_time;
    s.missed_deadlines = missed_deadlines;

    return s;
}
