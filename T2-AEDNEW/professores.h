#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "arqB.h"

#define MAX 50
#define NUM 10

typedef struct{
    char codProf[NUM];
    char codP[NUM];
    char nomeProfessor[MAX];
    int proxEsq;
    int proxDir;
}Professores;

// Função para imprimir a lista de professores
// Pré-condição: Nenhuma
// Pós-condição: A lista de professores é impressa na saída padrão
void imprimirListProf();

// Função para gravar um professor em um arquivo binário
// Pré-condição: 'prof' contém os dados do professor a ser gravado
// Pós-condição: Os dados do professor são gravados no arquivo binário
void gravaProfessores(Professores *prof);

// Função para cadastrar um professor
// Pré-condição: Nenhuma
// Pós-condição: O professor é cadastrado e gravado no arquivo binário
void cadastrarProfessores();

#endif
