#ifndef CURSOS_H
#define CURSOS_H

#include "arqB.h"

#define MAX 50
#define NUM 10

typedef struct{
    char codCurso[NUM];
    char codC[NUM];
    char nomeCurso[MAX];
    char area; //E para Exatas, H para Humanas, B para Biológicas
    int proxEsq;
    int proxDir;
} Cursos;

// Função para imprimir a lista de cursos
// Pré-condição: Nenhuma
// Pós-condição: A lista de cursos é impressa na saída padrão
void imprimirListCursos();

// Função para gravar um curso em um arquivo binário
// Pré-condição: 'aux' contém os dados do curso a ser gravado
// Pós-condição: Os dados do curso são gravados no arquivo binário
void gravaCursos(Cursos *aux);

// Função para cadastrar um curso
// Pré-condição: Nenhuma
// Pós-condição: O curso é cadastrado e gravado no arquivo binário
void cadastrarCursos();

#endif
