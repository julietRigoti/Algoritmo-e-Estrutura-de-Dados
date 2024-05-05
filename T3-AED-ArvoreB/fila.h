#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 10

struct no{
    int chave;
    struct no* prox;
};

typedef struct{
    struct no* inicio;
    struct no* fim;
} fila;

// Função para verificar se a fila está vazia
// Pré-condição: Recebe um ponteiro para a fila (f).
// Pós-condição: Retorna 1 se a fila estiver vazia, 0 caso contrário.
int vazia(fila* f);

// Função para criar uma fila vazia
// Pré-condição: Nenhuma.
// Pós-condição: Retorna um ponteiro para uma fila recém-criada com inicio e fim apontando para NULL.
fila* cria_fila_vazia();

// Função para adicionar um elemento ao final da fila (enqueue)
// Pré-condição: Recebe um ponteiro para a fila (f) e uma string (anoCod) a ser adicionada à fila.
// Pós-condição: Insere um novo nó com a string ao final da fila, atualizando o ponteiro de fim se necessário.
void enqueue(fila* f, int chave);

// Função para remover o elemento no início da fila (dequeue)
// Pré-condição: Recebe um ponteiro para a fila (f).
// Pós-condição: Remove o nó no início da fila, atualizando o ponteiro de início e, se necessário, o ponteiro de fim.
void dequeue(fila* f);

#endif
