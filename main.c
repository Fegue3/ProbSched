#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"

int main() {
    srand(time(NULL));  // Inicializa a seed para aleatoriedade

    int count = 5;

    printf("=== Processos Estáticos ===\n");
    Process* static_list = generate_static_processes(count);
    print_processes(static_list, count);
    free_processes(static_list);

    printf("\n=== Processos Aleatórios ===\n");
    Process* random_list = generate_random_processes(count, 5, 10, 5);
    print_processes(random_list, count);
    free_processes(random_list);

    return 0;
}
