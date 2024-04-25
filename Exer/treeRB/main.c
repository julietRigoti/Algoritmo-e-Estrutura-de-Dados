#include <stdio.h>
#include <stdlib.h>

typedef struct noRB{
    /* data */
    enum
    { RED, BLACK} color;
    int key;
    struct noRB *left;
    struct noRB *right;
    struct noRB *super; // pai
} nodeRB;

typedef struct{
    nodeRB *root; // root da arvore
    nodeRB *nil;  // no sentinela para as folhas
} treeRB;

treeRB *createTree(){

    treeRB *aux; // arvore auxiliar
    // por que precisa criar um node temp?
    nodeRB *temp; // no temporario

    aux = (treeRB *)malloc(sizeof(treeRB));

   temp = aux->nil = (nodeRB *)malloc(sizeof(nodeRB)); // fazer um teste se isso é possivel com aux->root

    temp->super = temp->left = temp->right = temp; // será que isso serve para questão da locação?
  
    temp = aux->root = (nodeRB *)malloc(sizeof(nodeRB)); //preciso fazer alocação do aux->root porque eu retorno o ponteiro aux e se eu não fizer a alocação dá erro nos

    temp->super = temp->left = temp->right = aux->nil ; /* qual a diferença disso para a linha 27? Como se faz outra alocação, o endereço de memoria dele é mudado então o aux->nil trata de colocar os mesmos endereço que antes, para que não tenha problema depois*/

    temp->key = 0;
    temp->color = BLACK;

    return (aux);
}

void leftRotation(treeRB *T, nodeRB *x){
    nodeRB *y;
    nodeRB *nil = T->nil; // para que essa atribuição?

    y = x->right;
    x->right = y->left; // esse aqui é para receber a subarvore T2 do slide

    if (y->left != nil)
        y->left->super = x; // vai receber o nó anterior dele, o super do y a esquerda é ele proprio
    y->super = x->super;

    if (x == x->super->left)
    { // acho que nesse caso é para ver se eles são o mesmo nó, caso ele não tenha filhos
        x->super->left = y;
    }
    else
    {
        x->super->right = y;
    }
    y->left = x;
    x->super = y;
}

void rightRotation(treeRB *T, nodeRB *y){
    nodeRB *x;
    nodeRB *nil = T->nil;

    x = y->left;
    y->left = x->right;

    if (nil != x->right)
        x->right->super = y;
    x->super = y->super;

    if (y == y->super->left)
    {
        y->super->left = x;
    }
    else
    {
        y->super->right = x;
    }
    x->right = y;
    y->super = x;
}

void insertAuxRB(treeRB *rb, nodeRB *z){
    nodeRB *x, *y, *nil = rb->nil;
 
    //nessas proximas linhas é tudo para receber o mesmo endereço de memoria 
    z->left = z->right = nil;
    y = rb->root;
    x = rb->root->left;

    while (x != nil){
        y = x;

        if (x->key > z->key)
            x = x->left;
        else
            x = x->right;
    }

    z->super = y;
    if ((y == rb->root) || (y->key > z->key))
        y->left = z;
    else
        y->right = z;
}

treeRB *insertRB(treeRB *aux, int k){
    nodeRB *y, *x;

    x = (nodeRB *)malloc(sizeof(nodeRB));
    x->key = k;
    insertAuxRB(aux, x);
    x->color = RED;

    while (x->super->color == RED){
        if (x->super == x->super->super->left){
            y = x->super->super->right;
            if (y->color == RED){ // caso 1
                x->super->color = BLACK;
                y->color = BLACK;
                x->super->super->color = RED;
                x = x->super->super;
            }
            else{
                if (x == x->super->right){
                    x = x->super;
                    leftRotation(aux, x);
                }
                x->super->color = BLACK;
                x->super->super->color = RED;
                rightRotation(aux, x->super->super);
            }
        }
        else{ // caso: x->super == x->super->super->right
            y = x->super->super->left;
            if (y->color == RED){
                x->super->color = BLACK;
                y->color = BLACK;
                x->super->super->color = RED;
                x = x->super->super;
            }
            else{
                if (x == x->super->left){
                    x = x->super;
                    rightRotation(aux, x);
                }
                x->super->color = BLACK;
                x->super->super->color = RED;
                leftRotation(aux, x->super->super);
            }
        }
    }
    aux->root->left->color = BLACK;
    return aux;
}

void in_ordem_aux(treeRB *rb, nodeRB *x) {
  nodeRB *nil = rb->nil;
  nodeRB *root = rb->root;

  if (x != nil) {
    in_ordem_aux(rb, x->left);

    printf("  Key: %d\n", x->key);
    printf("  Left Child Key: ");
    if (x->left == nil) {
      printf("NULL ");
    } else {
      printf("%d ", x->left->key);
    }

    printf("  Right Child Key: ");
    if (x->right == nil) {
      printf("NULL ");
    } else {
      printf("%d ", x->right->key);
    }

    printf("  Parent Key: ");
    if (x->super == root) {
      printf("NULL ");
    } else {
      printf("%d ", x->super->key);
    }

    printf("  Color: %d\n", x->color);

    in_ordem_aux(rb, x->right);
  }
}

// chamada inicial
void in_ordemRB(treeRB *rb){
    in_ordem_aux(rb, rb->root);
}


void redCountAux(treeRB *rb, nodeRB *aux, int *k) {

    if (aux != rb->nil) {
        redCountAux(rb, aux->left, k);
        redCountAux(rb, aux->right, k);
        if (aux->color == RED) {
            (*k)++;
        }
    }
}

int redCount(treeRB *rb) {
    int count = 0;
    if (rb->root->left->key != 0)
        redCountAux(rb, rb->root->left, &count);
    return count;
}

void uniqueChildAux(treeRB *rb, nodeRB *aux, int *k){

    if(aux != rb->nil){
        uniqueChildAux(rb, aux->left, k);
        uniqueChildAux(rb, aux->right, k);
        if((aux->left != rb->nil && aux->right == rb->nil) || 
           (aux->right != rb->nil && aux->left == rb->nil)) {
            (*k)++;
        }
    }
}

int uniqueChild(treeRB *rb){
    int count = 0;
    if(rb->root->left->key != 0) uniqueChildAux(rb, rb->root->left, &count);
    return count;
}

int main()
{
    treeRB *teste = createTree();
    teste = insertRB(teste, 11);
    teste = insertRB(teste, 2);
    teste = insertRB(teste, 14);
    teste = insertRB(teste, 1);
    teste = insertRB(teste, 7);
    teste = insertRB(teste, 15);
    teste = insertRB(teste, 5);
    teste = insertRB(teste, 8);
    teste = insertRB(teste, 4);

    in_ordemRB(teste); 

    printf("O numero de nós vermelhos = %d\n", redCount(teste));
    printf("O numero de nós com filho unico = %d\n", uniqueChild(teste));
    return 0;
}