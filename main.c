#include "algorithms.h"
int main()
{
    srand(time(NULL)); // Inicializa a seed para aleatoriedade

    int count = 5;
    double lambda_arrival = 3.0; // controla frequência de chegada (Poisson)
    double lambda_burst = 0.5;   // controla variação de burst time (Exponencial)
    int max_priority = 5;

    printf("=== Processos Estáticos ===\n");
    Process *static_list = generate_static_processes(count);
    print_processes(static_list, count);
    free_processes(static_list);

    printf("\n=== Processos Aleatórios ===\n");
    Process* random_list = generate_random_processes(count, lambda_arrival, lambda_burst, max_priority);
    print_processes(random_list, count);
    free_processes(random_list);

    return 0; 
}
