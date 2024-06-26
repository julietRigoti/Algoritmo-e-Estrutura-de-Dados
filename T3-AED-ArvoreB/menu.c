#include "menu.h"

// Função para registrar informações de um arquivo de texto em uma estrutura de dados
// Pré-condição: O arquivo passado como argumento está aberto para leitura
// Pós-condição: As informações do arquivo de texto são registradas na estrutura de dados
void registroArqTXT(FILE *f, arquivoB *arqDados, arquivoB *arqIndice) {
    char linha[200];
    Produto p;
    while (fgets(linha, sizeof(linha), f) != NULL) {
        char token;
        if (sscanf(linha, " %c", &token) == 1) {
            if (token == 'I') {
                if(sscanf(linha, "I;%d;%[^;];%[^;];%[^;];%d;%[^;]", &p.codProd, p.nomeProd, p.marcaProd, p.categProd, &p.estoque, p.preco) == 6){
                   inserirProdutoArv(p, arqDados, arqIndice);
                }
            } else if (token == 'A') {
                if (sscanf(linha, "A;%d;%d;%[^;]", &p.codProd, &p.estoque, p.preco) <= 3) {
                    if(sscanf(linha, "A;%d;%d;%s ", &p.codProd, &p.estoque, p.preco) == 3){
                        atualizarInfoText(p.codProd, p.estoque, p.preco, 2, arqIndice, arqDados);
                    } else if (sscanf(linha, "A;%d;%d;", &p.codProd, &p.estoque) == 2){ //ARRUMAR
                        atualizarInfoText(p.codProd, p.estoque, p.preco, 0, arqIndice, arqDados);
                    } else if (sscanf(linha, "A;%d;;%s", &p.codProd, p.preco) == 2){
                        atualizarInfoText(p.codProd, p.estoque, p.preco, 1, arqIndice, arqDados);
                    }
                }
            } else if(token == 'R'){
                if(sscanf(linha, "R;%d", &p.codProd) == 1){
                    removeProdutoAux(p.codProd, arqIndice, arqDados);
                }
            }
        }
    }
}

// Função para imprimir o menu
// Pré-condição: Nenhuma
// Pós-condição: O menu é impresso na saída padrão
void mostrarOpc(){
     printf(
            "\n0 - Sair do programa\n1 - Cadastrar produto\n2 - Remover produto\n3 - Atualizar preco\n4 - Atualizar estoque\n");
    printf(
            "5 - Imprimir informacoes\n6 - Imprimir lista de todos os produtos\n7 - Imprimir arvore\n8 - Imprimir lista de livres do arquivo de indices\n");
    printf(
            "9 - Imprimir lista de livres do arquivo de dados\n10 - Carregamento em lote\n");
}

// Função para verificar se o arquivo foi carregado com sucesso
// Pré-condição: O arquivo é passado como argumento
// Pós-condição: Retorna 0 se o arquivo foi carregado com sucesso, 1 caso contrário
int loadFile(FILE* file){
    if(file == NULL){
        printf("Falha ao ler arquivo!\n\n");
        return 1;
    }
    else{
        printf("Arquivo lido com sucesso!\n");
        return 0;
    }
}

// Função para carregar informações de um arquivo em lote
// Pré-condição: Nenhuma
// Pós-condição: As informações do arquivo em lote são registradas na estrutura de dados
void carregarLote(arquivoB *arqDados, arquivoB *arqIndice){
    FILE *fr;
    char path[50];
    do{
        printf("Nome do arquivo: ");
        scanf("%s%*c", path);
        fr = fopen(path, "r");
    }
    while(loadFile(fr));
    registroArqTXT(fr, arqDados, arqIndice);
    printf("\n");
    fclose(fr);
}

// Função que exibe o menu e permite ao usuário escolher uma opção
// Pré-condição: Nenhuma
// Pós-condição: Dependendo da escolha do usuário, as funções correspondentes são chamadas
void menu(){
    int choose;
    mostrarOpc();
    printf("\nInforme o que deseja fazer:\n");
    scanf("%d%*c", &choose);
    printf("\n");

    arquivoB *arqDados = abrirArquivo("../T3-AED-ArvoreB/arqDados");
    arquivoB *arqIndice = abrirArquivo("../T3-AED-ArvoreB/arqIndices");

    while (choose >= 0 || choose <= 10) {
        switch (choose) {
            case 0:
                fechaArquivo(arqDados);
                fechaArquivo(arqIndice);
                exit(0);
            case 1:
                cadastrarProduto(arqDados, arqIndice);
                break;
            case 2:
                removerProduto(arqDados, arqIndice);
                break;
            case 3:
                atualizarInfo(arqIndice, arqDados, 0);
                break;
            case 4:
                atualizarInfo(arqIndice, arqDados, 1);
                break;
            case 5:
                imprimirInfo(arqIndice, arqDados);
                break;
            case 6:
                imprimirInOrdem(arqIndice, arqDados, arqIndice->cab.pos_cabeca);
                break;
            case 7:
                 imprimirArvore(arqIndice);
                break;
            case 8:
                imprimirLivreIndice(arqIndice);
                break;
            case 9:
                imprimirLivreDados(arqDados);
                break;
            case 10:
                carregarLote(arqDados, arqIndice);
                break;
            default:
                printf("Tente novamente!\n");
        }
        mostrarOpc();
        printf("\nInforme o que deseja fazer:\n");
        scanf("%d%*c", &choose);
    }
}
