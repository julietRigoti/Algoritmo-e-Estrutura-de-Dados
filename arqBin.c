#include "menu.h"
#include "arqBin.h"

void lerCabecalho(arqBin* bin){
    fseek(bin->f,0,SEEK_SET);
    fread(&bin->cab,sizeof(cabecalho), 1, bin->f);
}

void escreveCabecalho(arqBin* bin){
    fseek(bin->f,0,SEEK_SET);
    fwrite(&bin->cab,sizeof(cabecalho), 1, bin->f);
}

void gravaDados(void *dados, int pos, size_t tamanho, arqBin *bin){
    fseek(bin->f, sizeof(cabecalho) + pos * tamanho, SEEK_SET);
    fwrite(dados, tamanho, 1, bin->f);
}

void lerDados(void *dados, int pos, size_t tamanho, arqBin *bin) {
    fseek(bin->f, sizeof(cabecalho) + pos * tamanho, SEEK_SET);
    fread(dados, tamanho, 1, bin->f);
}

arqBin *abrirArquivo(char * nomeArq){
    arqBin *cab = (arqBin *) malloc (sizeof(arqBin));
    cab->f = fopen(nomeArq, "r+b");
    if(cab->f == NULL){
        cab->f = fopen(nomeArq, "w+b");
        cab->cab.pos_cabeca = -1;
        cab->cab.pos_topo = 0;
        cab->cab.pos_livre = -1;
        escreveCabecalho(cab);
    }else{
        lerCabecalho(cab);
    }
    return cab;
}