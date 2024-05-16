#include "arvore.h"

//FUNÇÕES AUXILIARES

// Pré-condição: 'aux' deve ser um ponteiro válido para uma estrutura de árvore B.
// Pós-condição: A página referenciada por 'aux' é inicializada para uso.
void inicializaPagina(arvoreB *aux){
    int i;
    for(i = 0; i < ORDEM; i++){
        aux->chaves[i] = -1;
        aux->ptDados[i] = -1;
        aux->filhos[i] = -1;
    }
    aux->filhos[i] = -1;
    aux->numChaves = 0;
}

// Descrição: Verifica se uma página da árvore B é uma folha.
// Pré-condição: 'B' é a página da árvore B a ser verificada.
// Pós-condição: Retorna 1 se a página for uma folha, caso contrário retorna 0.
int ehFolha(arvoreB B){
    return (B.filhos[0] == -1);
}

// Descrição: Verifica se há overflow em uma página da árvore B.
// Pré-condição: 'numChaves' é o número de chaves na página da árvore B.
// Pós-condição: Retorna 1 se houver overflow, caso contrário retorna 0.
int overflow(int numChaves){
    return (numChaves == ORDEM);
}

// Descrição: Verifica se há underflow em uma página da árvore B.
// Pré-condição: 'numChaves' é o número de chaves na página da árvore B.
// Pós-condição: Retorna 1 se houver underflow, caso contrário retorna 0.
int underflow(int numChaves){
    return (numChaves < (ORDEM - 1)/2);
}

// Descrição: Busca recursivamente um código de usuário em um arquivo de índice.
// Pré-condição: 'codUsuario' deve ser o código de usuário a ser buscado.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'posArq' deve ser a posição atual no arquivo de índice.
//               'pos' deve ser um ponteiro válido para armazenar a posição encontrada.
// Pós-condição: Se o código de usuário for encontrado, 'pos' conterá a posição.
//               Caso contrário, 'pos' conterá -1.
int busca(int codUsuario, arquivoB* arqIndice, int posArq, int *pos){
    if(posArq == -1) return -1;

    arvoreB B;
    lerDados(&B, posArq, sizeof(arvoreB), arqIndice);

    int i = 0;
    while(i < B.numChaves && B.chaves[i] < codUsuario) i++;
    if((i+1) > B.numChaves || B.chaves[i] > codUsuario)
        return busca(codUsuario, arqIndice, B.filhos[i], pos);
    (*pos) = i;
    return posArq;
}

// Pré-condição: 'pos' deve ser um ponteiro válido para a posição de busca.
//               'codProd' deve ser o código do produto a ser buscado.
//               'arqDIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'i' é um índice usado na busca.
// Pós-condição: Retorna a posição onde as informações são encontradas.
int buscaInfo(int *aux, int codProd, arquivoB * arqIndice, int pos){
    if(pos == -1) return -1;

    arvoreB B;
    lerDados(&B, pos, sizeof(arvoreB), arqIndice);
        for ((*aux) = 0; (*aux) < B.numChaves; (*aux)++){
            if(codProd == B.chaves[(*aux)])
                return 1;
            else if(codProd < B.chaves[(*aux)])
                break; //codProd pode estar na subarvore filho
        }

    return 0;
}

//INSERÇÃO

// Descrição: Adiciona uma nova chave à direita na página da árvore B.
// Pré-condição: 'B' deve ser um ponteiro válido para a estrutura da árvore B.
//               'pos' é um ponteiro para a posição onde a chave será adicionada.
//               'codProd' é o código do produto a ser adicionado.
//               'k' é a posição dos dados associados à chave.
//               'novoFilho' é o novo filho a ser adicionado.
// Pós-condição: A nova chave é adicionada à direita na página da árvore B.
void adicionaDireita(arvoreB *B, int *pos, int codProd, int k, int novoFilho){
    int i;
    for(i = B->numChaves; i > (*pos); i--){
        B->chaves[i] = B->chaves[i-1];
        B->filhos[i+1] = B->filhos[i];
        B->ptDados[i] = B->ptDados[i-1];
    }
    B->chaves[(*pos)] = codProd;
    B->ptDados[(*pos)] = k;
    B->filhos[(*pos)+1] = novoFilho;
    B->numChaves++;
}

// Descrição: Realiza a operação de split em uma página da árvore B.
// Pré-condição: 'aux' deve ser um ponteiro válido para a estrutura da árvore B.
//               'm' é um ponteiro para armazenar a chave mediana após o split.
//               'ptDado' é um ponteiro para armazenar a posição de dados associada à chave mediana.
// Pós-condição: A operação de split é realizada na página da árvore B e uma nova página é criada.
arvoreB split(arvoreB *aux, int *m, int *ptDado){
    arvoreB C;
    inicializaPagina(&C);

    int q = aux->numChaves/2; // 5/2 = 2
    C.numChaves = aux->numChaves - q - 1; //5 - 2 - 1 = 2
    aux->numChaves = q;
    *m = aux->chaves[q]; //chave mediana
    *ptDado = aux->ptDados[q];
    C.filhos[0] = aux->filhos[q+1];

    for(int i = 0; i < C.numChaves; i++){
        C.chaves[i] = aux->chaves[q+i+1];
        C.ptDados[i] = aux->ptDados[q+i+1];
        C.filhos[i+1] = aux->filhos[q+i+2];
    }
    return C;
}

// Descrição: Insere uma nova chave na árvore B.
// Pré-condição: 'codProd' é o código do produto a ser inserido.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'ptDado' é a posição de dados associada à chave.
//               'indicePos' é a posição da página da árvore B no arquivo de índice.
// Pós-condição: Uma nova chave é inserida na árvore B.
void insereArqIndexAux(int codProd, arquivoB *arqIndice, int ptDado, int indicePos){
    //lembrando que esse *pos é a posição no vetor de chaves
    //k é linha do arquivo de dados
    arvoreB raiz, raizAux;
    lerDados(&raiz, indicePos, sizeof(arvoreB), arqIndice);
    int aux = 0;
        //preciso de uma variavel para saber a posição da chave no vetor de chaves no arquivo
    if(!buscaInfo(&aux, codProd, arqIndice, indicePos)){
        if (ehFolha(raiz)){
           adicionaDireita(&raiz, &aux, codProd, ptDado, -1);
        } else {
            insereArqIndexAux(codProd, arqIndice, ptDado, raiz.filhos[aux]); //lembrar que tem que inserir na folha
            lerDados(&raizAux, raiz.filhos[aux], sizeof(arvoreB), arqIndice);
            if(overflow(raizAux.numChaves)){
                int chaveMed, ptDadoMed;
                 arvoreB t = split(&raizAux, &chaveMed, &ptDadoMed);
                 gravaDados(&raizAux, raiz.filhos[aux], sizeof(arvoreB), arqIndice);
                 if(arqIndice->cab.pos_livre == -1){
                    gravaDados(&t, arqIndice->cab.pos_topo++, sizeof(arvoreB), arqIndice);
                    adicionaDireita(&raiz, &aux, chaveMed, ptDadoMed, arqIndice->cab.pos_topo - 1);
                 } else { //verificar se está certo
                    arvoreB livre;
                    lerDados(&livre, arqIndice->cab.pos_livre, sizeof(arvoreB), arqIndice);
                    gravaDados(&t, arqIndice->cab.pos_livre, sizeof(arvoreB), arqIndice);
                    adicionaDireita(&raiz, &aux, chaveMed, ptDadoMed, arqIndice->cab.pos_livre);
                    arqIndice->cab.pos_livre = livre.chaves[0];
                 }

            }
        }
    }
    gravaDados(&raiz, indicePos, sizeof(arvoreB), arqIndice);
}

// Pré-condição: 'codProd' deve ser o código do produto a ser inserido.
//               'ptDado' deve ser a posição de dados associada ao código do produto.
//               'arqDados' deve ser um ponteiro válido para o arquivo de dados.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
// Pós-condição: O novo índice é inserido no arquivo de índice.
void insereArqIndex(int codProd, int ptDado, arquivoB * arqDados, arquivoB *arqIndice){
    arvoreB raiz;
    if (arqIndice->cab.pos_cabeca == -1){
        inicializaPagina(&raiz);
        raiz.numChaves = 1;
        raiz.chaves[0] = codProd;
        raiz.ptDados[0] = ptDado;
        if(arqIndice->cab.pos_livre == -1){
            arqIndice->cab.pos_cabeca = arqIndice->cab.pos_topo;
            arqIndice->cab.pos_topo++;
        } else {
            arvoreB livre;
            lerDados(&livre, arqIndice->cab.pos_livre, sizeof(arvoreB), arqIndice);
            arqIndice->cab.pos_cabeca = arqIndice->cab.pos_livre;
            arqIndice->cab.pos_livre = livre.chaves[0];
        }
        gravaDados(&raiz, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice); //minha raiz

    } else {
        insereArqIndexAux(codProd, arqIndice, ptDado, arqIndice->cab.pos_cabeca);

        lerDados(&raiz, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
        if(overflow(raiz.numChaves)){ //verifica se o nó está cheio
            int chaveMed, ptDado;
            arvoreB aux, novaRaiz;
            inicializaPagina(&aux);
            inicializaPagina(&novaRaiz);
            aux = split(&raiz, &chaveMed, &ptDado);
            novaRaiz.chaves[0] = chaveMed;
            novaRaiz.ptDados[0] = ptDado;
            novaRaiz.filhos[0] = arqIndice->cab.pos_cabeca;
            novaRaiz.numChaves = 1;
            gravaDados(&raiz, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);

            if(arqIndice->cab.pos_livre == -1){
                novaRaiz.filhos[1] = arqIndice->cab.pos_topo;
                gravaDados(&aux, arqIndice->cab.pos_topo++, sizeof(arvoreB), arqIndice);
                arqIndice->cab.pos_cabeca = arqIndice->cab.pos_topo++;
                gravaDados(&novaRaiz, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
            }
            else { //verificar se está certo
                arvoreB livre;
                lerDados(&livre, arqIndice->cab.pos_livre, sizeof(arvoreB), arqIndice);
                novaRaiz.filhos[1] = arqIndice->cab.pos_livre;
                gravaDados(&aux, arqIndice->cab.pos_livre, sizeof(arvoreB), arqIndice);
                arqIndice->cab.pos_livre = livre.filhos[0];
                arqIndice->cab.pos_cabeca = arqIndice->cab.pos_livre;
                gravaDados(&novaRaiz, arqIndice->cab.pos_cabeca, sizeof(arvoreB), arqIndice);
            }
        }
    }
    escreveCabecalho(arqIndice);
}

//REMOÇÃO

// Descrição: Remove uma chave à esquerda na árvore B.
// Pré-condição: 'B' deve ser um ponteiro válido para a estrutura da árvore B.
//               'aux' é a posição a partir da qual as chaves serão movidas.
// Pós-condição: A chave à esquerda é removida da árvore B.
void retiraEsquerda(arvoreB *B, int aux){
    int i;
    for(i = aux; i < B->numChaves - 1; i++){
        B->chaves[i] = B->chaves[i + 1];
        B->ptDados[i] = B->ptDados[i + 1];
        B->filhos[i] = B->filhos[i + 1];
    }
    B->filhos[i] = B->filhos[i+1];
    B->numChaves--;
}

// Descrição: Realiza a concatenação de duas subárvores na árvore B.
// Pré-condição: 'raiz' deve ser um ponteiro válido para a raiz da árvore B.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'posArq' é a posição atual no arquivo de índice.
//               'posVetor' é a posição na qual a concatenação será realizada.
// Pós-condição: As duas subárvores são concatenadas na árvore B.
void concatenar(arvoreB * raiz, arquivoB *arqIndice, int posArq, int posVetor){
    arvoreB filhoEsq, filhoDir, filho;
    lerDados(&filho, raiz->filhos[posVetor], sizeof(arvoreB), arqIndice);
    lerDados(&filhoEsq, raiz->filhos[posVetor - 1], sizeof(arvoreB), arqIndice);
    lerDados(&filhoDir, raiz->filhos[posVetor + 1], sizeof(arvoreB), arqIndice);

    if(posVetor - 1 >= 0){
        int j = 0;
        adicionaDireita(&filho, &j, raiz->chaves[posVetor - 1], raiz->ptDados[posVetor - 1], filho.filhos[0]);

        for(int i = 0; i < filhoEsq.numChaves; i++)
            adicionaDireita(&filho, &i, filhoEsq.chaves[i], filhoEsq.ptDados[i], filhoEsq.filhos[i+1]);

        filho.filhos[0] = filhoEsq.filhos[0];
        gravaDados(&filho, raiz->filhos[posVetor], sizeof(arvoreB), arqIndice);

        if(arqIndice->cab.pos_livre == -1){
            filhoEsq.chaves[0] = -1;
        } else {
            filhoEsq.chaves[0] = arqIndice->cab.pos_livre;
        }
        arqIndice->cab.pos_livre = raiz->filhos[posVetor - 1];
        filhoEsq.numChaves = 0;

        gravaDados(&filhoEsq, raiz->filhos[posVetor - 1], sizeof(arvoreB), arqIndice);
        retiraEsquerda(raiz, posVetor - 1);
        gravaDados(raiz, posArq, sizeof(arvoreB), arqIndice);

    } else if (posVetor + 1 <= raiz->numChaves) {
        int j = 0;
        adicionaDireita(&filhoDir, &j, raiz->chaves[posVetor], raiz->ptDados[posVetor], filhoDir.filhos[0]);

        for(int i = 0; i < filho.numChaves; i++)
            adicionaDireita(&filhoDir, &i, filho.chaves[i], filho.ptDados[i], filho.filhos[i+1]);

        filhoDir.filhos[0] = filho.filhos[0];
        gravaDados(&filhoDir, raiz->filhos[posVetor + 1], sizeof(arvoreB), arqIndice);

        if(arqIndice->cab.pos_livre == -1){
            filho.chaves[0] = -1;
        } else {
            filho.chaves[0] = arqIndice->cab.pos_livre;
        }
        arqIndice->cab.pos_livre = raiz->filhos[posVetor];
        filhoEsq.numChaves = 0;
        gravaDados(&filho, raiz->filhos[posVetor], sizeof(arvoreB), arqIndice);
        retiraEsquerda(raiz, posVetor);
        gravaDados(raiz, posArq, sizeof(arvoreB), arqIndice);
    }
    escreveCabecalho(arqIndice);
}

// Descrição: Realiza o empréstimo de uma chave de uma subárvore para outra na árvore B.
// Pré-condição: 'raiz' deve ser um ponteiro válido para a raiz da árvore B.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'posArq' é a posição atual no arquivo de índice.
//               'posVetor' é a posição na qual o empréstimo será realizado.
// Pós-condição: Uma chave é emprestada de uma subárvore para outra na árvore B.
int emprestimo(arvoreB * raiz, arquivoB *arqIndice, int posArq, int posVetor){
    arvoreB filhoEsq, filhoDir, filho;
    lerDados(&filho, raiz->filhos[posVetor], sizeof(arvoreB), arqIndice);
    lerDados(&filhoEsq, raiz->filhos[posVetor - 1], sizeof(arvoreB), arqIndice);
    lerDados(&filhoDir, raiz->filhos[posVetor + 1], sizeof(arvoreB), arqIndice);

    if(posVetor - 1 >= 0 && filhoEsq.numChaves > (ORDEM-1)/2){
        int j = 0;
        adicionaDireita(&filho, &j, raiz->chaves[posVetor - 1], raiz->ptDados[posVetor - 1], -1);
        gravaDados(&filho, raiz->filhos[posVetor], sizeof(arvoreB), arqIndice);

        int novaChave = filhoEsq.numChaves - 1;
        raiz->chaves[posVetor-1] = filhoEsq.chaves[novaChave];
        raiz->ptDados[posVetor-1] = filhoEsq.ptDados[novaChave];
        gravaDados(raiz, posArq, sizeof(arvoreB), arqIndice);

        retiraEsquerda(&filhoEsq, novaChave);
        gravaDados(&filhoEsq, raiz->filhos[posVetor - 1], sizeof(arvoreB), arqIndice);

        return 1;
    }
    if(posVetor + 1 <= raiz->numChaves && filhoDir.numChaves > (ORDEM-1)/2){
        int i = filho.numChaves;
        adicionaDireita(&filho, &i, raiz->chaves[posVetor], raiz->ptDados[posVetor], -1);
        gravaDados(&filho, raiz->filhos[posVetor], sizeof(arvoreB), arqIndice);

        raiz->chaves[posVetor] = filhoDir.chaves[0];
        raiz->ptDados[posVetor] = filhoDir.ptDados[0];
        gravaDados(raiz, posArq, sizeof(arvoreB), arqIndice);

        retiraEsquerda(&filhoDir, 0);
        gravaDados(&filhoDir, raiz->filhos[posVetor + 1], sizeof(arvoreB), arqIndice);

        return 1;
    }
    return 0;
}

// Descrição: Encontra a sucessora de uma chave na árvore B.
// Pré-condição: 'B' deve ser um ponteiro válido para a estrutura da árvore B.
//               'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'ptDado' é um ponteiro para armazenar a posição de dados associada à sucessora.
// Pós-condição: Retorna a sucessora da chave na árvore B.
int sucessora(arvoreB *B, arquivoB *arqIndice, int *ptDado) {
    if (arqIndice->cab.pos_cabeca == -1) return -1; // Valor de erro para indicar sucessor não encontrado

    if(B->filhos[0] == -1){
        int sucessor = B->chaves[0]; // Armazena o valor da chave do sucessor
        (*ptDado) = B->ptDados[0];
        return sucessor;
    } else {
        arvoreB aux;
        lerDados(&aux, B->filhos[0], sizeof(arvoreB), arqIndice);
        return sucessora(&aux, arqIndice, ptDado);
    }
}

// Pré-condição: 'arqIndice' deve ser um ponteiro válido para o arquivo de índice.
//               'B' deve ser um ponteiro válido para a árvore B.
//               'posArq' deve ser a posição atual no arquivo de índice.
//               'codUsuario' deve ser o código de usuário a ser removido.
// Pós-condição: O índice correspondente ao código de usuário é removido do arquivo de índice.
void removeArqIndex(arquivoB *arqIndice, arvoreB *B, int posArq, int codUsuario){
    //posVetor: variavel para saber a posição do vetor
    arvoreB f;
    f.numChaves = -1;
    int posVetor;
    for(posVetor = 0; posVetor < B->numChaves; posVetor++){
        if(codUsuario == B->chaves[posVetor] || codUsuario < B->chaves[posVetor])
            break;
    }
    if(posVetor < B->numChaves && codUsuario == B->chaves[posVetor]){
        if(ehFolha(*B)){
            retiraEsquerda(B, posVetor); //se estiver pensando certo, a gente só faz a lista encadeada quando removermos uma pagina e não apenas um nó
            gravaDados(B, posArq, sizeof(arvoreB), arqIndice);
        }
        else { //remoção do nó interno
            int ptDado;
            arvoreB filho;
            lerDados(&filho, B->filhos[posVetor + 1], sizeof(arvoreB), arqIndice);
            int infoApos = sucessora(&filho, arqIndice, &ptDado);
            B->chaves[posVetor] = infoApos;
            B->ptDados[posVetor] = ptDado;
            gravaDados(B, posArq, sizeof(arvoreB), arqIndice);
            removeArqIndex(arqIndice, &filho, B->filhos[posVetor + 1], infoApos); //pode haver modificações
            if(underflow(filho.numChaves)){
                if(!emprestimo(B, arqIndice, posArq, posVetor + 1)){
                    concatenar(B, arqIndice, posArq, posVetor + 1);
                }
            }
        }
    }
    else{
        lerDados(&f, B->filhos[posVetor], sizeof(arvoreB), arqIndice);
        removeArqIndex(arqIndice, &f,  B->filhos[posVetor], codUsuario);
    }
    if(!ehFolha(*B)){
        if(f.numChaves != -1 && underflow(f.numChaves)){
            if(!emprestimo(B, arqIndice, posArq, posVetor)){
                concatenar(B, arqIndice, posArq, posVetor);
            }
        }
    }
    if(B->numChaves == 0){
        if(arqIndice->cab.pos_livre == -1){
            B->chaves[0] = -1;
        } else {
            B->chaves[0] = arqIndice->cab.pos_livre;
        }
        arqIndice->cab.pos_cabeca = B->filhos[0];
        arqIndice->cab.pos_livre = posArq;
        gravaDados(B, posArq, sizeof(arvoreB), arqIndice);
        escreveCabecalho(arqIndice);
    }

}
