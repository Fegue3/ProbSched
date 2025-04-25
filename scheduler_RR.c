#include "algorithms.h"

Stats simulate_rr(Process* processes, int count, int quantum) {
    int time = 0;
    int completed = 0;
    int* remaining = malloc(sizeof(int) * count);
    int* arrived = malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        remaining[i] = processes[i].burst_time;
        arrived[i] = 0;
    }

    int* queue = malloc(sizeof(int) * count * 2); // fila circular simples
    int front = 0, rear = 0;

    double total_wait = 0;
    double total_turnaround = 0;

    // Primeiros processos que chegaram
    for (int i = 0; i < count; i++) {
        if (processes[i].arrival_time <= time) {
            queue[rear++] = i;
            arrived[i] = 1;
        }
    }

    while (completed < count) {
        if (front == rear) {
            time++; // idle time
            for (int i = 0; i < count; i++) {
                if (!arrived[i] && processes[i].arrival_time <= time) {
                    queue[rear++] = i;
                    arrived[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++ % (count * 2)];

        int slice = remaining[idx] < quantum ? remaining[idx] : quantum;
        int start_time = time;
        time += slice;
        remaining[idx] -= slice;

        // Verificar novos processos que chegaram durante este slice
        for (int i = 0; i < count; i++) {
            if (!arrived[i] && processes[i].arrival_time <= time) {
                queue[rear++ % (count * 2)] = i;
                arrived[i] = 1;
            }
        }

        if (remaining[idx] > 0) {
            queue[rear++ % (count * 2)] = idx; // volta ao fim da fila
        } else {
            completed++;
            int turnaround = time - processes[idx].arrival_time;
            int waiting = turnaround - processes[idx].burst_time;
            total_turnaround += turnaround;
            total_wait += waiting;
            printf("Processo %d: Chegada=%d, Início=%d, Fim=%d, Espera=%d, Turnaround=%d\n",
                processes[idx].id, processes[idx].arrival_time, start_time, time, waiting, turnaround);         
        }
    }

    free(remaining);
    free(arrived);
    free(queue);

    Stats s;
    s.avg_turnaround_time = total_turnaround / count;
    s.avg_waiting_time = total_wait / count;
    return s;
}
