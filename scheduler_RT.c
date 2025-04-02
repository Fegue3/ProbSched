#include <stdio.h>
#include <limits.h>
#include "algorithms.h"

RTStats simulate_rate_monotonic(Process* processes, int count, int simulation_time) {
    int time = 0;
    int completed = 0;
    int missed_deadlines = 0;
    int cpu_busy_time = 0;

    while (time < simulation_time) {
        int selected = -1;
        int min_period = INT_MAX;

        // Escolher o processo com menor período e que está pronto
        for (int i = 0; i < count; i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 && processes[i].period > 0) {
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
            }
        }

        // Verifica deadlines e gera nova instância se necessário
        for (int i = 0; i < count; i++) {
            if (processes[i].period > 0 && (time + 1) % processes[i].period == 0) {
                if (processes[i].remaining_time > 0) {
                    missed_deadlines++;
                }

                // Nova instância do processo
                processes[i].arrival_time = time + 1;
                processes[i].remaining_time = processes[i].burst_time;
            }
        }

        time++;
    }

    RTStats stats;
    stats.total_processes = count;
    stats.completed = completed;
    stats.missed_deadlines = missed_deadlines;
    stats.cpu_utilization = (double)cpu_busy_time / simulation_time;

    return stats;
}