typedef struct {
    int id;               // ID do processo (único e sequencial)
    int arrival_time;     // Tempo de chegada
    int burst_time;       // Tempo total de CPU necessário
    int remaining_time;   // Tempo restante (útil para RR ou preemptivos)
    int priority;         // Prioridade (para Priority Scheduling)
    
    // Para algoritmos de tempo real
    int deadline;         // Deadline (para EDF)
    int period;           // Período (para Rate Monotonic)
} Process;