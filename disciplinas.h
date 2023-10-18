#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H

#define MAX 50

#include "menu.h"

typedef struct{
    char nomeDisciplina[MAX];
    int codDisc;
    int codCurso;
    int serie;
    int prox; 
}Disciplinas;

// Função para cadastrar uma disciplina
// Pré-condição: Nenhuma
// Pós-condição: A disciplina é cadastrada e gravada no arquivo binário
void cadastrarDisciplina();

// Função para imprimir a lista de disciplinas
// Pré-condição: Nenhuma
// Pós-condição: A lista de disciplinas é impressa na saída padrão, incluindo o código do curso ao qual pertencem
void imprimirListDisc();

#endif