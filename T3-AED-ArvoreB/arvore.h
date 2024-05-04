#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

#include "arqB.h"

#define ORDEM 5
typedef struct {
    int numChaves;
    int chaves[ORDEM];
    int filhos[ORDEM + 1]; //tente usar o filho[0] para fazer a lista encadeada no arquivo de indice
    int ptDados[ORDEM];
}arvoreB;

int busca(int codUsuario, arquivoB* arqIndice, int posK);

int buscaInfo(int *pos, int codProd, arquivoB * arqDIndice, int i);

void insereB(int codProd, arquivoB * arqDados, arquivoB *arqIndice);

#endif
