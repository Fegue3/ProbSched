typedef struct {
    int id;               // ID do processo (único e sequencial)
    int arrival_time;     // Tempo de chegada
    int burst_time;       // Tempo total de CPU necessário
    int remaining_time;   // Tempo restante (útil para RR ou preemptivos)
    int priority;         // Prioridade (para Priority Scheduling)

    int deadline;         // Deadline (para EDF)
    int period;           // Período (para Rate Monotonic)
} Process;

Process* generate_static_processes(int count);

Process* generate_random_processes(int count, double lambda_arrival, double lambda_burst, int max_priority);

void print_processes(Process* processes, int count);

void free_processes(Process* processes);