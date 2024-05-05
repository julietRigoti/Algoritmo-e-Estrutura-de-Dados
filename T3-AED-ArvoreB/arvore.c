#include "arvore.h"

int ehFolha(arvoreB *B){
    return (B->filhos[0] == -1);
}

int overflow(int numChaves){
    return (numChaves == ORDEM);
}

void imprimirInfoB(arvoreB B){
    int i;
     printf("B.chaves[ ");
    for (i = 0; i < B.numChaves; i++)
    {
       printf(" %d ", B.chaves[i]);
    }
    printf("]\n");
    printf("B.ptDados[ ");
    for (i = 0; i < B.numChaves; i++)
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

int busca(int codUsuario, arquivoB* arqIndice, int posK){
    if(posK == -1) return -1;

    arvoreB B;
    lerDados(&B, posK, sizeof(arvoreB), arqIndice);

    int i = 0;
    while(i < B.numChaves && B.chaves[i] < codUsuario) i++;
    if((i+1) > B.numChaves || B.chaves[i] > codUsuario)
        return busca(codUsuario, arqIndice, B.filhos[i]);
    return B.ptDados[i];
}

int buscaInfo(int *aux, int codProd, arquivoB * arqIndice, int pos){
    arvoreB B;
    lerDados(&B, pos, sizeof(arvoreB), arqIndice);

    if(arqIndice->cab.pos_cabeca != -1){
        for ((*aux) = 0; (*aux) < B.numChaves; (*aux)++){
            if(codProd == B.chaves[(*aux)])
                return 1;
            else if(codProd < B.chaves[(*aux)])
                break; //codProd pode estar na subarvore filho
        }
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

int split(int pos, int *m, int *ptDado, arquivoB *arqIndice){
    arvoreB C, B;
    lerDados(&B, pos, sizeof(arvoreB), arqIndice);

    int posNova = arqIndice->cab.pos_topo;

    int q = B.numChaves/2; // 5/2 = 2
    C.numChaves = B.numChaves - q - 1; //5 - 2 - 1 = 2
    B.numChaves = q;
    *m = B.chaves[q]; //chave mediana
    *ptDado = B.ptDados[q];
    C.filhos[0] = B.filhos[q+1];

    for(int i = 0; i < C.numChaves; i++){
        C.chaves[i] = B.chaves[q+i+1];
        C.ptDados[i] = B.ptDados[q+i+1];
        C.filhos[i+1] = B.filhos[q+i+2];
    }

    gravaDados(&C, posNova, sizeof(arvoreB), arqIndice);
    gravaDados(&B, pos, sizeof(arvoreB), arqIndice);

    if(posNova == arqIndice->cab.pos_topo) {
        arqIndice->cab.pos_topo++;
        //escreveCabecalho(arqIndice);
        //imprimirCabecalho(arqIndice);
    }
    return posNova;
}

void insereAux(int codProd, arquivoB *arqIndice, int dadosTopo, int indicePos){
    //lembrando que esse *pos é a posição no vetor de chaves
    //k é linha do arquivo de dados
    arvoreB B, L;
    lerDados(&B, indicePos, sizeof(arvoreB), arqIndice);
    int aux = 0;
        //preciso de uma variavel para saber a posição da chave no vetor de chaves no arquivo
    if(!buscaInfo(&aux, codProd, arqIndice, indicePos)){
        if (ehFolha(&B)){
           adicionaDireita(&B, &aux, codProd, dadosTopo, -1);
        } else {
            insereAux(codProd, arqIndice, dadosTopo, B.filhos[aux]);
            lerDados(&L, B.filhos[aux], sizeof(arvoreB), arqIndice);
            if(overflow(L.numChaves)){
                int chaveMed, ptDado;
                 int posNo = split(B.filhos[aux], &chaveMed, &ptDado, arqIndice);
                 adicionaDireita(&B, &aux, chaveMed, ptDado, posNo);
            }
        }
    }
    gravaDados(&B, indicePos, sizeof(arvoreB), arqIndice);

   /* arvoreB L;
    lerDados(&L, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
    imprimirInfoB(L);*/
}

void insereB(int codProd, arquivoB * arqDados, arquivoB *arqIndice){

    arvoreB B;
    arvoreB L;
    if (arqIndice->cab.pos_cabeca == -1){
        B.numChaves = 1;
        B.chaves[0] = codProd;
        B.ptDados[0] = arqDados->cab.pos_topo;
        for(int i = B.numChaves; i < ORDEM; i++){
            B.chaves[i] = -1;
            B.ptDados[i] = -1;
        }
        for(int i = 0; i <= ORDEM; i++) B.filhos[i] = -1;

        gravaDados(&B, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice); //minha raiz
        arqIndice->cab.pos_cabeca = arqIndice->cab.pos_topo;
        arqIndice->cab.pos_topo++;
        escreveCabecalho(arqIndice);
    } else {
        insereAux(codProd, arqIndice, arqDados->cab.pos_topo, arqIndice->cab.pos_cabeca);

        lerDados(&B, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);

        if(overflow(B.numChaves)){ //verifica se o nó está cheio
            int chaveMed, ptDado;
            int posNo = split(arqIndice->cab.pos_cabeca, &chaveMed, &ptDado, arqIndice);

            arvoreB novaRaiz;
            novaRaiz.chaves[0] = chaveMed;
            novaRaiz.ptDados[0] = ptDado;
            novaRaiz.filhos[0] = arqIndice->cab.pos_cabeca;
            novaRaiz.filhos[1] = posNo;
            novaRaiz.numChaves = 1;
            lerDados(&B, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
            for (int i = (((int)ORDEM/2) + 1); i < ORDEM; i++)
                B.filhos[i] = -1;
            for(int i = 2; i <= ORDEM; i++)
                novaRaiz.filhos[i] = -1;

            gravaDados(&novaRaiz, arqIndice->cab.pos_topo, sizeof(arvoreB), arqIndice);
            gravaDados(&B, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
            arqIndice->cab.pos_cabeca = arqIndice->cab.pos_topo; //possiveis mudanças
            arqIndice->cab.pos_topo++;
            escreveCabecalho(arqIndice);
            //imprimirCabecalho(arqIndice);
        }
    }
    /*for(int i = 0; i < arqIndice->cab.pos_topo; i++){
        lerDados(&L, i, sizeof(arvoreB), arqIndice);
        imprimirInfoB(L);
    }*/
}
