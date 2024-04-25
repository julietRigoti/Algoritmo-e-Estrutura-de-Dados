#include "produto.h"

void inserirProdutoArv(Produto *p, arqB * arqDados, arqB *arqIndice){
    
    if (!buscaInfo(p->codProd, arqDados)){
        /* code */
    }
    
}

void cadastrarProduto(arqB * arqDados, arqB *arqIndice){
    Produto *p = (Produto *) malloc (sizeof(Produto)); 

    printf("Informe o codigo do produto:\n");
    scanf("%d%*c", &p->codProd);
    printf("Informe o nome do produto:\n");
    scanf("%[^\n]%*c", p->nomeProd);        
    printf("Informe a marca do produto:\n");
    scanf("%[^\n]%*c", p->marcaProd);  
    printf("Informe a categoria do produto:\n");
    scanf("%[^\n]%*c", p->categProd); 
    printf("Informe a quantidade no estoque do produto:\n");
    scanf("%d", &p->estoque);
    printf("Informe o preco do produto:\n");
    scanf("%lf", &p->preco);

    inserirProdutoArv(p, arqDados, arqIndice); 
    free(p);
}