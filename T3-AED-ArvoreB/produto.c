#include "produto.h"

void imprimirAux(Produto p){
    printf("-> O codigo do produto eh: %d\n", p.codProd);
    printf("-> O nome do produto eh: %s\n", p.nomeProd);
    printf("-> A marca do produto eh: %s\n", p.marcaProd);
    printf("-> A categoria do produto eh: %s\n", p.categProd);
    printf("-> O estoque tem %d unidades\n", p.estoque);
    printf("-> O preco unitario do produto eh: %s\n", p.preco);

}
/*
void imprimirInfo(arquivoB *arqIndice){
    int codUsuario = 0, *pos;

    Produto *p = (Produto *) malloc(sizeof(Produto));

    printf("Informe o codigo do produto que esta procurando: \n");
    scanf("%d", &codUsuario);


}*/

void inserirProdutoArv(Produto p, arquivoB * arqDados, arquivoB *arqIndice){

    printf("\n\nAAAAAAa");

    int *aux; //preciso de uma variavel para saber a posição da chave no vetor de chaves no arquivo

    printf("\n\nAAAAAAa");

    if(!buscaInfo(&aux, p.codProd, arqIndice, arqIndice->cab.pos_cabeca)){
        printf("Inserir Produto na Arvore");
        insereB(p, arqDados, arqIndice, &aux);
    } else {
        printf("Produto já cadastrado\n");
    }
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

    imprimirAux(p);
    inserirProdutoArv(p, arqDados, arqIndice);
}
