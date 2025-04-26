#include "algorithms.h"

Stats simulate_rr(Process *processes, int count, int quantum)
{
    int time = 0;
    int completed = 0;
    int cpu_busy_time = 0;
    int *remaining = malloc(sizeof(int) * count);
    int *arrived = malloc(sizeof(int) * count);
    int *first_start_time = malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++)
    {
        remaining[i] = processes[i].burst_time;
        arrived[i] = 0;
        first_start_time[i] = -1; // ainda não começou
    }

    int *queue = malloc(sizeof(int) * count * 2);
    int front = 0, rear = 0;

    double total_wait = 0;
    double total_turnaround = 0;

    printf("\n--- Historico de Execucoes ---\n");

    // Primeiros processos que chegaram
    for (int i = 0; i < count; i++)
    {
        if (processes[i].arrival_time <= time)
        {
            queue[rear++] = i;
            arrived[i] = 1;
        }
    }

    while (completed < count)
    {
        /*
        if (front == rear) {
             time++; // CPU idle
            for (int i = 0; i < count; i++) {
                 if (!arrived[i] && processes[i].arrival_time <= time) {
                     queue[rear++] = i;
                    arrived[i] = 1;
                }
           }
            continue;
         } Pode causar acessos indevidos a memoria e segfaults
        */

        int idx = queue[front++ % (count * 2)];
        int slice = (remaining[idx] < quantum) ? remaining[idx] : quantum;

        if (first_start_time[idx] == -1)
        {
            first_start_time[idx] = time; // primeira execução
        }

        printf("Tempo %d -> Processo %d executa por %d unidades\n", time, processes[idx].id, slice);

        time += slice;
        cpu_busy_time += slice;
        remaining[idx] -= slice;

        // Verificar novos processos que chegaram durante execução
        for (int i = 0; i < count; i++)
        {
            if (!arrived[i] && processes[i].arrival_time <= time)
            {
                queue[rear++ % (count * 2)] = i;
                arrived[i] = 1;
            }
        }

        if (remaining[idx] > 0)
        {
            queue[rear++ % (count * 2)] = idx;
        }
        else
        {
            completed++;
            int turnaround = time - processes[idx].arrival_time;
            int waiting = turnaround - processes[idx].burst_time;
            total_turnaround += turnaround;
            total_wait += waiting;
        }
    }

    free(remaining);
    free(arrived);
    free(first_start_time);
    free(queue);

    Stats s;
    s.avg_turnaround_time = total_turnaround / count;
    s.avg_waiting_time = total_wait / count;
    s.cpu_utilization = (double)cpu_busy_time / time;
    s.throughput = (double)count / time;
    return s;
}
