#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>

#include "arqB.h"
#include "arvore.h"

typedef struct {
    int codProd; //na remocao, usa o codProd para fazer a lista encadeada
    int estoque;
    char preco[10];
    char nomeProd[50];
    char categProd[50];
    char marcaProd[30];
}Produto;

void imprimirAux(Produto p);

void imprimirInOrdem(arquivoB *arqIndice, arquivoB *arqDados, int pos);

void imprimirInfo(arquivoB *arqIndice, arquivoB *arqDados);

void cadastrarProduto(arquivoB * arqDados, arquivoB *arqIndice);

void inserirProdutoArv(Produto p, arquivoB * arqDados, arquivoB *arqIndice);

#endif
