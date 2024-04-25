#include <stdio.h>
#include <stdlib.h>

struct node23 {
    int leftKey;
    int rightKey;
    struct node23 *left;
    struct node23 *mid;
    struct node23 *right;
    int n;
};

typedef struct node23 *tree23;

int empty(tree23 r) { return (r == NULL); }

// Retorno: ponteiro para o n´o contendo a chave ou
// NULL caso a chave n~ao perten¸ca `a `arvore
tree23 busca(tree23 r, int chave) {
    if (empty(r)) return NULL;
    if (r->leftKey == chave) return r;
    if (r->n == 2 && r->rightKey == chave) return r;
    if (chave < r->leftKey)
        return busca(r->left, chave);
    else if (r->n == 1)
        return busca(r->mid, chave);
    else if (chave < r->rightKey)
        return busca(r->mid, chave);
    else
        return busca(r->right, chave);
}

tree23 createNode(int leftKey, int rightKey, tree23 left, tree23 mid,
                  tree23 right, int n) {
    tree23 aux = (tree23)malloc(sizeof(struct node23));
    aux->leftKey = leftKey;
    aux->rightKey = rightKey;
    aux->left = left;
    aux->mid = mid;
    aux->right = right;
    aux->n = n;
    return aux;
}

void keyAdd(tree23 r, int key, tree23 p) {
    if (r->leftKey < key) {
        r->rightKey = key;
        r->right = p;
    } else {
        r->rightKey = r->leftKey;
        r->leftKey = key;
        r->right = r->mid;
        r->mid = p;
    }
    r->n = 2;
}

int isLeaf(tree23 r) { return (r->left == NULL); }

tree23 split(tree23 p, int key, tree23 subTree, int *keyAux) {
    tree23 aux;
    if (key > p->rightKey) {
        *keyAux = p->rightKey;
        aux = p->right;
        p->right = NULL;
        p->n = 1;
        return createNode(key, 0, aux, subTree, NULL, 1);
    }
    if (key >= p->leftKey) {
        *keyAux = key;
        aux = p->right;
        p->right = NULL;
        p->n = 1;
        return createNode(p->rightKey, 0, subTree, aux, NULL, 1);
    }
    *keyAux = p->leftKey;
    aux = createNode(p->rightKey, 0, p->mid, p->right, NULL, 1);
    p->leftKey = key;
    p->n = 1;
    p->right = NULL;
    p->mid = subTree;
    return aux;
}

tree23 insertAux(tree23 r, int key, int *keyAux) {
    if (isLeaf(r)) {
        if (r->n == 1) {
            keyAdd(r, key, NULL);
            return NULL;
        } else
            return split(r, key, NULL, keyAux);
    } else {
        tree23 aux;
        int k;
        if (key < r->leftKey) {
            aux = insertAux(r->left, key, &k);
        } else if ((r->n == 1) || (key < r->rightKey)) {
            aux = insertAux(r->mid, key, &k);
        } else {
            aux = insertAux(r->right, key, &k);
        }
        if (empty(aux)) return aux;
        if (r->n == 1) {
            keyAdd(r, k, aux);
            return NULL;
        } else
            return split(r, k, aux, keyAux);
    }
}

tree23 insert(tree23 r, int key) {
    if (empty(r)) {
        return createNode(key, 0, NULL, NULL, NULL, 1);
    } else {
        int promoveKey;
        tree23 aux = insertAux(r, key, &promoveKey);
        if (!empty(aux))  // caso para criar nova root
            return createNode(promoveKey, 0, r, aux, NULL, 1);
        else
            return r;
    }
}

void InOrdem(tree23 root) {
    if (root != NULL) {
        InOrdem(root->mid);
        printf("%d ", root->leftKey);
        InOrdem(root->mid);
        if (root->n == 2) printf("%d ", root->rightKey);
        InOrdem(root->right);
    }
}

int high(tree23 root) {
    if (root != NULL) return 1 + high(root->left);
    return -1;
}

void printNivelAux(tree23 root, int i, int nivel) {
    if (root != NULL) {
        if (i == nivel) {
            printf("[");
            if (root->n == 2) {
                printf("%d ", root->leftKey);
                printf("%d", root->rightKey);
            } else
                printf("%d", root->leftKey);
            printf("] ");
        }
        printNivelAux(root->left, i + 1, nivel);
        printNivelAux(root->mid, i + 1, nivel);
        printNivelAux(root->right, i + 1, nivel);
    }
}

void printNivel(tree23 root) {
    int i, highArvore;
    highArvore = high(root);
    for (i = 0; i <= highArvore; i++) {
        printNivelAux(root, 0, i);
        printf("\n");
    }
}


int main() {
    tree23 teste = NULL;
    int i;
    teste = insert(teste, 65);
    teste = insert(teste, 15);
    teste = insert(teste, 75);
    teste = insert(teste, 10);
    teste = insert(teste, 40);
    teste = insert(teste, 5);
    teste = insert(teste, 30);
    teste = insert(teste, 50);
    teste = insert(teste, 70);
    teste = insert(teste, 85);
    teste = insert(teste, 80);
    teste = insert(teste, 90);
    teste = insert(teste, 88);
    teste = insert(teste, 100);
    teste = insert(teste, 120);
    teste = insert(teste, 110);
    teste = insert(teste, 89);
    // InOrdem(teste);
    printNivel(teste);

    return 0;
}