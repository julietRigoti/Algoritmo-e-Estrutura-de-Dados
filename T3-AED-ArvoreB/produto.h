#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdio.h>
#include <stdlib.h>

#include "arqB.h"

typedef struct {
    int codProd; //na remocao, usa o codProd para fazer a lista encadeada
    int estoque; 
    double preco;
    char nomeProd[50];    
    char categProd[50];
    char marcaProd[30];
}Produto;

void cadastrarProduto(arqB * arqDados, arqB *arqIndice);

void inserirProdutoArv(Produto *p, arqB * arqDados, arqB *arqIndice);

#endif