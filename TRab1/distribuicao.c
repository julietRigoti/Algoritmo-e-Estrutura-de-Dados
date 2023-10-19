#include "distribuicao.h"

// Função para remover uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é removida do arquivo
void removerDistDisc() {
    int cod, ano;
    printf("Entre com o codigo da disciplina\n");
    scanf("%d", &cod);
    printf("Entre com o ano letivo\n");
    scanf("%d%*c", &ano);

    arqBin *arqCadastro = abrirArquivo("arqCadastro");
    Materia aux;

    int posAtual = arqCadastro->cab.pos_cabeca;
    int posAnt = -1;

    while (posAtual != -1) {
        lerDados(&aux, posAtual, sizeof(Materia), arqCadastro);
        if (aux.codDisciplina == cod && aux.anoLetivo == ano) {
            break;
        }
        posAnt = posAtual;
        posAtual = aux.prox;

    }

    if (posAtual != -1) {
        if (posAnt == -1) {
            arqCadastro->cab.pos_cabeca = aux.prox;
        } else {
            Materia ax;
            lerDados(&ax, posAnt, sizeof(Materia), arqCadastro);
            ax.prox = aux.prox;
            gravaDados(&ax, posAnt, sizeof(Materia), arqCadastro);
        }

        aux.prox = arqCadastro->cab.pos_livre;
        arqCadastro->cab.pos_livre = posAtual;
        gravaDados(&aux, posAtual, sizeof(Materia), arqCadastro);
        escreveCabecalho(arqCadastro);
    }

    fclose(arqCadastro->f);
}

// Função para buscar informações sobre a disciplina e o professor
// Pré-condição: 'aux' contém os dados da distribuição de disciplina
// Pós-condição: As informações sobre a disciplina e o professor são impressas na saída padrão
void buscaDisciplina(Materia *aux){
    Disciplinas dx;
    Professores px;
    arqBin *arqDisc = abrirArquivo("arqDisc");
    arqBin *arqProf = abrirArquivo("arqProf");

    int pos = arqDisc->cab.pos_cabeca;
    int ps = arqProf->cab.pos_cabeca;

    while (pos != -1)
    {
        lerDados(&dx, pos, sizeof(Disciplinas), arqDisc);
        if (aux->codDisciplina == dx.codDisc)
        {
            printf("\nA disciplina e %s (codigo %d)\n", dx.nomeDisciplina, aux->codDisciplina);
        }
        pos = dx.prox;
    }
    printf("o ano letivo e %d\n", aux->anoLetivo);
    while (ps != -1)
    {
        lerDados(&px, ps, sizeof(Professores), arqProf);
        if (aux->codProf == px.codProf)
        {
            printf("o código do professor que ministra a disciplina e %d (%s)", aux->codProf, px.nomeProfessor);
        }
        ps = px.prox;
    }
    fclose(arqDisc->f);
    fclose(arqProf->f);
}
// Função para imprimir a lista de distribuição de disciplinas
// Pré-condição: Nenhuma
// Pós-condição: A lista de distribuição de disciplinas é impressa na saída padrão
void imprimirDistDisc()
{
    Materia aux;
    arqBin *arqCadastro = abrirArquivo("arqCadastro");
    int pos = arqCadastro->cab.pos_cabeca;
    while (pos != -1)
    {
        lerDados(&aux, pos, sizeof(Materia), arqCadastro);
        buscaDisciplina(&aux);
        printf("\n");
        pos = aux.prox;
    }
    fclose(arqCadastro->f);
}
// Função para buscar uma distribuição de disciplina em um arquivo binário
// Pré-condição: 'dist' contém os dados da distribuição de disciplina a ser buscada, 'arqCadastro' é um arquivo binário aberto para leitura
// Pós-condição: Retorna 1 se a distribuição de disciplina foi encontrada, 0 caso contrário
int buscaDist(Materia *dist, arqBin *arqCadastro)
{ // para função cadastrar Distribuição Disciplina
    Materia aux;
    int pos = arqCadastro->cab.pos_cabeca;
    while (pos != -1)
    {
        lerDados(&aux, pos, sizeof(Materia), arqCadastro);
        if (dist->codDisciplina == aux.codDisciplina && dist->anoLetivo == aux.anoLetivo){
            return 1;
        }
        pos = aux.prox;
    }
    return 0;
}
// Função para gravar uma distribuição de disciplina em um arquivo binário
// Pré-condição: 'dist' contém os dados da distribuição de disciplina a ser gravada
// Pós-condição: Os dados da distribuição de disciplina são gravados no arquivo binário
void gravaMateria(Materia *dist)
{
    arqBin *arqCadastro = abrirArquivo("arqCadastro");
    dist->prox = arqCadastro->cab.pos_cabeca;

    if (buscaDist(dist, arqCadastro))
    {
        printf("Materia já ministrada\n");
        fclose(arqCadastro->f); 
        return;
    }
    if (arqCadastro->cab.pos_livre != -1)
    {
        Materia aux;
        lerDados(&aux, arqCadastro->cab.pos_livre, sizeof(Materia), arqCadastro);
        gravaDados(dist, arqCadastro->cab.pos_topo, sizeof(Materia), arqCadastro);
        arqCadastro->cab.pos_cabeca = arqCadastro->cab.pos_topo;
        arqCadastro->cab.pos_livre = aux.prox;
    }
    else
    {
        gravaDados(dist, arqCadastro->cab.pos_topo, sizeof(Materia), arqCadastro);
        arqCadastro->cab.pos_cabeca = arqCadastro->cab.pos_topo;
        arqCadastro->cab.pos_topo++;
    }
    escreveCabecalho(arqCadastro);
    fclose(arqCadastro->f);
}
// Função para cadastrar uma distribuição de disciplina
// Pré-condição: Nenhuma
// Pós-condição: A distribuição de disciplina é cadastrada e gravada no arquivo binário
void cadastrarDistDisc()
{
    Materia dist;
    printf("Informe o código da disciplina\n");
    scanf("%d%*c", &dist.codDisciplina);
    printf("Informe o ano letivo\n");
    scanf("%d%*c", &dist.anoLetivo);
    printf("informe o codigo do professor que ministra a disciplina\n");
    scanf("%d%*c", &dist.codProf);
    gravaMateria(&dist);
}
