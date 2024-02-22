#include "professores.h"

// Função auxiliar para imprimir a lista de professores
// Pré-condição: Nenhuma
// Pós-condição: A lista de professores é impressa na saída padrão
void imprimirAuxProf(int posAtual, arqB * arqProf, Professores aux){
    lerDados(&aux, posAtual, sizeof(Professores), arqProf);

    if(aux.proxEsq != -1) imprimirAuxProf(aux.proxEsq, arqProf, aux);

    printf("-> O codigo do professor e %s\n", aux.codProf);
    printf("-> O nome do professor e %s\n", aux.nomeProfessor);
    printf("\n");

    if(aux.proxDir != -1) imprimirAuxProf(aux.proxDir, arqProf, aux);
}

// Função para imprimir a lista de professores
// Pré-condição: Nenhuma
// Pós-condição: A lista de professores é impressa na saída padrão
void imprimirListProf(){
    Professores aux;
    arqB * arqProf = abrirArquivo("../arqProfessores");
    if(arqProf->cab.pos_cabeca == -1){
        printf("Não possui professores cadastrados\n");
    }
    else
        imprimirAuxProf(0, arqProf, aux);
    fclose(arqProf->f);
}

// Função para inserir um nó na árvore de professores
// Pré-condição: 'arqProf' é um ponteiro válido para a estrutura do arquivo de professores,
// 'pos_reg' é a posição do registro a ser inserido, 'pos_atual' é a posição atual na árvore, 'cod' é o código do professor a ser inserido
// Pós-condição: O nó é inserido na posição correta na árvore de professores
void insereNoArvProf(arqB *arqProf, int pos_reg, int pos_atual, char cod[]){
	Professores no_atual;
	lerDados(&no_atual, pos_atual, sizeof(Professores), arqProf);

    if(strcmp(no_atual.codP, cod) == 0) return;
	if(strcmp(no_atual.codP, cod) < 0){
    	if(no_atual.proxDir != -1){
        	insereNoArvProf(arqProf, pos_reg, no_atual.proxDir, cod);
    	}
    	else no_atual.proxDir = pos_reg;
	}
	else if(strcmp(no_atual.codP, cod) > 0){
    	if(no_atual.proxEsq != -1){
        	insereNoArvProf(arqProf, pos_reg, no_atual.proxEsq, cod);
    	}
    	else no_atual.proxEsq = pos_reg;
	}
	gravaDados(&no_atual, pos_atual, sizeof(Professores), arqProf);
}

// Função para gravar um professor em um arquivo binário
// Pré-condição: 'prof' contém os dados do professor a ser gravado
// Pós-condição: Os dados do professor são gravados no arquivo binário
void gravaProfessores(Professores *prof){
    arqB *arqProf = abrirArquivo("../arqProfessores");

    prof->proxDir = -1;
    prof->proxEsq = -1;

    if(strlen(prof->codProf) < 2){
        sprintf(prof->codP, "0%s", prof->codProf);
    }
    else{
        sprintf(prof->codP, "%s", prof->codProf);
    }

    gravaDados(prof, arqProf->cab.pos_topo, sizeof(Professores), arqProf);
    if(arqProf->cab.pos_cabeca == -1)arqProf->cab.pos_cabeca = 0;
    insereNoArvProf(arqProf, arqProf->cab.pos_topo, arqProf->cab.pos_cabeca, prof->codP);
    arqProf->cab.pos_topo++;

    escreveCabecalho(arqProf);
    fclose(arqProf->f);
}

// Função para cadastrar um professor
// Pré-condição: Nenhuma
// Pós-condição: O professor é cadastrado e gravado no arquivo binário
void cadastrarProfessores(){
    Professores prof;
    printf("Informe o codigo do professor\n");
    scanf("%[^\n]%*c", prof.codProf);
    printf("Informe o nome do professor\n");
    scanf("%[^\n]%*c", prof.nomeProfessor);
    gravaProfessores(&prof);
}

