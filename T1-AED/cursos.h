#ifndef CURSOS_H
#define CURSOS_H

#include "menu.h"

#define MAX 50

typedef struct{
    int codCurso;
    char nomeCurso[MAX];
    char area; //E para Exatas, H para Humanas, B para Biológicas
    int prox; 
} Cursos;

// Função para cadastrar um curso
// Pré-condição: Nenhuma
// Pós-condição: O curso é cadastrado e gravado no arquivo binário
void cadastrarCurso();

// Função para imprimir a lista de cursos
// Pré-condição: Nenhuma
// Pós-condição: A lista de cursos é impressa na saída padrão
void imprimirListCurso();

#endif
