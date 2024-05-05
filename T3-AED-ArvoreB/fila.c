#include "fila.h"

// Função para verificar se a fila está vazia
// Pré-condição: Recebe um ponteiro para a fila (f).
// Pós-condição: Retorna 1 se a fila estiver vazia, 0 caso contrário.
int vazia(fila* f){
    return(f->inicio == NULL);
}

// Função para criar uma fila vazia
// Pré-condição: Nenhuma.
// Pós-condição: Retorna um ponteiro para uma fila recém-criada com inicio e fim apontando para NULL.
fila* cria_fila_vazia(){
    fila *aux= (fila*) malloc(sizeof(fila));
    aux->inicio = NULL;
    aux->fim = NULL;
    return aux;
}

// Função para adicionar um elemento ao final da fila (enqueue)
// Pré-condição: Recebe um ponteiro para a fila (f) e uma string (anoCod) a ser adicionada à fila.
// Pós-condição: Insere um novo nó com a string ao final da fila, atualizando o ponteiro de fim se necessário.
void enqueue(fila* f, int chave){
    struct no* aux = (struct no*) malloc(sizeof(struct no));
    aux->chave = chave;
    aux->prox = NULL;
    if (vazia(f)){
        f-> inicio = aux;
    }
    else {
        f->fim->prox =aux;
    }
    f->fim = aux;
}

// Função para remover o elemento no início da fila (dequeue)
// Pré-condição: Recebe um ponteiro para a fila (f).
// Pós-condição: Remove o nó no início da fila, atualizando o ponteiro de início e, se necessário, o ponteiro de fim.
void dequeue(fila *f){
    if(!vazia(f)){
        struct no *aux = f->inicio;
        if(f->inicio == f->fim) f->fim = NULL;
        f->inicio = f->inicio->prox;
        free(aux);
    }
}
