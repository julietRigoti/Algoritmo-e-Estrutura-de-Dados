#include "produto.h"

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
