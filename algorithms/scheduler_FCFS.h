#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct {
    double avg_waiting_time;
    double avg_turnaround_time;
} Stats;

Stats simulate_fcfs(Process* processes, int count);

#endif