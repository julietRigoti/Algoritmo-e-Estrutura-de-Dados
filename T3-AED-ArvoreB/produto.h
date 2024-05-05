#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arqB.h"
#include "arvore.h"
#include "fila.h"

typedef struct {
    int codProd; //na remocao, usa o codProd para fazer a lista encadeada
    int estoque;
    char preco[10];
    char nomeProd[50];
    char categProd[50];
    char marcaProd[30];
}Produto;

void atualizarInfoText(int codProd, int estoque, char preco[], int op, arquivoB * arqIndice, arquivoB * arqDados);

void atualizarInfo(arquivoB *arqIndice, arquivoB *arqDados, int op);

void imprimirArvore(arquivoB *arqIndice);

void imprimirAux(Produto p);

void imprimirInOrdem(arquivoB *arqIndice, arquivoB *arqDados, int pos);

void imprimirInfo(arquivoB *arqIndice, arquivoB *arqDados);

void cadastrarProduto(arquivoB * arqDados, arquivoB *arqIndice);

void inserirProdutoArv(Produto p, arquivoB * arqDados, arquivoB *arqIndice);

#endif
