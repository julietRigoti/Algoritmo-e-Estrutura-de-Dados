#include "distribuicoes.h"

// Função para buscar um professor na árvore de professores
// Pré-condição: 'arqProf' é um ponteiro válido para a estrutura do arquivo de professores,
// 'aux' contém os dados do professor a ser buscado, 'posAtual' é a posição inicial na árvore
// Pós-condição: Retorna a estrutura do professor encontrado ou uma estrutura de professor com valores vazios caso não seja encontrado
Professores buscaProfessor(arqB * arqProf, Distribuicao aux, int posAtual){
    Professores prof;
    lerDados(&prof, posAtual, sizeof(Professores), arqProf);
    if (posAtual == -1){
        return prof;
    }
    if (strcmp(prof.codProf,aux.codProf) == 0){
        return prof;
    }
    else if (strcmp(prof.codProf, aux.codProf) < 0){
        return buscaProfessor(arqProf, aux, prof.proxDir);
    }
    else{
        return buscaProfessor(arqProf, aux, prof.proxEsq);
    }
}

// Função para buscar uma disciplina na árvore de disciplinas
// Pré-condição: 'arqDisc' é um ponteiro válido para a estrutura do arquivo de disciplinas,
// 'aux' contém os dados da disciplina a ser buscada, 'posAtual' é a posição inicial na árvore
// Pós-condição: Retorna a estrutura da disciplina encontrada ou uma estrutura de disciplina com valores vazios caso não seja encontrado
Disciplinas buscaDisciplina(arqB * arqDisc, Distribuicao aux, int posAtual){
    Disciplinas disc;
    lerDados(&disc, posAtual, sizeof(Disciplinas), arqDisc);
    if (posAtual == -1){
        return disc;
    }
    if (strcmp(disc.codDisc, aux.codDisciplina) == 0){
        return disc;
    }
    else if (strcmp(disc.codDisc, aux.codDisciplina) < 0){
        return buscaDisciplina(arqDisc, aux, disc.proxDir);
    }
    else{
        return buscaDisciplina(arqDisc, aux, disc.proxEsq);
    }
}

// Função para buscar uma distribuição na árvore de distribuições
// Pré-condição: 'arqDist' é um ponteiro válido para a estrutura do arquivo de distribuições,
// 'auxAnoCod' é o código do ano a ser buscado, 'posAtual' é a posição inicial na árvore
// Pós-condição: Retorna a estrutura da distribuição encontrada ou uma estrutura de distribuição com valores vazios caso não seja encontrado
Distribuicao buscaDistribuicao(arqB * arqDist, char auxAnoCod[], int posAtual){
    Distribuicao dist;

    if(posAtual == -1) return dist;

    lerDados(&dist, posAtual, sizeof(Distribuicao), arqDist);

    if(strcmp(dist.AnoCod, auxAnoCod) == 0){
        return dist;
    }
    else if(strcmp(dist.AnoCod, auxAnoCod) < 0){
        return buscaDistribuicao(arqDist, auxAnoCod, dist.proxDir);
    }
    else {
        return buscaDistribuicao(arqDist, auxAnoCod, dist.proxEsq);
    }
}

// Função auxiliar para imprimir a lista de Distribuicao
// Pré-condição: Nenhuma
// Pós-condição: A lista de Distribuicao é impressa na saída padrão
void imprimirAuxDist(int posAtual, arqB * arqDist, arqB * arqProf, arqB * arqDisc, Distribuicao aux){

    if(posAtual == -1) return;

    lerDados(&aux, posAtual, sizeof(Distribuicao), arqDist);

    if(aux.proxEsq != -1) imprimirAuxDist(aux.proxEsq, arqDist, arqProf, arqDisc, aux);
    Disciplinas disc = buscaDisciplina(arqDisc, aux, arqDisc->cab.pos_cabeca);
    printf("-> A disciplina %s (codigo %s)\n", disc.nomeDisciplina, aux.codDisciplina);
    printf("-> O ano letivo eh %s\n", aux.anoLetivo);
    Professores prof = buscaProfessor(arqProf, aux, arqProf->cab.pos_cabeca);
    printf("-> O ódigo do professor que ministra a disciplina e %s (%s)\n", aux.codProf, prof.nomeProfessor);
    printf("-> Esq %d e Dir %d\n",aux.proxEsq, aux.proxDir);
    printf("\n");

    if(aux.proxDir != -1) imprimirAuxDist(aux.proxDir, arqDist, arqProf, arqDisc, aux);
}

// Função para imprimir a lista de Distribuicao
// Pré-condição: Nenhuma
// Pós-condição: A lista de Distribuicao é impressa na saída padrão
void imprimirListDist(){
    Distribuicao aux;
    arqB * arqDist = abrirArquivo("../arqDistribuicao");
    arqB * arqProf = abrirArquivo("../arqProfessores");
    arqB * arqDisc = abrirArquivo("../arqDisciplinas");
     printf("%d  %d  %d\n", arqDist->cab.pos_cabeca, arqDist->cab.pos_topo, arqDist->cab.pos_livre);
     printf("%d  %d  %d\n", arqProf->cab.pos_cabeca, arqProf->cab.pos_topo, arqProf->cab.pos_livre);
     printf("%d  %d  %d\n", arqDisc->cab.pos_cabeca, arqDisc->cab.pos_topo, arqDisc->cab.pos_livre);

    if(arqDist->cab.pos_cabeca == -1){
        printf("Não possui Distribuiçäo cadastradas\n");
    }
    else{
        imprimirAuxDist(0, arqDist, arqProf, arqDisc, aux);
    }

    fclose(arqDist->f);
    fclose(arqDisc->f);
    fclose(arqProf->f);
}

//Imprime posicoes de registros livres
//Pre-condicao: nós livres removidos
//Pos-condicao: impressão dos registros livres
void imprimelivre(){
    arqB* arqDistribuicao = abrirArquivo("../arqDistribuicao");
    int pos = arqDistribuicao->cab.pos_livre;
    if(pos == -1){
        printf("Nao existe nos livre\n");
        return;
    }
    Distribuicao aux, aux1;
    lerDados(&aux, pos, sizeof(Distribuicao),arqDistribuicao);
    printf("nos livres: ");
    while(pos != -1){
        printf("%s ",aux.AnoCod);
        pos = aux.proxEsq;
        lerDados(&aux, pos, sizeof(Distribuicao),arqDistribuicao);
    }
    printf("-1\n");
    fclose(arqDistribuicao->f);
}

//Imprime as distribuicoes da arvore binária por nivel
//Pre-condicao:distribuição de disciplina cadastradas
//Pos-condicao: Impressao das distribuicoes por nivel
void imprimirpornivel (){

    arqB* arqDistribuicao = abrirArquivo("../arqDistribuicao");
    int pos = arqDistribuicao->cab.pos_cabeca;
    if(pos == -1) return;

    fila* f = cria_fila_vazia();
    Distribuicao aux, aux1 ;
    char cod[3*NUM + 1];

    lerDados(&aux, pos, sizeof(Distribuicao), arqDistribuicao);
    enqueue(f, aux.AnoCod);
    enqueue(f, "-1");

    while(!vazia(f)){
        printf("[%s] ", f->inicio->AnoCod);
        dequeue(f);

        if(aux.proxEsq != -1){
            lerDados(&aux1, aux.proxEsq, sizeof(Distribuicao), arqDistribuicao);
            enqueue(f, aux1.AnoCod);
        }
        if(aux.proxDir != -1){
            lerDados(&aux1, aux.proxDir, sizeof(Distribuicao), arqDistribuicao);
            enqueue(f, aux1.AnoCod);
        }
        if(strcmp(f->inicio->AnoCod, "-1") == 0){
            printf("\n");
            dequeue(f);
            enqueue(f, "-1");
        }
        if(strcmp(f->inicio->AnoCod, "-1") == 0 && f->inicio->prox == NULL){
            printf("\n\n");
            break;
        }
        cod[0] = '\0';
        sprintf(cod, "%s", f->inicio->AnoCod);
        aux = buscaDistribuicao(arqDistribuicao, cod, arqDistribuicao->cab.pos_cabeca);
    }
    fclose(arqDistribuicao->f);
}

// Função para inserir um nó na árvore de distribuições
// Pré-condição: 'arqDistribuicao' é um ponteiro válido para a estrutura do arquivo de distribuições,
// 'pos_reg' é a posição do registro a ser inserido, 'pos_atual' é a posição atual na árvore, 'cod' é o código do ano letivo a ser inserido
// Pós-condição: O nó é inserido na posição correta na árvore de distribuições
void insereNoArvDist(arqB *arqDistribuicao, int pos_reg, int pos_atual, char cod[]){
    Distribuicao no_atual;
    lerDados(&no_atual, pos_atual, sizeof(Distribuicao), arqDistribuicao);
    if(strcmp(no_atual.AnoCod, cod) == 0){
     return;
     }
    if(strcmp(no_atual.AnoCod, cod) < 0){
        if(no_atual.proxDir != -1){
            insereNoArvDist(arqDistribuicao, pos_reg, no_atual.proxDir, cod);
        }
        else no_atual.proxDir = pos_reg;
    }
    else if(strcmp(no_atual.AnoCod, cod) > 0){
        if(no_atual.proxEsq != -1){
            insereNoArvDist(arqDistribuicao, pos_reg, no_atual.proxEsq, cod);
        }
        else no_atual.proxEsq = pos_reg;
    }
    gravaDados(&no_atual, pos_atual, sizeof(Distribuicao), arqDistribuicao);
}

// Função para encontrar o nó com o maior valor (anoCod) na subárvore direita
// Pré-condição: 'arqDistribuicao' é um ponteiro válido para a estrutura do arquivo de distribuições,
// 'posAtual' é a posição inicial na árvore
// Pós-condição: Retorna a posição do nó com o maior valor na subárvore direita
int maiorMenor(arqB *arqDistribuicao, int posAtual){
    Distribuicao dist;
    lerDados(&dist, posAtual, sizeof(Distribuicao), arqDistribuicao);
    if(dist.proxDir == -1){
        return posAtual;
    }
    return maiorMenor(arqDistribuicao, dist.proxDir);
}

// Função para remover um nó da árvore de distribuições com base no ano letivo
// Pré-condição: 'posAtual' é a posição inicial na árvore, 'anoCod' é o ano letivo a ser removido, 'arqDistribuicao' é um ponteiro válido para a estrutura do arquivo de distribuições
// Pós-condição: Retorna a nova posição do nó ou -1 se o nó não for encontrado
int remocao(int posAtual, char* anoCod, arqB *arqDistribuicao){
    if(posAtual == -1) {
        return -1;
    }
    Distribuicao noAtual;
    lerDados(&noAtual, posAtual, sizeof(Distribuicao), arqDistribuicao);
    if(strcmp(noAtual.AnoCod, anoCod) < 0){
        noAtual.proxDir = remocao(noAtual.proxDir, anoCod,  arqDistribuicao);
        gravaDados(&noAtual, posAtual, sizeof(Distribuicao), arqDistribuicao);
    }
    else if(strcmp(noAtual.AnoCod, anoCod) > 0){
        noAtual.proxEsq = remocao(noAtual.proxEsq, anoCod,  arqDistribuicao);
        gravaDados(&noAtual, posAtual, sizeof(Distribuicao), arqDistribuicao);
    }
    else{
        if(noAtual.proxEsq == -1){ // NÓ FOLHA OU SÓ TEM FILHO A DIREITA
            noAtual.proxEsq = arqDistribuicao->cab.pos_livre;
            arqDistribuicao->cab.pos_livre = posAtual;
            gravaDados(&noAtual, posAtual, sizeof(Distribuicao), arqDistribuicao);
            escreveCabecalho(arqDistribuicao);
            return noAtual.proxDir;
        } else {  // TEM FILHO A ESQUERDA (SUBSTITUIÇÃO)
            // Chama a função para encontrar o sucessor
            int posNoMaior = maiorMenor(arqDistribuicao, noAtual.proxEsq);
            Distribuicao noMaior;
            lerDados(&noMaior, posNoMaior, sizeof(Distribuicao), arqDistribuicao);

            strcpy(noAtual.codDisciplina, noMaior.codDisciplina);
            strcpy(noAtual.anoLetivo, noMaior.anoLetivo);
            strcpy(noAtual.codProf, noMaior.codProf);
            strcpy(noAtual.AnoCod, noMaior.AnoCod);

            noAtual.proxEsq = remocao(noAtual.proxEsq, noMaior.AnoCod, arqDistribuicao);

            gravaDados(&noAtual, posAtual, sizeof(Distribuicao), arqDistribuicao);
            return posAtual;
        }
    }
    return posAtual;
}

// Função para remover uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é removida do arquivo
void removerDistDisc(Remocao aux){
    arqB *arqDistribuicao = abrirArquivo("../arqDistribuicao");

    if(arqDistribuicao->cab.pos_cabeca != -1){
        if (strlen(aux.cod) < 2){
            sprintf(aux.anoCod, "%s0%s", aux.ano, aux.cod);
        }else {
            sprintf(aux.anoCod, "%s%s", aux.ano, aux.cod);
        }
        int cab, cabNovo;
        cab = arqDistribuicao->cab.pos_cabeca;
        cabNovo = remocao(cab, aux.anoCod, arqDistribuicao);
        fclose(arqDistribuicao->f);
        arqB *arqDistribuicao = abrirArquivo("../arqDistribuicao");
        arqDistribuicao->cab.pos_cabeca = cabNovo;
        escreveCabecalho(arqDistribuicao);
    }
    else printf("Não possui distribuicoes de disciplinas\n");

    fclose(arqDistribuicao->f);
}

// Função para interagir com o usuário e solicitar informações para remoção de distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A função chama a função 'removerDistDisc' para efetuar a remoção
void retirarDistDisc(){

    Remocao aux;

    printf("Entre com o codigo da disciplina\n");
    scanf("%[^\n]%*c", aux.cod);
    printf("Entre com o ano letivo\n");
    scanf("%[^\n]%*c", aux.ano);
    removerDistDisc(aux);
}

// Função para gravar uma distribuição de disciplina em um arquivo binário
// Pré-condição: 'dist' contém os dados da distribuição de disciplina a ser gravada
// Pós-condição: Os dados da distribuição de disciplina são gravados no arquivo binário
void gravaDistribuicoes(Distribuicao *dist){

    arqB *arqDistribuicao = abrirArquivo("../arqDistribuicao");
    dist->proxDir = -1;
    dist->proxEsq = -1;

    if (strlen(dist->codDisciplina) < 2){
        sprintf(dist->AnoCod, "%s0%s", dist->anoLetivo, dist->codDisciplina);
    }
    else{
        sprintf(dist->AnoCod, "%s%s", dist->anoLetivo, dist->codDisciplina);
    }

    if(arqDistribuicao->cab.pos_livre == -1){
        gravaDados(dist, arqDistribuicao->cab.pos_topo, sizeof(Distribuicao), arqDistribuicao);
        if(arqDistribuicao->cab.pos_cabeca == -1) arqDistribuicao->cab.pos_cabeca = 0;
        insereNoArvDist(arqDistribuicao, arqDistribuicao->cab.pos_topo, arqDistribuicao->cab.pos_cabeca, dist->AnoCod);
        arqDistribuicao->cab.pos_topo++;
    }
    else {
        gravaDados(dist, arqDistribuicao->cab.pos_livre, sizeof(Distribuicao), arqDistribuicao); //isso é possivel porque na remoção a gente indica o livre
        insereNoArvDist(arqDistribuicao, arqDistribuicao->cab.pos_livre, arqDistribuicao->cab.pos_cabeca, dist->AnoCod);
        arqDistribuicao->cab.pos_livre = dist->proxEsq;
    }
    escreveCabecalho(arqDistribuicao);
    fclose(arqDistribuicao->f);
}

// Função para cadastrar uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é cadastrada e gravada no arquivo binário
void cadastrarDistDisc(){
    Distribuicao dist;
    printf("Informe o código da disciplina\n");
    scanf("%[^\n]%*c", dist.codDisciplina);
    printf("Informe o ano letivo\n");
    scanf("%[^\n]%*c", dist.anoLetivo);
    printf("informe o codigo do professor que ministra a disciplina\n");
    scanf("%[^\n]%*c", dist.codProf);

    gravaDistribuicoes(&dist);
}
