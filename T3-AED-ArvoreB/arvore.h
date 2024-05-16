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

// Pré-condição: 'aux' deve ser um ponteiro válido para uma estrutura de árvore B.
// Pós-condição: A página referenciada por 'aux' é inicializada para uso.
void inicializaPagina(arvoreB *aux);

// Descrição: Busca recursivamente um código de usuário em um arquivo de índice.
// Pré-condição: 'codUsuario' deve ser o código de usuário a ser buscado.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'posArq' deve ser a posição atual no arquivo de índice.
//               'pos' deve ser um ponteiro válido para armazenar a posição encontrada.
// Pós-condição: Se o código de usuário for encontrado, 'pos' conterá a posição.
//               Caso contrário, 'pos' conterá -1.
int busca(int codUsuario, arquivoB* arqIndice, int posArq, int *pos);

// Pré-condição: 'pos' deve ser um ponteiro válido para a posição de busca.
//               'codProd' deve ser o código do produto a ser buscado.
//               'arqDIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'i' é um índice usado na busca.
// Pós-condição: Retorna a posição onde as informações são encontradas.
int buscaInfo(int *pos, int codProd, arquivoB * arqDIndice, int i);

// Pré-condição: 'codProd' deve ser o código do produto a ser inserido.
//               'ptDado' deve ser a posição de dados associada ao código do produto.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: O novo índice é inserido no arquivo de índice.
void insereArqIndex(int codProd, int ptDado, arquivoB * arqDados, arquivoB *arqIndice);

// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'B' deve ser um ponteiro válido para a árvore B.
//               'posArq' deve ser a posição atual no arquivo de índice.
//               'codUsuario' deve ser o código de usuário a ser removido.
// Pós-condição: O índice correspondente ao código de usuário é removido do arquivo de índice.
void removeArqIndex(arquivoB *arqIndice, arvoreB *B, int posArq, int codUsuario);

#endif
