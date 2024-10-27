#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DESCR 51
#define MAX_PROCS 100

// Armazena um horário de chegada
typedef struct {
    int hh;
    int mm;
    int ss;
} horario;

// Armazena informações de um processo
typedef struct {
    int prior;
    horario chegada;
    char descricao[MAX_DESCR];
} celula;

celula processos[MAX_PROCS];
int total_processos = 0; // Número de processos armazenados no momento

// Compara prioridades
int compara_prioridade(const void *a, const void *b) {
    return ((celula *)b)->prior - ((celula *)a)->prior;
}

// Compara horários
int compara_tempo(const void *a, const void *b) {
    horario h1 = ((celula *)a)->chegada;
    horario h2 = ((celula *)b)->chegada;
    if (h1.hh != h2.hh) return h1.hh - h2.hh;
    if (h1.mm != h2.mm) return h1.mm - h2.mm;
    return h1.ss - h2.ss;
}

// Adiciona um novo processo ao vetor
void add_processo() {
    if (total_processos >= MAX_PROCS) return;
    scanf("%d %d:%d:%d %s", &processos[total_processos].prior, &processos[total_processos].chegada.hh,
           &processos[total_processos].chegada.mm, &processos[total_processos].chegada.ss, processos[total_processos].descricao);
    total_processos++;
}

// Executa e remove um processo da lista com base em prioridade ou horário
void exec_processo(char opcao) {
    if (total_processos == 0) return;

    int indice = 0;
    if (opcao == 'p') {
        // Encontrar o processo com maior prioridade
        for (int i = 1; i < total_processos; i++)
            if (processos[i].prior > processos[indice].prior)
                indice = i;
    } else {
        // Encontrar o processo com o menor horário
        for (int i = 1; i < total_processos; i++) {
            if (compara_tempo(&processos[i], &processos[indice]) < 0)
                indice = i;
        }
    }

    // Remove o processo executado deslocando os processos subsequentes
    for (int i = indice; i < total_processos - 1; i++)
        processos[i] = processos[i + 1];
    total_processos--;
}

// Exibe o próximo processo a ser executado
void next_processo(char opcao) {
    if (total_processos == 0) return;

    int indice = 0;
    if (opcao == 'p') {
        // Encontrar o processo com maior prioridade
        for (int i = 1; i < total_processos; i++)
            if (processos[i].prior > processos[indice].prior)
                indice = i;
    } else {
        // Encontrar o processo com o menor horário
        for (int i = 1; i < total_processos; i++)
            if (compara_tempo(&processos[i], &processos[indice]) < 0)
                indice = i;
    }

    // Imprime as informações do processo
    printf("%02d %02d:%02d:%02d %s\n",
           processos[indice].prior,
           processos[indice].chegada.hh,
           processos[indice].chegada.mm,
           processos[indice].chegada.ss,
           processos[indice].descricao);
    printf("\n");
}

// Modifica a prioridade de um processo
void change_prioridade(int valor_antigo, int valor_novo) {
    for (int i = 0; i < total_processos; i++) {
        if (processos[i].prior == valor_antigo) {
            processos[i].prior = valor_novo;
            return;
        }
    }
    return;
}

// Modifica o horário de um processo
void change_horario(horario anterior, horario novo) {
    for (int i = 0; i < total_processos; i++) {
        if (anterior.hh == processos[i].chegada.hh && anterior.mm == processos[i].chegada.mm
            && anterior.ss == processos[i].chegada.ss){
           processos[i].chegada = novo;
           return;
        }
    }
    return;
}


// Imprime todos os processos em ordem de prioridade ou horário
void print_processos(char opcao) {
    if (total_processos == 0) return;

    // Ordena os processos conforme a opção escolhida
    if (opcao == 'p') {
        qsort(processos, total_processos, sizeof(celula), compara_prioridade);
    } else {
        qsort(processos, total_processos, sizeof(celula), compara_tempo);
    }

    // Imprime cada processo na ordem definida
    for (int i = 0; i < total_processos; i++) {
        printf("%02d %02d:%02d:%02d %s\n",
               processos[i].prior,
               processos[i].chegada.hh,
               processos[i].chegada.mm,
               processos[i].chegada.ss,
               processos[i].descricao);
    }
    printf("\n");
}

int main() {
    char comando[10];

    while (scanf(" %s", comando) != EOF) {
        if (strcmp(comando, "add") == 0) {
            add_processo();
        } else if (strcmp(comando, "exec") == 0) {
            char opcao;
            scanf(" -%c", &opcao);
            exec_processo(opcao);
        } else if (strcmp(comando, "next") == 0) {
            char opcao;
            scanf(" -%c", &opcao);
            next_processo(opcao);
        } else if (strcmp(comando, "change") == 0) {
            char opcao;
            scanf(" -%c", &opcao);
            if (opcao == 'p') {
                int anterior, novo;
                scanf("%d|%d", &anterior, &novo);
                change_prioridade(anterior, novo);
            } else if (opcao == 't') {
                horario anterior, novo;
                scanf("%02d:%02d:%02d|%02d:%02d:%02d", &anterior.hh, &anterior.mm, &anterior.ss,
                       &novo.hh, &novo.mm, &novo.ss);
                change_horario(anterior, novo);
            }
        } else if (strcmp(comando, "print") == 0) {
            char opcao;
            scanf(" -%c", &opcao);
            print_processos(opcao);
        } else if (strcmp(comando, "quit") == 0) {
            break;
        }
    }

    return 0;
}
