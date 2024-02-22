#include "cursos.h"

// Função para buscar um curso em um arquivo binário
// Pré-condição: 'aux' contém os dados do curso a ser procurado, 'arqCursos' é um arquivo binário aberto para leitura
// Pós-condição: Retorna 1 se o curso foi encontrado, 0 caso contrário
int buscaCursos(Cursos * aux, arqBin *arqCursos){
    Cursos ax;
    int pos = arqCursos->cab.pos_cabeca;
    while(pos != -1){
        lerDados(&ax, pos, sizeof(Cursos), arqCursos);
        if(aux->codCurso == ax.codCurso) {
            return 1;
        }
    }
    return 0;
}

// Função para gravar um curso em um arquivo binário
// Pré-condição: 'aux' contém os dados do curso a ser gravado
// Pós-condição: Os dados do curso são gravados no arquivo binário
void gravaCursos(Cursos *aux){
    arqBin *arqCursos = abrirArquivo("arqCursos");

    aux->prox = arqCursos->cab.pos_cabeca;

    if(buscaCursos(aux, arqCursos)){
        printf("Curso já cadastrado\n");
        fclose(arqCursos->f);
        return;
    }
    if (arqCursos->cab.pos_livre != -1)
    {
        Cursos ax;
        lerDados(&ax, arqCursos->cab.pos_livre, sizeof(Cursos), arqCursos);
        gravaDados(aux, arqCursos->cab.pos_topo, sizeof(Cursos), arqCursos);//arrumar 
        arqCursos->cab.pos_cabeca = arqCursos->cab.pos_livre;
        arqCursos->cab.pos_livre = aux->prox;
    }
    else
    {
        gravaDados(aux, arqCursos->cab.pos_topo, sizeof(Cursos), arqCursos);
        arqCursos->cab.pos_cabeca = arqCursos->cab.pos_topo;
        arqCursos->cab.pos_topo++;
    }
    escreveCabecalho(arqCursos);    
    fclose(arqCursos->f);
}

// Função para cadastrar um curso
// Pré-condição: Nenhuma
// Pós-condição: O curso é cadastrado e gravado no arquivo binário
void cadastrarCurso(){
    Cursos cr;
    printf("Informe o codigo do curso de graduação: \n");
    scanf("%d%*c", &cr.codCurso);
    printf("Informe o nome do curso:\n");
    scanf("%[^\n]%*c", cr.nomeCurso);
    printf("Informe a area do curso:E para Exatas, H para Humanas, B para Biológicas\n");
    scanf("%c%*c", &cr.area);

    gravaCursos(&cr);
}

// Função para imprimir a lista de cursos
// Pré-condição: Nenhuma
// Pós-condição: A lista de cursos é impressa na saída padrão
void imprimirListCurso(){
    Cursos aux;
    arqBin * arqCursos = abrirArquivo("arqCursos");
    int pos = arqCursos->cab.pos_cabeca;
    while (pos != -1)
    {
        lerDados(&aux, pos, sizeof(Cursos), arqCursos);
        printf("O codigo do curso e %d\n", aux.codCurso);
        printf("O nome do curso e %s\n", aux.nomeCurso);
        printf("A area e %c\n", aux.area);
        pos = aux.prox;
        printf("\n");
    }
    fclose(arqCursos->f);
   
}
