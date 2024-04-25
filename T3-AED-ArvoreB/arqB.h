#ifndef ARQB_H
#define ARQB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { //estrutura do arquivo
    int pos_cabeca; //posição do início da lista
    int pos_topo; // 1a posição não usada no fim do arquivo
    int pos_livre; // posição do início da lista de nós livres
} cabecalho;

typedef struct{
    FILE *f;
    cabecalho cab;
}arqB;

// Função para ler o cabeçalho do arquivo binário
// Pré-condição: 'bin' é um ponteiro válido para a estrutura do arquivo binário
// Pós-condição: O cabeçalho do arquivo binário é lido e armazenado na estrutura 'bin'
void lerCabecalho(arqB *bin);

// Função para escrever o cabeçalho no arquivo binário
// Pré-condição: 'bin' é um ponteiro válido para a estrutura do arquivo binário
// Pós-condição: O cabeçalho é escrito no arquivo binário
void escreveCabecalho(arqB *bin);

// Função para gravar dados em uma posição específica do arquivo binário
// Pré-condição: 'dados' é um ponteiro válido para os dados a serem gravados, 'pos' é a posição no arquivo, 'tamanho' é o tamanho dos dados, 'bin' é um ponteiro válido para a estrutura do arquivo binário
// Pós-condição: Os dados são gravados na posição especificada do arquivo binário
void gravaDados(void *dados, int pos, size_t tamanho, arqB *bin);

// Função para ler dados de uma posição específica do arquivo binário
// Pré-condição: 'dados' é um ponteiro válido para armazenar os dados lidos, 'pos' é a posição no arquivo, 'tamanho' é o tamanho dos dados, 'bin' é um ponteiro válido para a estrutura do arquivo binário
// Pós-condição: Os dados são lidos da posição especificada do arquivo binário e armazenados em 'dados'
void lerDados(void *dados, int pos, size_t tamanho, arqB *bin);

//int saberPos(arqB * arq, void *dados);

// Função para abrir um arquivo binário
// Pré-condição: 'nomeArq' é o nome do arquivo a ser aberto
// Pós-condição: Retorna um ponteiro para a estrutura do arquivo binário associado ao arquivo aberto
arqB *abrirArquivo(char *nomeArq);

//Função para fechar um arquivo binario 
void fechaArquivo(arqB *arq);

#endif
