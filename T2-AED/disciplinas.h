#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H

#include "arqB.h"
#include "cursos.h"

#define MAX 50
#define NUM 10

typedef struct{
    char nomeDisciplina[MAX];
    char codDisc[NUM];
    char codD[NUM];
    char codCurso[NUM];
    char serie[NUM];
    int proxEsq;
    int proxDir;
}Disciplinas;

// Função para imprimir a lista de Disciplinas
// Pré-condição: Nenhuma
// Pós-condição: A lista de Disciplinas é impressa na saída padrão
void imprimirListDisc();

// Função para gravar uma disciplina em um arquivo binário
// Pré-condição: 'aux' contém os dados da disciplina a ser gravada
// Pós-condição: Os dados da disciplina são gravados no arquivo binário
void gravaDisciplinas(Disciplinas *aux);

// Função para cadastrar uma disciplina
// Pré-condição: Nenhuma
// Pós-condição: A disciplina é cadastrada e gravada no arquivo binário
void cadastrarDisciplinas();

#endif
