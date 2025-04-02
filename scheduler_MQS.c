#include "algorithms.h"

Stats simulate_mlq(Process* processes, int count, int quantum) {
    // Três filas: alta prioridade (RR), média (RR), baixa (FCFS)
    Process* queue_high[count]; // prioridade 1
    Process* queue_mid[count];  // prioridade 2-3
    Process* queue_low[count];  // prioridade 4-5
    int high_size = 0, mid_size = 0, low_size = 0;

    // Separar os processos por prioridade
    for (int i = 0; i < count; i++) {
        if (processes[i].priority == 1)
            queue_high[high_size++] = &processes[i];
        else if (processes[i].priority <= 3)
            queue_mid[mid_size++] = &processes[i];
        else
            queue_low[low_size++] = &processes[i];
    }

    // Alocar arrays temporários para as simulações
    Process* high_list = malloc(sizeof(Process) * high_size);
    Process* mid_list = malloc(sizeof(Process) * mid_size);
    Process* low_list = malloc(sizeof(Process) * low_size);

    for (int i = 0; i < high_size; i++) high_list[i] = *queue_high[i];
    for (int i = 0; i < mid_size; i++)  mid_list[i] = *queue_mid[i];
    for (int i = 0; i < low_size; i++)  low_list[i] = *queue_low[i];

    printf("\n--- [Fila Alta - RR] ---\n");
    Stats s1 = simulate_rr(high_list, high_size, quantum);

    printf("\n--- [Fila Média - RR] ---\n");
    Stats s2 = simulate_rr(mid_list, mid_size, quantum);

    printf("\n--- [Fila Baixa - FCFS] ---\n");
    Stats s3 = simulate_fcfs(low_list, low_size);

    // Combinar as estatísticas
    Stats final;
    final.avg_waiting_time = (s1.avg_waiting_time * high_size +
                              s2.avg_waiting_time * mid_size +
                              s3.avg_waiting_time * low_size) / count;

    final.avg_turnaround_time = (s1.avg_turnaround_time * high_size +
                                 s2.avg_turnaround_time * mid_size +
                                 s3.avg_turnaround_time * low_size) / count;

    free(high_list);
    free(mid_list);
    free(low_list);

    return final;
}
