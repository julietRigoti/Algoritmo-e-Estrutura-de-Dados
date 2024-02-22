#include "cursos.h"

// Função auxiliar para imprimir a lista de cursos
// Pré-condição: Nenhuma
// Pós-condição: A lista de cursos é impressa na saída padrão
void imprimirAuxCurso(int posAtual, arqB * arqCursos, Cursos aux){
    lerDados(&aux, posAtual, sizeof(Cursos), arqCursos);
    if(aux.proxEsq != -1) imprimirAuxCurso(aux.proxEsq, arqCursos, aux);

    printf("-> O codigo do curso e %s\n", aux.codCurso);
    printf("-> O nome do curso e %s\n", aux.nomeCurso);
    printf("-> A area e %c\n", aux.area);
    printf("\n");

    if(aux.proxDir != -1) imprimirAuxCurso(aux.proxDir, arqCursos, aux);
}

// Função para imprimir a lista de cursos
// Pré-condição: Nenhuma
// Pós-condição: A lista de cursos é impressa na saída padrão
void imprimirListCursos(){
    Cursos aux;
    arqB * arqCursos = abrirArquivo("../arqCursos");
    if(arqCursos->cab.pos_cabeca == -1){
        printf("Não possui cursos cadastrados\n");
    }
    else
        imprimirAuxCurso(0, arqCursos, aux);

    fclose(arqCursos->f);
}

// Função para inserir um nó na árvore de cursos
// Pré-condição: 'arqCursos' é um ponteiro válido para a estrutura do arquivo de cursos,
// 'pos_reg' é a posição do registro a ser inserido, 'pos_atual' é a posição atual na árvore, 'cod' é o código do curso a ser inserido
// Pós-condição: O nó é inserido na posição correta na árvore de cursos
void insereNoArvCurso(arqB *arqCursos, int pos_reg, int pos_atual, char cod[]){
    Cursos no_atual;
    lerDados(&no_atual, pos_atual, sizeof(Cursos), arqCursos);

    if(strcmp(no_atual.codC, cod) == 0) return;
    if(strcmp(no_atual.codC, cod) < 0){
        if(no_atual.proxDir != -1){
            insereNoArvCurso(arqCursos, pos_reg, no_atual.proxDir, cod);
        }
        else no_atual.proxDir = pos_reg;
    }
    else if(strcmp(no_atual.codC, cod) > 0){
        if(no_atual.proxEsq != -1){
            insereNoArvCurso(arqCursos, pos_reg, no_atual.proxEsq, cod);
        }
        else no_atual.proxEsq = pos_reg;
    }
    gravaDados(&no_atual, pos_atual, sizeof(Cursos), arqCursos);
}

// Função para gravar um curso em um arquivo binário
// Pré-condição: 'aux' contém os dados do curso a ser gravado
// Pós-condição: Os dados do curso são gravados no arquivo binário
void gravaCursos(Cursos *aux){
    arqB *arqCursos = abrirArquivo("../arqCursos");

    aux->proxEsq = -1;
    aux->proxDir = -1;

    if(strlen(aux->codCurso) < 2){
        sprintf(aux->codC, "0%s", aux->codCurso);
    }
    else{
        sprintf(aux->codC, "%s", aux->codCurso);
    }

    gravaDados(aux, arqCursos->cab.pos_topo, sizeof(Cursos), arqCursos);
    if(arqCursos->cab.pos_cabeca == -1)arqCursos->cab.pos_cabeca = 0;
    insereNoArvCurso(arqCursos, arqCursos->cab.pos_topo, arqCursos->cab.pos_cabeca, aux->codC);
    arqCursos->cab.pos_topo++;

    escreveCabecalho(arqCursos);
    fclose(arqCursos->f);
}

// Função para cadastrar um curso
// Pré-condição: Nenhuma
// Pós-condição: O curso é cadastrado e gravado no arquivo binário
void cadastrarCursos(){
    Cursos cr;
    printf("Informe o codigo do curso de graduacao: \n");
    scanf("%[^\n]%*c", cr.codCurso);
    printf("Informe o nome do curso:\n");
    scanf("%[^\n]%*c", cr.nomeCurso);
    printf("Informe a area do curso:E para Exatas, H para Humanas, B para Biologicas\n");
    scanf("%c%*c", &cr.area);

    gravaCursos(&cr);
}
