#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H

#include "menu.h"

typedef struct{
    int codDisciplina;
    int anoLetivo;
    int codProf; 
    int prox; 
} Materia;

// Função para cadastrar uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é cadastrada e gravada no arquivo binário
void cadastrarDistDisc();

// Função para imprimir a lista de distribuição de disciplinas
// Pré-condição: Nenhuma
// Pós-condição: A lista de distribuição de disciplinas é impressa na saída padrão
void imprimirDistDisc();

// Função para remover uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é removida do arquivo
void removerDistDisc();


#endif
