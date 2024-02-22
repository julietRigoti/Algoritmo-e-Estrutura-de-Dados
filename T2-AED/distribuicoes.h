#ifndef DISTRIBUICOES_H
#define DISTRIBUICOES_H

#include "arqB.h"
#include "disciplinas.h"
#include "professores.h"
#include "fila.h"

#define NUM 10

typedef struct{
    char codDisciplina[NUM];
    char anoLetivo[NUM];
    char AnoCod[3*NUM + 1];
    char codProf[NUM];
    int proxEsq;
    int proxDir;
} Distribuicao;

typedef struct{
    char cod[NUM];
    char ano[NUM];
    char anoCod[3*NUM + 1];
} Remocao;

// Função para imprimir disciplinas livres
// Pré-condição: Nenhuma
// Pós-condição: As disciplinas livres são impressas no console
void imprimelivre();

// Função para imprimir disciplinas por nível
// Pré-condição: Nenhuma
// Pós-condição: As disciplinas são impressas no console organizadas por nível
void imprimirpornivel();

// Função para imprimir lista de distribuições de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A lista de distribuições de disciplina é impressa no console
void imprimirListDist();

// Função para remover uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é removida do arquivo
void removerDistDisc(Remocao aux);

// Função para imprimir disciplinas livres
// Pré-condição: Nenhuma
// Pós-condição: As disciplinas livres são impressas no console
void imprimelivre();

// Função para imprimir disciplinas por nível
// Pré-condição: Nenhuma
// Pós-condição: As disciplinas são impressas no console organizadas por nível
void imprimirpornivel();

// Função para imprimir lista de distribuições de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A lista de distribuições de disciplina é impressa no console
void imprimirListDist();

// Função para remover uma distribuição de disciplina
// Pré-condição: A estrutura 'aux' contém informações necessárias para a remoção
// Pós-condição: A distribuição de disciplina é removida do arquivo
void removerDistDisc(Remocao aux);

// Função para retirar uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é retirada
void retirarDistDisc();

// Função para gravar uma distribuição de disciplina em um arquivo binário
// Pré-condição: 'dist' contém os dados da distribuição de disciplina a ser gravada
// Pós-condição: Os dados da distribuição de disciplina são gravados no arquivo binário
void gravaDistribuicoes(Distribuicao *dist);

// Função para cadastrar uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é cadastrada e gravada no arquivo binário
void cadastrarDistDisc();

#endif

