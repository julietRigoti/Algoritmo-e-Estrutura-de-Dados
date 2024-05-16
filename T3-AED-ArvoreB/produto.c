#include "produto.h"

//FUNÇOES DE REMOVER

// Descrição: Remove um produto específico dos arquivos de índice e de dados.
// Pré-condição: 'codUsuario' deve ser o código do usuário associado ao produto a ser removido.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
// Pós-condição: O produto associado ao código do usuário é removido dos arquivos de índice e de dados.
void removeProdutoAux(int codUsuario, arquivoB *arqIndice, arquivoB *arqDados){
    if(arqIndice->cab.pos_cabeca != -1) {
        int posVetor;
        int ptDado = busca(codUsuario, arqIndice, arqIndice->cab.pos_cabeca, &posVetor); //retorna o ponteiro para o arquivo de Dados
        arvoreB B, C;
        Produto p;
        lerDados(&B, ptDado, sizeof(arvoreB), arqIndice);
        lerDados(&C, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
        lerDados(&p, B.ptDados[posVetor], sizeof(Produto), arqDados);

        if(arqDados->cab.pos_livre == -1){
            p.codProd = -1;
        } else {
            p.codProd = arqDados->cab.pos_livre;
        }
        arqDados->cab.pos_livre = B.ptDados[posVetor];
        removeArqIndex(arqIndice, &C, arqIndice->cab.pos_cabeca, codUsuario);
        gravaDados(&p, B.ptDados[posVetor], sizeof(Produto), arqDados);
        escreveCabecalho(arqDados);
    }
    else printf("Não possui produtos cadastrados\n");
}

// Descrição: Remove um produto, solicitando informações ao usuário.
// Pré-condição: 'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: O produto é removido dos arquivos de dados e de índice.
void removerProduto(arquivoB *arqDados, arquivoB *arqIndice){
    int codUsuario = 0;

    printf("Informe o codigo do produto que esta procurando: \n");
    scanf("%d", &codUsuario);
    removeProdutoAux(codUsuario, arqIndice, arqDados);
}

//FUNÇOES DE ATUALIZAR

// Descrição: Atualiza informações de um produto, como estoque e preço.
// Pré-condição: 'codProd' deve ser o código do produto a ser atualizado.
//               'estoque' deve ser o novo estoque do produto.
//               'preco' deve ser o novo preço do produto.
//               'op' indica se é uma atualização de estoque (0) ou de preço (1).
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
// Pós-condição: As informações do produto são atualizadas nos arquivos de índice e de dados.
void atualizarInfoText(int codProd, int estoque, char preco[], int op, arquivoB * arqIndice, arquivoB * arqDados){
    int pos;
    int aux = busca(codProd, arqIndice, arqIndice->cab.pos_cabeca, &pos);
    arvoreB B;
    lerDados(&B, aux, sizeof(arvoreB), arqIndice);

    if(aux != -1){
    Produto p;
     lerDados(&p, B.ptDados[pos], sizeof(Produto), arqDados);
        if(op == 0){
            p.estoque = estoque;
        } else if (op == 1){
            strcpy(p.preco, preco);
        } else {
            p.estoque = estoque;
            strcpy(p.preco, preco);
        }
        gravaDados(&p, B.ptDados[pos], sizeof(Produto), arqDados);
    }
}

// Descrição: Solicita informações ao usuário para atualizar um produto.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'op' indica se é uma atualização de estoque (0) ou de preço (1).
// Pós-condição: As informações do produto são atualizadas nos arquivos de índice e de dados.
void atualizarInfo(arquivoB *arqIndice, arquivoB *arqDados, int op){
    int codUsuario = 0, pos ;
    int estoqueNovo;
    char precoNovo[10];
    Produto p;

    printf("Informe o codigo do produto que esta procurando: \n");
    scanf("%d", &codUsuario);

    int aux = busca(codUsuario, arqIndice, arqIndice->cab.pos_cabeca, &pos);
    arvoreB B;

    if(aux != -1){
        lerDados(&B, aux, sizeof(arvoreB), arqIndice);
        lerDados(&p, B.ptDados[pos], sizeof(Produto), arqDados);
        if(op == 1) {
            printf("Informe o novo estoque deste produto: \n");
            scanf("%d", &estoqueNovo);
            p.estoque = estoqueNovo;
        } else if (op == 0){
            printf("Informe o novo preco deste produto: \n");
            scanf("%s%*c", precoNovo);
            strcpy(p.preco, precoNovo);
            }
        gravaDados(&p, B.ptDados[pos], sizeof(Produto), arqDados);
    } else {
        printf("Nao existe esse produto cadastrado...\n");
    }
}

//FUNÇÕES IMPRIMIR

// Descrição: Imprime os detalhes de um produto.
// Pré-condição: 'p' deve ser uma estrutura válida de Produto.
// Pós-condição: Os detalhes do produto são impressos na tela.
void imprimirAux(Produto p){
    printf("-> O codigo do produto eh: %d\n", p.codProd);
    printf("-> O nome do produto eh: %s\n", p.nomeProd);
    printf("-> A marca do produto eh: %s\n", p.marcaProd);
    printf("-> A categoria do produto eh: %s\n", p.categProd);
    printf("-> O estoque tem %d unidades\n", p.estoque);
    printf("-> O preco unitario do produto eh: %s\n", p.preco);
}

// Função para obter o valor da posição atual na fila sem remover o elemento
int front(fila *f) {
    if (vazia(f)) {
        printf("Erro: fila vazia!\n");
        return -1; // Retorna um valor inválido caso a fila esteja vazia
    }
    return f->inicio->chave;
}

// Descrição: Imprime a árvore B na tela.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: A árvore B é impressa na tela.
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
}

// Descrição: Imprime os produtos na ordem definida na árvore B.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'pos' é a posição atual na árvore B.
// Pós-condição: Os produtos são impressos na ordem definida na árvore B.
void imprimirInOrdem(arquivoB *arqIndice, arquivoB *arqDados, int pos){
    if(pos != -1){
        arvoreB B; int i;
        lerDados(&B, pos, sizeof(arvoreB), arqIndice);
        for(i = 0; i < B.numChaves; i++){
            imprimirInOrdem(arqIndice, arqDados, B.filhos[i]);
            Produto p;
            lerDados(&p, B.ptDados[i], sizeof(Produto), arqDados);
            printf("-> O codigo do produto eh: %d\n", p.codProd);
            printf("-> O nome do produto eh: %s\n\n", p.nomeProd);
        }
        imprimirInOrdem(arqIndice, arqDados, B.filhos[i]);
    }
}

// Descrição: Imprime informações sobre os produtos.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
// Pós-condição: As informações dos produtos são impressas na tela.
void imprimirInfo(arquivoB *arqIndice, arquivoB *arqDados){
    int codUsuario = 0, pos;
    Produto p;

    printf("Informe o codigo do produto que esta procurando: \n");
    scanf("%d", &codUsuario);

    int aux = busca(codUsuario, arqIndice, arqIndice->cab.pos_cabeca, &pos);
    if(aux != -1) {
        arvoreB B;
        lerDados(&B, aux, sizeof(arvoreB), arqIndice);
        lerDados(&p, B.ptDados[pos], sizeof(Produto), arqDados);
        imprimirAux(p);
    }
}

// Descrição: Imprime as posições livres no arquivo de dados.
// Pré-condição: 'arqDados' deve ser um ponteiro válido para o arquivo de dados.
// Pós-condição: As posições livres no arquivo de dados são impressas na tela.
void imprimirLivreDados(arquivoB *arqDados){
    if(arqDados->cab.pos_livre == -1){
        printf("Não foi removido nenhum produto\n");
        return;
    }
    Produto livre;
    lerDados(&livre, arqDados->cab.pos_livre, sizeof(Produto), arqDados);
    printf("Posicao livre = %d\n", arqDados->cab.pos_livre);
    printf("Livre: ");
    while(livre.codProd != -1){
        printf("%d ", livre.codProd);
        lerDados(&livre, livre.codProd, sizeof(Produto), arqDados);
    }
    printf("\n");
}

// Descrição: Imprime as posições livres no arquivo de índice.
// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: As posições livres no arquivo de índice são impressas na tela.
void imprimirLivreIndice(arquivoB *arqIndice){
    if(arqIndice->cab.pos_livre == -1){
        printf("Não foi removido nenhuma pagina\n");
        return;
    }
    arvoreB livre;
    lerDados(&livre, arqIndice->cab.pos_livre, sizeof(arvoreB), arqIndice);
    printf("Posicao livre = %d\n", arqIndice->cab.pos_livre);
    printf("Livre: ");
    while(livre.chaves[0] != -1){
        printf("%d ", livre.chaves[0]);
        lerDados(&livre, livre.chaves[0], sizeof(arvoreB), arqIndice);
    }
    printf("\n");
}

//INSERÇÃO

// Descrição: Insere um produto na árvore B.
// Pré-condição: 'p' deve ser uma estrutura válida de Produto.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: O produto é inserido na árvore B.
void inserirProdutoArv(Produto p, arquivoB * arqDados, arquivoB *arqIndice){

    int posVetor;
    int posArq = busca(p.codProd, arqIndice, arqIndice->cab.pos_cabeca, &posVetor);

    if(posArq == -1) {
        if(arqDados->cab.pos_livre != -1){
            Produto livre;
            lerDados(&livre, arqDados->cab.pos_livre, sizeof(Produto), arqDados);
            gravaDados(&p, arqDados->cab.pos_livre, sizeof(Produto), arqDados);
            insereArqIndex(p.codProd, arqDados->cab.pos_livre, arqDados, arqIndice);
            arqDados->cab.pos_livre = livre.codProd;
        }
        else {
            gravaDados(&p, arqDados->cab.pos_topo, sizeof(Produto), arqDados);
            insereArqIndex(p.codProd, arqDados->cab.pos_topo, arqDados, arqIndice);
            arqDados->cab.pos_topo++;
        }
        escreveCabecalho(arqDados);
    }
}

// Descrição: Solicita informações ao usuário para cadastrar um novo produto.
// Pré-condição: 'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: Um novo produto é cadastrado nos arquivos de dados e de índice.
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

    inserirProdutoArv(p, arqDados, arqIndice);
}
