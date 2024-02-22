#include "disciplinas.h"

// Função para buscar o código do curso ao qual a disciplina pertence
// Pré-condição: 'aux' contém os dados da disciplina a ser consultada
// Pós-condição: O código do curso ao qual a disciplina pertence é impresso na saída padrão
void buscaCodigo(Disciplinas * aux){ //para função imprimir Disciplina 
    Cursos ax; 
    arqBin * arqCursos = abrirArquivo("arqCursos");
    int pos = arqCursos->cab.pos_cabeca;
    while(pos != -1){
        lerDados(&ax, pos, sizeof(Cursos), arqCursos);
        if(aux->codCurso == ax.codCurso){
            printf("A disciplina pertence ao curso %s (codigo %d)\n", ax.nomeCurso, ax.codCurso);
            break;
        }
        pos = ax.prox;
    }
    fclose(arqCursos->f);
}

// Função para gravar uma disciplina em um arquivo binário
// Pré-condição: 'aux' contém os dados da disciplina a ser gravada
// Pós-condição: Os dados da disciplina são gravados no arquivo binário
void gravaDisciplina(Disciplinas *aux){
    arqBin *arqDisc = abrirArquivo("arqDisc");
    aux->prox = arqDisc->cab.pos_cabeca;
    if (arqDisc->cab.pos_livre != -1)
    {
        Disciplinas ax;
        lerDados(&ax, arqDisc->cab.pos_livre, sizeof(Disciplinas), arqDisc);
        gravaDados(aux, arqDisc->cab.pos_topo, sizeof(Disciplinas), arqDisc);
        arqDisc->cab.pos_cabeca = arqDisc->cab.pos_livre;
        arqDisc->cab.pos_livre = aux->prox;
    }
    else
    {
        gravaDados(aux, arqDisc->cab.pos_topo, sizeof(Disciplinas), arqDisc);
        arqDisc->cab.pos_cabeca = arqDisc->cab.pos_topo;
        arqDisc->cab.pos_topo++;
    }
    escreveCabecalho(arqDisc);
    fclose(arqDisc->f);
}

// Função para cadastrar uma disciplina
// Pré-condição: Nenhuma
// Pós-condição: A disciplina é cadastrada e gravada no arquivo binário
void cadastrarDisciplina(){
    Disciplinas aux;
    printf("Informe o codigo da disciplina\n");
    scanf("%d%*c", &aux.codDisc);
    printf("Informe o nome da disciplina\n");
    scanf("%[^\n]%*c", aux.nomeDisciplina);
    printf("Informe o codigo do curso que a disciplina pertence\n");
    scanf("%d%*c", &aux.codCurso);
    printf("Informe o a serie que a disciplina pertence\n");
    scanf("%d%*c", &aux.serie);
    gravaDisciplina(&aux);
}

// Função para imprimir a lista de disciplinas
// Pré-condição: Nenhuma
// Pós-condição: A lista de disciplinas é impressa na saída padrão, incluindo o código do curso ao qual pertencem
void imprimirListDisc(){
    Disciplinas aux;
    arqBin *arqDisc = abrirArquivo("arqDisc");
    int pos = arqDisc->cab.pos_cabeca;
    while (pos != -1)
    {
        lerDados(&aux, pos, sizeof(Disciplinas), arqDisc);
        printf("O codigo da disciplina e %d\n", aux.codDisc);
        printf("O nome da disciplina e %s\n", aux.nomeDisciplina);
        buscaCodigo(&aux);
        printf("A série da disciplina e %d\n", aux.serie);
        pos = aux.prox;
        printf("\n");
    }
    fclose(arqDisc->f);
}
