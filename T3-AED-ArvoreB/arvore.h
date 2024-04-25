#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>

#include "arqB.h"

#define ORDEM 5
typedef struct {
    int numChaves;
    int chave[ORDEM];
    int filho[ORDEM + 1]; //tente usar o filho[0] para fazer a lista encadeada no arquivo de indice
    int arqDados[ORDEM]; 
}arvB;

int buscaInfo(int codProd, arqB * arqDados); 

#endif