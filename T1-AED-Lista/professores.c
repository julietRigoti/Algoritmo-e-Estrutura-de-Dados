#include "professores.h"

// Função para imprimir a lista de professores
// Pré-condição: Nenhuma
// Pós-condição: A lista de professores é impressa na saída padrão
void imprimirListProf(){
    Professores aux;
    arqBin *arqProf = abrirArquivo("arqProf");
    int pos = arqProf->cab.pos_cabeca;
    while (pos != -1)
    {
        lerDados(&aux, pos, sizeof(Professores), arqProf);
        printf("O codigo do professor e %d\n", aux.codProf);
        printf("O nome do professor e %s\n", aux.nomeProfessor);
        pos = aux.prox;
        printf("\n");
    }
   fclose(arqProf->f);
}

// Função para buscar um professor em um arquivo binário
// Pré-condição: 'aux' contém os dados do professor a ser procurado, 'arqProf' é um arquivo binário aberto para leitura
// Pós-condição: Retorna 1 se o professor foi encontrado, 0 caso contrário
int buscaProf(Professores * aux, arqBin *arqProf){
    Professores ax;
    int pos = arqProf->cab.pos_cabeca;
    while(pos != -1){
        lerDados(&ax, pos, sizeof(Professores), arqProf);
        if(aux->codProf == ax.codProf) {
            return 1;
        }
    }
    return 0;
}

// Função para gravar um professor em um arquivo binário
// Pré-condição: 'prof' contém os dados do professor a ser gravado
// Pós-condição: Os dados do professor são gravados no arquivo binário
void gravaProfessor(Professores *prof){
    arqBin *arqProf = abrirArquivo("arqProf");
    prof->prox = arqProf->cab.pos_cabeca;

    if(buscaProf(prof, arqProf)){
        printf("Professor já cadastrado\n");
        fclose(arqProf->f);
        return;
    }
    if (arqProf->cab.pos_livre != -1)
    {
        Professores aux;
        lerDados(&aux, arqProf->cab.pos_livre, sizeof(Professores), arqProf);
        gravaDados(prof, arqProf->cab.pos_topo, sizeof(Professores), arqProf);
        arqProf->cab.pos_cabeca = arqProf->cab.pos_livre;
        arqProf->cab.pos_livre = aux.prox;
    }
    else
    {
        gravaDados(prof, arqProf->cab.pos_topo, sizeof(Professores), arqProf);
        arqProf->cab.pos_cabeca = arqProf->cab.pos_topo;
        arqProf->cab.pos_topo++;
    }
    escreveCabecalho(arqProf);
    fclose(arqProf->f);
}

// Função para cadastrar um professor
// Pré-condição: Nenhuma
// Pós-condição: O professor é cadastrado e gravado no arquivo binário
void cadastrarProfessor(){
    Professores prof;
    printf("Informe o codigo do professor\n");
    scanf("%d%*c", &prof.codProf);
    printf("Informe o nome do professor\n");
    scanf("%[^\n]%*c", prof.nomeProfessor);
    gravaProfessor(&prof);
}
