#include "menu.h"

// Função para imprimir o menu
// Pré-condição: Nenhuma
// Pós-condição: O menu é impresso na saída padrão
void printar() {
    printf(
        "\n0-Sair do programa\n1-cadastra curso\n2-cadastrar "
        "disciplina\n3-cadastrar professor\n4-cadastrar distribuicao de "
        "disciplina\n");
    printf(
        "5-remover distribuicao de disciplina\n6-imprimir lista de "
        "cursos\n7-imprimir lista de disciplinas\n8-imprimir lista de "
        "professores\n");
    printf(
        "9-imprimir lista de distribuicao de disciplina\n10-Inclusao de "
        "arquivo em lote\n");
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
                cadastrarCurso();
                break;
            case 2:
                cadastrarDisciplina();
                break;
            case 3:
                cadastrarProfessor();
                break;
            case 4:
                cadastrarDistDisc();
                break;
            case 5:
                removerDistDisc();
                break;
            case 6:
                imprimirListCurso();
                break;
            case 7:
                imprimirListDisc();
                break;
            case 8:
                imprimirListProf();
                break;
            case 9:
                imprimirDistDisc();
                break;
            case 10:
                carregarLote();
                break;
        }
        printar();
        printf("\nInforme o que deseja fazer:\n");
        scanf("%d%*c", &aux);
    }
}

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
                if (sscanf(linha, "C;%d;%99[^;]; %c", &aux.codCurso,
                           aux.nomeCurso, &aux.area) == 3) {
                    gravaCursos(&aux);
                }
            } else if (token == 'D') {
                Disciplinas aux;
                if (sscanf(linha, "D;%d;%99[^;];%d;%d", &aux.codDisc,
                           aux.nomeDisciplina, &aux.codCurso,
                           &aux.serie) == 4) {
                    gravaDisciplina(&aux);
                }
            } else if (token == 'P') {
                Professores aux;
                if (sscanf(linha, "P;%d;%99[^\n]", &aux.codProf,
                           aux.nomeProfessor) == 2) {
                    gravaProfessor(&aux);
                }
            } else if (token == 'M') {
                Materia aux;
                if (sscanf(linha, "M;%d;%d;%d", &aux.codDisciplina,
                           &aux.anoLetivo, &aux.codProf) == 3) {
                    gravaMateria(&aux);
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
    else return 0;
}

// Função para carregar informações de um arquivo em lote
// Pré-condição: Nenhuma
// Pós-condição: As informações do arquivo em lote são registradas na estrutura de dados
void carregarLote(){
    FILE *fr;
    char path[50];
    do{
        printf("Nome do arquivo:");
        scanf("%s%*c", path);
        fr = fopen(path, "r");
    }
    while(loadFile(fr));
    registroArqTXT(fr);
    printf("\n");
    fclose(fr);
}
