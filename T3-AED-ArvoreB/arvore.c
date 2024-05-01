#include "arvore.h"

void imprimirInfoB(arvoreB B){
    int i;
     printf("B.chaves[ ");
    for (i = 0; i < ORDEM; i++)
    {
       printf(" %d ", B.chaves[i]);
    }
    printf("]\n");
    printf("B.ptDados[ ");
    for (i = 0; i < ORDEM; i++)
    {
       printf(" %d ", B.ptDados[i]);
    }
    printf("]\n");
    printf("B.filhos[ ");
    for (i = 0; i < ORDEM + 1; i++){
       printf(" %d ", B.filhos[i]);
    }
    printf("]\n");
    printf("B.numChave: %d\n", B.numChaves);
}

arvoreB * inicializaArvore(){
    arvoreB * x;
    for (int i = 0; i < ORDEM; i++){
        x->chaves[i] = -1;
        x->ptDados[i] = -1;
        x->numChaves = 0;
    }
    for (int i = 0; i <= ORDEM; i++) x->filhos[i] = -1;

    return x;
}

int ehFolha(arvoreB *B){
    return (B->filhos[0] == -1);
}

int overflow(arvoreB *B){
    return (B->numChaves == ORDEM);
}

int buscaInfo(int *pos, int codProd, arquivoB * arqIndice, int i){
    Produto p;
    arvoreB B;
    lerDados(&B, i,sizeof(arvoreB), arqIndice);

    for ((*pos) = 0; (*pos) < B.numChaves; (*pos)++){
        if(codProd == B.chaves[(*pos)])
            return 1;
        else if(codProd < B.chaves[(*pos)])
            break; //codProd pode estar na subarvore filho
    }
    return 0;
}

void adicionaDireita(arvoreB *B, int *pos, int codProd, int k, int novoFilho){
    int i;
    for(i = B->numChaves; i > (*pos); i--){
        B->chaves[i] = B->chaves[i-1];
        B->filhos[i+1] = B->filhos[i];
        B->ptDados[i] = B->ptDados[i-1];
    }
    B->chaves[(*pos)] = codProd;
    B->ptDados[(*pos)] = k;
    B->filhos[(*pos)+1] = novoFilho;
    B->numChaves++;
}

/*int split(int posRaiz, int *m, int *ptDado, arquivoB *arqIndice){
    arvoreB *C = inicializaArvore();
    arvoreB *B;
    int posNova;

    lerDados(&B, posRaiz, sizeof(arvoreB), arqIndice);

    int q = B->numChaves/2; // 5/2 = 2

    C->numChaves = B->numChaves - q - 1; //5 - 2 - 1 = 2

    B->numChaves = q;
    *m = B->chaves[q]; //chave mediana
    *ptDado = B->ptDados[q];
    C->filhos[0] = B->filhos[q+1];

    for (int i = 0; i < C->numChaves; i++){
        C->chaves[i] = B->chaves[q+i+1];
        C->ptDados[i] = B->chaves[q+i+1];
        C->filhos[i+1] = B->filhos[q+i+2];
    }
    gravaDados(&C, arqIndice->cab.pos_topo, sizeof(arquivoB), arqIndice);
    gravaDados(&B, posRaiz, sizeof(arquivoB), arqIndice);
    return
}*/

void insereAux(int codProd, int *pos, arquivoB *arqIndice, int k){
    //lembrando que esse *pos é a posição no vetor de chaves
    arvoreB B;
    lerDados(&B, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
    if (ehFolha(&B)){
       adicionaDireita(&B, pos, codProd, k, -1);
    } else {

    }
    printf("\n\n");
    gravaDados(&B, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
   /* arvoreB L;
    lerDados(&L, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
    imprimirInfoB(L);*/
}

void insereB(Produto p, arquivoB * arqDados, arquivoB *arqIndice, int *pos){

    arvoreB *B;
    //Produto l;
    gravaDados(&p,arqDados->cab.pos_topo, sizeof(Produto),arqDados);
    /*lerDados(&l,arqDados->cab.pos_topo, sizeof(Produto),arqDados);
    imprimirAux(l);*/

    if (arqIndice->cab.pos_cabeca == -1){
        printf("Primeira inserção");
        B->numChaves = 1;
        B->chaves[0] = p.codProd;
        B->ptDados[0] = arqDados->cab.pos_topo;
        for (int i = 0; i <= ORDEM; i++) B->filhos[i] = -1;

        gravaDados(&B, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice); //minha raiz
        arqIndice->cab.pos_cabeca = arqIndice->cab.pos_topo;
        arqIndice->cab.pos_topo++;
        escreveCabecalho(arqIndice);
    } else {
        insereAux(p.codProd, pos, arqIndice, arqDados->cab.pos_topo);

        //lerDados(&B, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);

        if(overflow(B)){ //verifica se o nó está cheio
        printf("Entrou no overflow");
           /*int chaveMed, ptDado;
            int posNo = split(arqIndice->cab.pos_cabeca, &chaveMed, &ptDado, arqIndice);

            arvoreB novaRaiz;
            novaRaiz.chaves[0] = chaveMed;
            novaRaiz.ptDados[0] = ptDado;
            novaRaiz.filhos[0] = arqIndice->cab.pos_cabeca;
            novaRaiz.filhos[1] = posNo;
            novaRaiz.numChaves = 1;
            for (int i = (((int)ORDEM/2) + 1); i < ORDEM; i++)
            {
                novaRaiz.filhos[i] = -1;
            }


            arqIndice->cab.pos_topo++;
            escreveCabecalho(arqIndice);
            gravaDados(&novaRaiz, arqIndice->cab.pos_topo, sizeof(arvoreB), arqIndice);
            arqIndice->cab.pos_cabeca = arqIndice->cab.pos_topo;
            arqIndice->cab.pos_topo++;
            escreveCabecalho(arqIndice);*/
        }
    }

    arqDados->cab.pos_topo++;

   /* arvoreB L;
    lerDados(&L, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
    imprimirInfoB(L);
    escreveCabecalho(arqDados);
    printf("ArqDados\n");
    imprimirCabecalho(arqDados);
    printf("ArqIndices\n");
    imprimirCabecalho(arqIndice);*/

}
