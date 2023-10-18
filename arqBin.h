#ifndef ARQBIN_H
#define ARQBIN_H

#include "menu.h"

typedef struct { //estrutura do arquivo
	int pos_cabeca; //posição do início da lista
	int pos_topo; // 1a posição não usada no fim do arquivo
	int pos_livre; // posição do início da lista de nós livres
} cabecalho;

typedef struct{
    FILE *f;
    cabecalho cab;
}arqBin;

void lerCabecalho(arqBin* bin);

void escreveCabecalho(arqBin* bin);

void gravaDados(void *dados, int pos, size_t tamanho, arqBin *bin);

void lerDados(void *dados, int pos, size_t tamanho, arqBin *bin);

arqBin *abrirArquivo(char *nomeArq);

#endif