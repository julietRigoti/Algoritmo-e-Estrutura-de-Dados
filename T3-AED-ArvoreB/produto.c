#include "produto.h"

/*void imprimirArvore(arquivoB *arqIndice){
    int pos = arqIndice->cab.pos_cabeca;
    if(pos == -1) return;

    fila *f = cria_fila_vazia();
    arvoreB B, C;

    lerDados(&B, pos, sizeof(arvoreB), arqIndice);
    for(int i = 0; i < B.numChaves; i++){
        enqueue(f, B.chaves[i]);
    }
    enqueue(f, -1);
    printf("[");
    while(!vazia(f)){
        printf("%d ", f->inicio->chave);
        dequeue(f);

        for(int i = 0; i <= B.numChaves; i++){
            lerDados(&C, B.filhos[i], sizeof(arvoreB), arqIndice);
            for(int j = 0; j < C.numChaves; j++)
                enqueue(f, C.chaves[j]);
        }
        if(f->inicio->chave == -1){
            printf("\n");
            dequeue(f);
            enqueue(f, -1);
        }
        if(f->inicio->chave == -1 && f->inicio->prox == NULL){
            printf("]\n\n");
            break;
        }
    }
}*/

// Função para obter o valor da posição atual na fila sem remover o elemento
int front(fila *f) {
    if (vazia(f)) {
        printf("Erro: fila vazia!\n");
        return -1; // Retorna um valor inválido caso a fila esteja vazia
    }
    return f->inicio->chave;
}

void imprimirArvore(arquivoB *arqIndice) {
    int pos = arqIndice->cab.pos_cabeca;
    if (pos == -1)
        return;

    fila *f = cria_fila_vazia();

    // Enfileira a posição da raiz da árvore B
    enqueue(f, pos);
    enqueue(f, -1); // Marca o final do nível atual

    while (!vazia(f)) {
        int curr_pos = front(f); // Obtém a posição atual
        dequeue(f); // Remove a posição atual da fila

        if (curr_pos == -1) { // Verifica se é o final do nível
            printf("\n");
            if (!vazia(f)) {
                enqueue(f, -1); // Marca o final do próximo nível
            }
        } else {
            arvoreB B;
            lerDados(&B, curr_pos, sizeof(arvoreB), arqIndice);

            printf("[");
            for (int i = 0; i < B.numChaves; i++) {
                printf("%d ", B.chaves[i]);
            }
            printf("] ");

            // Enfileira os filhos do nó atual
            for (int i = 0; i <= B.numChaves; i++) {
                if (B.filhos[i] != -1) {
                    enqueue(f, B.filhos[i]);
                }
            }
        }
    }

    //libera_fila(f); // Libera a memória da fila
}

void imprimirAux(Produto p){
    printf("-> O codigo do produto eh: %d\n", p.codProd);
    printf("-> O nome do produto eh: %s\n", p.nomeProd);
    printf("-> A marca do produto eh: %s\n", p.marcaProd);
    printf("-> A categoria do produto eh: %s\n", p.categProd);
    printf("-> O estoque tem %d unidades\n", p.estoque);
    printf("-> O preco unitario do produto eh: %s\n", p.preco);
}

void imprimirInOrdem(arquivoB *arqIndice, arquivoB *arqDados, int pos){
    if(pos != -1){
        arvoreB B; int i;
        lerDados(&B, pos, sizeof(arvoreB), arqIndice);
        for(i = 0; i < B.numChaves; i++){
            imprimirInOrdem(arqIndice, arqDados, B.filhos[i]);
            Produto p;
            lerDados(&p, B.ptDados[i], sizeof(Produto), arqDados);
            imprimirAux(p);
        }
        imprimirInOrdem(arqIndice, arqDados, B.filhos[i]);
    }
}

void imprimirInfo(arquivoB *arqIndice, arquivoB *arqDados){
    int codUsuario = 0;
    Produto p;
    printf("Informe o codigo do produto que esta procurando: \n");
    scanf("%d", &codUsuario);
    imprimirCabecalho(arqIndice);
    printf("\n");
    imprimirCabecalho(arqDados);
    int ptDado = busca(codUsuario, arqIndice, arqIndice->cab.pos_cabeca);
    lerDados(&p, ptDado, sizeof(Produto), arqDados);
    imprimirAux(p);
}

void inserirProdutoArv(Produto p, arquivoB * arqDados, arquivoB *arqIndice){

    printf("Inserir Produto na Arvore\n");
    gravaDados(&p, arqDados->cab.pos_topo, sizeof(Produto),arqDados);
    insereB(p.codProd, arqDados, arqIndice);
    arqDados->cab.pos_topo++;
    escreveCabecalho(arqDados);
}

void cadastrarProduto(arquivoB * arqDados, arquivoB *arqIndice){
    Produto p;

    printf("Informe o codigo do produto:\n");
    scanf("%d%*c", &p.codProd);
    printf("Informe o nome do produto:\n");
    scanf("%[^\n]%*c", p.nomeProd);
    printf("Informe a marca do produto:\n");
    scanf("%[^\n]%*c", p.marcaProd);
    printf("Informe a categoria do produto:\n");
    scanf("%[^\n]%*c", p.categProd);
    printf("Informe a quantidade no estoque do produto:\n");
    scanf("%d%*c", &p.estoque);
    printf("Informe o preco do produto:\n");
    scanf("%[^\n]%*c", p.preco);

    //imprimirAux(p);
    inserirProdutoArv(p, arqDados, arqIndice);
}
