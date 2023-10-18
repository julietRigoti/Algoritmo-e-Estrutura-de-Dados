#ifndef PROFESSORES_H
#define PROFESSORES_H

#define MAX 50

#include "menu.h"

typedef struct{
    int codProf;
    char nomeProfessor[MAX];
    int prox; 
}Professores;

// Função para cadastrar um professor
// Pré-condição: Nenhuma
// Pós-condição: O professor é cadastrado e gravado no arquivo binário
void cadastrarProfessor();

// Função para imprimir a lista de professores
// Pré-condição: Nenhuma
// Pós-condição: A lista de professores é impressa na saída padrão
void imprimirListProf();

#endif