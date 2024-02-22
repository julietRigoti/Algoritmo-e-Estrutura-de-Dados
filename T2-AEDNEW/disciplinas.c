#include "disciplinas.h"

// Função para buscar um curso na árvore de cursos
// Pré-condição: 'arqCursos' é um ponteiro válido para a estrutura do arquivo de cursos,
// 'aux' contém os dados do curso a ser buscado, 'pos_atual' é a posição inicial na árvore
// Pós-condição: Retorna a estrutura do curso encontrado ou uma estrutura de curso com valores vazios caso não seja encontrado
Cursos buscaCursos(arqB *arqCursos, Disciplinas aux, int pos_atual){
	Cursos curso;
	lerDados(&curso, pos_atual, sizeof(Cursos), arqCursos);
    if (pos_atual == -1) {
            return curso;
        }
	if (strcmp(curso.codCurso, aux.codCurso) == 0) {
		return curso;
	} else if (strcmp(curso.codCurso, aux.codCurso) < 0) {
		return buscaCursos(arqCursos, aux, curso.proxDir);
	} else {
		return buscaCursos(arqCursos, aux, curso.proxEsq);
	}
}

// Função auxiliar para imprimir a lista de Disciplinas
// Pré-condição: Nenhuma
// Pós-condição: A lista de Disciplinas é impressa na saída padrão
void imprimirAuxDisc(int posAtual, arqB * arqDisciplinas, arqB *arqCursos, Disciplinas aux){

    lerDados(&aux, posAtual, sizeof(Disciplinas), arqDisciplinas);
    if(aux.proxEsq != -1) imprimirAuxDisc(aux.proxEsq, arqDisciplinas, arqCursos, aux);

    printf("-> O codigo da disciplina e %s\n", aux.codDisc);
    printf("-> O nome da disciplina e %s\n", aux.nomeDisciplina);
    Cursos curso = buscaCursos(arqCursos, aux, arqCursos->cab.pos_cabeca);
    printf("-> A disciplina pertence ao curso %s (código %s)\n",curso.nomeCurso, aux.codCurso);
    printf("-> A serie da disciplina e %s\n", aux.serie);
    printf("\n");

    if(aux.proxDir != -1) imprimirAuxDisc(aux.proxDir, arqDisciplinas, arqCursos, aux);
}

// Função para imprimir a lista de Disciplinas
// Pré-condição: Nenhuma
// Pós-condição: A lista de Disciplinas é impressa na saída padrão
void imprimirListDisc(){
    Disciplinas aux;
    arqB * arqDisciplinas = abrirArquivo("../arqDisciplinas");
    arqB * arqCursos = abrirArquivo("../arqCursos");

    if(arqDisciplinas->cab.pos_cabeca == -1){
        printf("Não possui Disciplinas cadastrados\n");
    }
    else imprimirAuxDisc(0, arqDisciplinas, arqCursos, aux);

    fclose(arqDisciplinas->f);
    fclose(arqCursos->f);
}

// Função para inserir um nó na árvore de disciplinas
// Pré-condição: 'arqDisciplinas' é um ponteiro válido para a estrutura do arquivo de disciplinas,
// 'pos_reg' é a posição do registro a ser inserido, 'pos_atual' é a posição atual na árvore, 'cod' é o código da disciplina a ser inserida
// Pós-condição: O nó é inserido na posição correta na árvore de disciplinas
void insereNoArvDisc(arqB *arqDisciplinas, int pos_reg, int pos_atual, char cod[]){
	Disciplinas no_atual;
	lerDados(&no_atual, pos_atual, sizeof(Disciplinas), arqDisciplinas);

	if(strcmp(no_atual.codD, cod) == 0) {
	 // printf("strcmp(%s, %s) = %d\n", no_atual.codD, cod, strcmp(no_atual.codD, cod));
        return;
	}
	if(strcmp(no_atual.codD, cod) < 0){
	//printf("Dir strcmp(%s, %s) = %d\n", no_atual.codD, cod,strcmp(no_atual.codD, cod));
    	if(no_atual.proxDir != -1){
        	insereNoArvDisc(arqDisciplinas, pos_reg, no_atual.proxDir, cod);
    	}
    	else no_atual.proxDir = pos_reg;
	}
	else if(strcmp(no_atual.codD,cod) > 0){
	//printf("Esq strcmp(%s, %s) = %d\n", no_atual.codD, cod,strcmp(no_atual.codD, cod));
	if(no_atual.proxEsq != -1){
        	insereNoArvDisc(arqDisciplinas, pos_reg, no_atual.proxEsq, cod);
    	}
    	else no_atual.proxEsq = pos_reg;
	}
	gravaDados(&no_atual, pos_atual, sizeof(Disciplinas), arqDisciplinas);
}

// Função para gravar uma disciplina em um arquivo binário
// Pré-condição: 'aux' contém os dados da disciplina a ser gravada
// Pós-condição: Os dados da disciplina são gravados no arquivo binário
void gravaDisciplinas(Disciplinas *aux){
    arqB *arqDisciplinas = abrirArquivo("../arqDisciplinas");

    aux->proxDir = -1;
    aux->proxEsq = -1;

    if(strlen(aux->codDisc) < 2){
        sprintf(aux->codD, "0%s", aux->codDisc);
    }
    else{
        sprintf(aux->codD, "%s", aux->codDisc);
    }

    gravaDados(aux, arqDisciplinas->cab.pos_topo, sizeof(Disciplinas), arqDisciplinas);
    if(arqDisciplinas->cab.pos_cabeca == -1) arqDisciplinas->cab.pos_cabeca = 0;
    insereNoArvDisc(arqDisciplinas, arqDisciplinas->cab.pos_topo, arqDisciplinas->cab.pos_cabeca, aux->codD);
    arqDisciplinas->cab.pos_topo++;

    escreveCabecalho(arqDisciplinas);
    fclose(arqDisciplinas->f);
}

// Função para cadastrar uma disciplina
// Pré-condição: Nenhuma
// Pós-condição: A disciplina é cadastrada e gravada no arquivo binário
void cadastrarDisciplinas(){
    Disciplinas aux;
    printf("Informe o codigo da disciplina\n");
    scanf("%[^\n]%*c", aux.codDisc);
    printf("Informe o nome da disciplina\n");
    scanf("%[^\n]%*c", aux.nomeDisciplina);
    printf("Informe o codigo do curso que a disciplina pertence\n");
    scanf("%[^\n]%*c", aux.codCurso);
    printf("Informe o a serie que a disciplina pertence\n");
    scanf("%[^\n]%*c", aux.serie);
    gravaDisciplinas(&aux);
}
