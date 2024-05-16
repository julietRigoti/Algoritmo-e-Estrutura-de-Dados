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

// Descrição: Remove um produto específico dos arquivos de índice e de dados.
// Pré-condição: 'codUsuario' deve ser o código do usuário associado ao produto a ser removido.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
// Pós-condição: O produto associado ao código do usuário é removido dos arquivos de índice e de dados.
void removeProdutoAux(int codUsuario, arquivoB *arqIndice, arquivoB *arqDados);

// Descrição: Remove um produto, solicitando informações ao usuário.
// Pré-condição: 'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: O produto é removido dos arquivos de dados e de índice.
void removerProduto(arquivoB *arqDados, arquivoB *arqIndice);

// Descrição: Atualiza informações de um produto, como estoque e preço.
// Pré-condição: 'codProd' deve ser o código do produto a ser atualizado.
//               'estoque' deve ser o novo estoque do produto.
//               'preco' deve ser o novo preço do produto.
//               'op' indica se é uma atualização de estoque (0) ou de preço (1).
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
// Pós-condição: As informações do produto são atualizadas nos arquivos de índice e de dados.
void atualizarInfoText(int codProd, int estoque, char preco[], int op, arquivoB * arqIndice, arquivoB * arqDados);

// Descrição: Solicita informações ao usuário para atualizar um produto.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'op' indica se é uma atualização de estoque (0) ou de preço (1).
// Pós-condição: As informações do produto são atualizadas nos arquivos de índice e de dados.
void atualizarInfo(arquivoB *arqIndice, arquivoB *arqDados, int op);

// Descrição: Imprime a árvore B na tela.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: A árvore B é impressa na tela.
void imprimirArvore(arquivoB *arqIndice);

// Descrição: Imprime os detalhes de um produto.
// Pré-condição: 'p' deve ser uma estrutura válida de Produto.
// Pós-condição: Os detalhes do produto são impressos na tela.
void imprimirAux(Produto p);

// Descrição: Imprime os produtos na ordem definida na árvore B.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'pos' é a posição atual na árvore B.
// Pós-condição: Os produtos são impressos na ordem definida na árvore B.
void imprimirInOrdem(arquivoB *arqIndice, arquivoB *arqDados, int pos);

// Descrição: Imprime informações sobre os produtos.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
// Pós-condição: As informações dos produtos são impressas na tela.
void imprimirInfo(arquivoB *arqIndice, arquivoB *arqDados);

// Descrição: Imprime as posições livres no arquivo de dados.
// Pré-condição: 'arqDados' deve ser um ponteiro válido para o arquivo de dados.
// Pós-condição: As posições livres no arquivo de dados são impressas na tela.
void imprimirLivreDados(arquivoB *arqDados);

// Descrição: Imprime as posições livres no arquivo de índice.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: As posições livres no arquivo de índice são impressas na tela.
void imprimirLivreIndice(arquivoB *arqIndice);

// Descrição: Solicita informações ao usuário para cadastrar um novo produto.
// Pré-condição: 'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: Um novo produto é cadastrado nos arquivos de dados e de índice.
void cadastrarProduto(arquivoB * arqDados, arquivoB *arqIndice);

// Descrição: Insere um produto na árvore B.
// Pré-condição: 'p' deve ser uma estrutura válida de Produto.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: O produto é inserido na árvore B.
void inserirProdutoArv(Produto p, arquivoB * arqDados, arquivoB *arqIndice);

#endif
