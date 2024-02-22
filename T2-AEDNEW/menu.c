#include "menu.h"

// Função para registrar informações de um arquivo de texto em uma estrutura de dados
// Pré-condição: O arquivo passado como argumento está aberto para leitura
// Pós-condição: As informações do arquivo de texto são registradas na estrutura de dados
void registroArqTXT(FILE *f) {
    char linha[100];
    while (fgets(linha, sizeof(linha), f) != NULL) {
        char token;
        if (sscanf(linha, " %c", &token) == 1) {
            if (token == 'C') {
                Cursos aux;
                if (sscanf(linha, "C;%99[^;];%99[^;];%c", aux.codCurso,
                           aux.nomeCurso, &aux.area) == 3) {
                    gravaCursos(&aux);
                }
            } else if (token == 'D') {
                Disciplinas aux;
                if (sscanf(linha, "D;%99[^;];%99[^;];%99[^;];%99[^\n]", aux.codDisc,
                           aux.nomeDisciplina, aux.codCurso, aux.serie) == 4) {
                    gravaDisciplinas(&aux);
                }
            } else if (token == 'P') {
                Professores aux;
                if (sscanf(linha, "P;%99[^;];%99[^\n]", aux.codProf,
                           aux.nomeProfessor) == 2) {
                    gravaProfessores(&aux);
                }
            } else if (token == 'M') {
               Distribuicao aux;
                if (sscanf(linha, "M;%99[^;];%99[^;];%99[^\n]", aux.codDisciplina,
                           aux.anoLetivo, aux.codProf) == 3) {
                    gravaDistribuicoes(&aux);
                }
            }
            else if(token == 'R'){
             Remocao aux;
                if(sscanf(linha, "R;%99[^;];%99[^\n]", aux.cod, aux.ano) == 2){
                 removerDistDisc(aux);
                }
            }
        }
    }
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
void carregarLote(){
    FILE *fr;
    char path[50];
    do{
        printf("Nome do arquivo: ");
        scanf("%s%*c", path);
        fr = fopen(path, "r");
    }
    while(loadFile(fr));
    registroArqTXT(fr);
    printf("\n");
    fclose(fr);
}

// Função para imprimir o menu
// Pré-condição: Nenhuma
// Pós-condição: O menu é impresso na saída padrão
void printar() {
    printf(
            "\n0 - Sair do programa\n1 - Cadastrar curso\n2 - Cadastrar "
            "disciplina\n3 - Cadastrar professor\n4 - Cadastrar distribuicao de "
            "disciplina\n");
    printf(
            "5 - Remover distribuicao de disciplina\n6 - Imprimir lista de "
            "cursos\n7 - Imprimir lista de disciplinas\n8 - Imprimir lista de "
            "professores\n");
    printf(
            "9 - Imprimir lista de distribuicao de disciplina\n10 - Imprimir lista de posicoes de registros livres da distribuição\n"
            "11 - Imprimir a arvore binaria da distribuicao de disciplinas por nivel\n12 - Carregamento em lote\n");
}

// Função que exibe o menu e permite ao usuário escolher uma opção
// Pré-condição: Nenhuma
// Pós-condição: Dependendo da escolha do usuário, as funções correspondentes são chamadas
void menu() {
    int aux;
    printar();
    printf("\nInforme o que deseja fazer:\n");
    scanf("%d%*c", &aux);
    printf("\n");
    while (aux >= 0 || aux <= 10) {
        switch (aux) {
            case 0:
                exit(0);
            case 1:
                cadastrarCursos();
                break;
            case 2:
                cadastrarDisciplinas();
                break;
            case 3:
                cadastrarProfessores();
                break;
            case 4:
                cadastrarDistDisc();
                break;
            case 5:
                retirarDistDisc();
                break;
            case 6:
                imprimirListCursos();
                break;
            case 7:
                imprimirListDisc();
                break;
            case 8:
                imprimirListProf();
                break;
            case 9:
                imprimirListDist();
                break;
            case 10:
                imprimelivre();
                break;
            case 11:
                imprimirpornivel();
                break;
            case 12:
                carregarLote();
                break;
            default:
                printf("Tente novamente!\n");
        }
        printar();
        printf("\nInforme o que deseja fazer:\n");
        scanf("%d%*c", &aux);
    }
}

