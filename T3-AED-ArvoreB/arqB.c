#include "arqB.h"

// Pré-condição: 'arq' é um ponteiro válido para a estrutura do arquivo binário
// Pós-condição: O cabeçalho do arquivo binário é impresso no console
void lerCabecalho(arquivoB* bin){ //não preciso modificar
    fseek(bin->f, 0, SEEK_SET);
    fread(&bin->cab, sizeof(cabecalho), 1, bin->f);
}

// Função para escrever o cabeçalho no arquivo binário
// Pré-condição: 'bin' é um ponteiro válido para a estrutura do arquivo binário
// Pós-condição: O cabeçalho é escrito no arquivo binário
void escreveCabecalho(arquivoB* bin){ //não preciso modificar
    fseek(bin->f, 0, SEEK_SET);
    fwrite(&bin->cab, sizeof(cabecalho), 1, bin->f);
}

// Função para gravar dados em uma posição específica do arquivo binário
// Pré-condição: 'dados' é um ponteiro válido para os dados a serem gravados, 'pos' é a posição no arquivo, 'tamanho' é o tamanho dos dados, 'bin' é um ponteiro válido para a estrutura do arquivo binário
// Pós-condição: Os dados são gravados na posição especificada do arquivo binário
void gravaDados(void *dados, int pos, size_t tamanho, arquivoB *bin){
    fseek(bin->f, sizeof(cabecalho) + pos * tamanho, SEEK_SET);
    fwrite(dados, tamanho, 1, bin->f);
}

// Função para ler dados de uma posição específica do arquivo binário
// Pré-condição: 'dados' é um ponteiro válido para armazenar os dados lidos, 'pos' é a posição no arquivo, 'tamanho' é o tamanho dos dados,
//'bin' é um ponteiro válido para a estrutura do arquivo binário
// Pós-condição: Os dados são lidos da posição especificada do arquivo binário e armazenados em 'dados'
void lerDados(void *dados, int pos, size_t tamanho, arquivoB *bin) {
    fseek(bin->f, sizeof(cabecalho) + pos * tamanho, SEEK_SET);
    fread(dados, tamanho, 1, bin->f);
}

//Função para fechar um arquivo binario
//Pré-condição: 'arq' é o nome do arquivo a ser fechado
//Pós-condição: o arquivo é fechado
void fechaArquivo(arquivoB * arq){
    fclose(arq->f);
}

// Função para abrir um arquivo binário
// Pré-condição: 'nomeArq' é o nome do arquivo a ser aberto
// Pós-condição: Retorna um ponteiro para a estrutura do arquivo binário associado ao arquivo aberto
arquivoB *abrirArquivo(char * nomeArq){
    arquivoB *cab = (arquivoB *) malloc (sizeof(arquivoB));
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
