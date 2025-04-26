# ProbSched: Um Simulador para Algoritmos de Escalonamento Probabilístico para Sistemas Operativos

Este projeto é um **simulador de escalonadores de processos** implementado em linguagem C, para a disciplina de **Sistemas Operativos**.  
Permite a simulação de diversos algoritmos de escalonamento, incluindo opções para simulação em **monocore** ou **multicore**.

## 📦 Estrutura do Projeto

- `main.c`: Menu principal e gestão das simulações.
- `algorithms.c/.h`: Funções auxiliares para apoio aos algoritmos.
- `scheduler_*.c`: Implementação dos vários algoritmos de escalonamento.
- `process.c`: Criação e manipulação de processos.
- `Makefile`: Facilita a compilação do projeto.

## 🚀 Como Compilar

```bash
make
```

Ou manualmente:

```bash
gcc main.c process.c algorithms.c scheduler_FCFS.c scheduler_RR.c scheduler_PS.c scheduler_EDF.c scheduler_RT.c scheduler_MQS.c scheduler_multicore.c -o simulator
```

## 🎮 Como Executar

Após a compilação, execute:

```bash
./simulator
```

## 📋 Fluxo de Execução (Exemplo Completo)

### Escolha de Núcleo (Core)

```text
Deseja executar em:
1. Monocore
2. Multicore
Escolha: 1
```

### Menu de Simulação

```text
=== ProbSched - Simulador de Escalonamento ===

--- Escolha o Algoritmo de Escalonamento ---
1. FCFS
2. SJF
3. Round Robin
4. Priority (Nao-Preemptivo)
5. Priority (Preemptivo)
6. EDF
7. Rate Monotonic (RT)
8. Multilevel Queue
0. Sair
Escolha o algoritmo:
```

### Geração de Processos Aleatórios

```text
--- Tipo de Processos ---
1. Introduzir manualmente
2. Lista Estatica pre-definida
3. Gerar Processos Aleatorios
Escolha:
```

### Execução e Resultados (Rate Monotonic)

```text
Lambda para Burst Time (Exponencial): 1
ID      Arrival Burst   Period  Deadline
0       0       1       11      11
1       0       1       10      10
2       0       1       5       5
3       0       1       10      10
4       0       1       13      13
5       0       1       10      10
6       0       1       5       5
Tempo 0: Processo 2 em execução
    Processo 2 finalizado — Chegada=0, Início=0, Fim=1, Espera=0, Turnaround=1

Tempo 1: Processo 6 em execução
    Processo 6 finalizado — Chegada=0, Início=1, Fim=2, Espera=1, Turnaround=2

Tempo 2: Processo 1 em execução
    Processo 1 finalizado — Chegada=0, Início=2, Fim=3, Espera=2, Turnaround=3

Tempo 3: Processo 3 em execução
    Processo 3 finalizado — Chegada=0, Início=3, Fim=4, Espera=3, Turnaround=4

Tempo 4: Processo 5 em execução
    Processo 5 finalizado — Chegada=0, Início=4, Fim=5, Espera=4, Turnaround=5

Tempo 5: Processo 2 em execução
    Processo 2 finalizado — Chegada=5, Início=5, Fim=6, Espera=0, Turnaround=1

Tempo 6: Processo 6 em execução
    Processo 6 finalizado — Chegada=5, Início=6, Fim=7, Espera=1, Turnaround=2

Tempo 7: Processo 0 em execução
    Processo 0 finalizado — Chegada=0, Início=7, Fim=8, Espera=7, Turnaround=8

Tempo 8: Processo 4 em execução
    Processo 4 finalizado — Chegada=0, Início=8, Fim=9, Espera=8, Turnaround=9

Tempo 10: Processo 2 em execução
    Processo 2 finalizado — Chegada=10, Início=10, Fim=11, Espera=0, Turnaround=1

Tempo 11: Processo 6 em execução
    Processo 6 finalizado — Chegada=10, Início=11, Fim=12, Espera=1, Turnaround=2

Tempo 12: Processo 1 em execução
    Processo 1 finalizado — Chegada=10, Início=12, Fim=13, Espera=2, Turnaround=3

Tempo 13: Processo 3 em execução
    Processo 3 finalizado — Chegada=10, Início=13, Fim=14, Espera=3, Turnaround=4

Tempo 14: Processo 5 em execução
    Processo 5 finalizado — Chegada=10, Início=14, Fim=15, Espera=4, Turnaround=5

Tempo 15: Processo 2 em execução
    Processo 2 finalizado — Chegada=15, Início=15, Fim=16, Espera=0, Turnaround=1

Tempo 16: Processo 6 em execução
    Processo 6 finalizado — Chegada=15, Início=16, Fim=17, Espera=1, Turnaround=2

Tempo 17: Processo 0 em execução
    Processo 0 finalizado — Chegada=11, Início=17, Fim=18, Espera=6, Turnaround=7

Tempo 18: Processo 4 em execução
    Processo 4 finalizado — Chegada=13, Início=18, Fim=19, Espera=5, Turnaround=6


--- Estatisticas ---
Espera media: 2.67
Turnaround medio: 3.67
Utilizacao da CPU: 90.00%
Throughput: 0.90 processos/unidade de tempo
```

## 🛠 Funcionalidades

- Geração de processos aleatórios ou carregamento via ficheiro.
- Seleção de algoritmo entre vários métodos clássicos.
- Simulação em Monocore ou Multicore.
- Estatísticas detalhadas por execução.
- Suporte a algoritmos preemptivos e não preemptivos.

## 👨‍💻 Créditos

Projeto desenvolvido por:

- [@Fegue3](https://github.com/Fegue3)
- [@FabioHorta](https://github.com/FabioHorta)
- [@JadfPT](https://github.com/JadfPT)
- [@imdtcode](https://github.com/imdtcode)

## 📜 Licença

Projeto académico. Sem licença explícita.

