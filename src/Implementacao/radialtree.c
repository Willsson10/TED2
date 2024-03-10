#include "radialtree.h"
#include "ordenacao.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

typedef struct NodeT {
    Info item;
    bool removido;
    struct NodeT** setor;
}NodeImpl;

typedef struct RadialT {
    int setores;
    double quantidade;
    double eliminados;
    double fd;
    NodeImpl* raiz;
}RadialTreeImpl;

RadialTree newRadialTree(int numSetores, double fd) {
    
    RadialTreeImpl* arvore = malloc(sizeof(RadialTreeImpl));
    
    arvore->setores = numSetores;
    arvore->quantidade = 0;
    arvore->eliminados = 0;
    arvore->fd = fd;
    arvore->raiz = NULL;
    return arvore;
}

Node insertRadialT(RadialTree t, double x, double y, Info i) {

    RadialTreeImpl* arvore = (RadialTreeImpl *)t;
    NodeImpl* aux = arvore->raiz;
    arvore->quantidade = (int)arvore->quantidade + 1; //Atualizando a quantidade maxima de nos da arvore

    if (arvore->raiz == NULL) {
        NodeImpl* novo = malloc(sizeof(NodeImpl)); //Alocando memória para o novo no
        novo->item = i;
        novo->removido = false;
        novo->setor = malloc(arvore->setores * sizeof(NodeImpl*));
        for (int i=0; i<arvore->setores; i++) novo->setor[i] = NULL;
        arvore->raiz = novo; 
        return novo;
    }
    else {
        int setor = PontoNoSetor(arvore->setores, GetX(aux->item), GetY(aux->item), x, y);

        RadialTreeImpl radial_aux;
        radial_aux.setores = arvore->setores;
        radial_aux.raiz = aux->setor[setor];

        aux->setor[setor] = insertRadialT(&radial_aux, x, y, i);
        return aux;
    }
}

Node getNodeRadialT(RadialTree t, double x, double y, double epsilon) {

    RadialTreeImpl* arvore = (RadialTreeImpl *)t;
    NodeImpl* aux = arvore->raiz;

    if (aux == NULL) return NULL; //Conferindo se a raiz da arvore posui nos

    if (fabs(GetX(aux->item) - x) < epsilon && fabs(GetY(aux->item) - y) < epsilon) {
        if (!(aux->removido)) return aux; //Apenas retorna o no, caso ele nao esteja marcado como removido
        // else return NULL;
    }
    
    int setor = PontoNoSetor(arvore->setores, GetX(aux->item), GetY(aux->item), x, y);

    RadialTreeImpl radial_aux;
    radial_aux.setores = arvore->setores;
    radial_aux.raiz = aux->setor[setor];

    return getNodeRadialT(&radial_aux, x, y, epsilon);
    
}

void removeNoRadialT(RadialTree t, Node n) {

    RadialTreeImpl* arvore = (RadialTreeImpl *)t;

    if (arvore->raiz == NULL) return;

    NodeImpl* node = (NodeImpl *)n;

    if (node == NULL) return; //Retorna NULL caso o node a ser removido seja NULL

    node->removido = true;
    arvore->eliminados++; //Atualiza a quantidade de nos marcados como removidos na arvore

    if (arvore->eliminados/arvore->quantidade >= arvore->fd) { //Confere se eh necessario realizar uma "reconstrucao" da arvore
        int TamanhoVetor = (int)(arvore->quantidade - arvore->eliminados);
        RadialTreeImpl* ArvoreAux = (RadialTreeImpl*)ReorganizaArvore(arvore, TamanhoVetor, arvore->setores, arvore->fd); //Reorganizando arvore radial

        // Atualizando arvore principal
        killRadialTree(arvore);
        arvore->quantidade = ArvoreAux->quantidade;
        arvore->eliminados = ArvoreAux->eliminados;
        arvore->raiz = ArvoreAux->raiz;
        ArvoreAux->raiz = NULL;
    }
}

Info getInfoRadialT(RadialTree t, Node n) {

    RadialTreeImpl* arvore = (RadialTreeImpl *)t;

    if (arvore->raiz == NULL || n == NULL) return NULL; //Confere se a raiz da arvore possui nos ou se o no n eh NULL

    NodeImpl* node = (NodeImpl *)n;
    
    return node->item;
}

bool getNodesDentroRegiaoRadialT(RadialTree t, double x1, double y1, double x2, double y2, Lista L) {

    RadialTreeImpl* arvore = (RadialTreeImpl *)t;
    NodeImpl* aux = arvore->raiz;

    if (aux == NULL) return false; //Confere se a raiz da arvore possui nos
    
    if (GetPontoDentroRetangulo(GetX(aux->item), GetY(aux->item), x1, y1, x2, y2) && !(aux->removido)) insertLst(L, aux->item);
    for (int i=0; i<arvore->setores; i++) {
        //Fazendo a busca apenas nos setores, em que os nos podem estar dentro do retangulo
        if (aux->setor[i] != NULL && ConfereSetorDoRetangulo(i, arvore->setores, x1, y1, x2, y2, GetX(aux->item), GetY(aux->item))) {
            RadialTreeImpl radial_aux;
            radial_aux.setores = arvore->setores;
            radial_aux.raiz = aux->setor[i];

            getNodesDentroRegiaoRadialT(&radial_aux, x1, y1, x2, y2, L);
        }
    }

    if (isEmptyLst(L)) return false;
    else return true;
}

bool getInfosDentroRegiaoRadialT(RadialTree t, double x1, double y1, double x2, double y2, FdentroDeRegiao f, Lista L) {

    RadialTreeImpl* arvore = (RadialTreeImpl *)t;
    NodeImpl* aux = arvore->raiz;

    if (aux == NULL) return false; //Confere se a raiz da arvore possui nos
    
    if (f(aux->item, x1, y1, x2, y2) && !(aux->removido)) insertLst(L, aux->item); //Inserindo informacoes na lista, para quais, a funcao f retorna true
    for (int i=0; i<arvore->setores; i++) {
    //Fazendo a busca apenas nos setores, em que os nos podem estar dentro do retangulo
        if (aux->setor[i] != NULL && ConfereSetorDoRetangulo(i, arvore->setores, x1, y1, x2, y2, GetX(aux->item), GetY(aux->item))) {
            RadialTreeImpl radial_aux;
            radial_aux.setores = arvore->setores;
            radial_aux.raiz = aux->setor[i];

            getInfosDentroRegiaoRadialT(&radial_aux, x1, y1, x2, y2, f, L);
        }
    }

    if (isEmptyLst(L)) return false;
    else return true;
}

/**/
bool getInfosAtingidoPontoRadialT(RadialTree t, double x, double y, FpontoInternoAInfo f, Lista L) {

    RadialTreeImpl* arvore = (RadialTreeImpl *)t;
    NodeImpl* aux = arvore->raiz;

    if (aux == NULL) return false; //Confere se a raiz da arvore possui nos
    
    if (f(aux->item, x, y) && !(aux->removido)) insertLst(L, aux->item); //Inserindo informacoes na lista, para quais, a funcao f retorna true
    for (int i=0; i<arvore->setores; i++) {
        if (aux->setor[i] != NULL) {
            RadialTreeImpl radial_aux;
            radial_aux.setores = arvore->setores;
            radial_aux.raiz = aux->setor[i];
            
            getInfosAtingidoPontoRadialT(&radial_aux, x, y, f, L);
        }
    }
    
    if (isEmptyLst(L)) return false;
    else return true;
}

void visitaProfundidadeRadialT(RadialTree t, FvisitaNo f, void *aux) {

    RadialTreeImpl* arvore = (RadialTreeImpl*)t;
    NodeImpl* node = arvore->raiz;

    if (node == NULL) return; //Confere se a raiz da arvore possui nos

    if (!(node->removido)) f(node->item, GetX(node->item), GetY(node->item), aux); //Invoca a funcao f em todos os nos da arvore, exceto nos que foram marcados como removidos
    for (int i=0; i<arvore->setores; i++) {
        if (node->setor[i] != NULL) {
            RadialTreeImpl radial_aux;
            radial_aux.setores = arvore->setores;
            radial_aux.raiz = node->setor[i];

            visitaProfundidadeRadialT(&radial_aux, f, aux);
        }
    }
}

void visitaLarguraRadialT(RadialTree t, FvisitaNo f, void* aux) {
    RadialTreeImpl* arvore = (RadialTreeImpl*)t;

    if (arvore->raiz == NULL)
        return;

    NodeImpl** fila = (NodeImpl**)malloc(arvore->setores * sizeof(NodeImpl*));
    int frente = 0;
    int tras = 0;

    fila[tras++] = arvore->raiz;

    while (frente < tras) {
        NodeImpl* noAtual = fila[frente++];
        f(noAtual->item, GetX(noAtual->item), GetY(noAtual->item), aux);

        for (int j = 0; j < arvore->setores; j++) {
            if (noAtual->setor[j] != NULL)
                fila[tras++] = noAtual->setor[j];
        }
    }

    free(fila);
}


Node procuraNoRadialT(RadialTree t, FsearchNo f, void *aux) {

    RadialTreeImpl* arvore = (RadialTreeImpl*)t;
    NodeImpl* node = arvore->raiz;

    if (node == NULL) return NULL;

    if (f(node->item, GetX(node->item), GetY(node->item), aux)) {
        if (!node->removido) {
            if (node != NULL) return node;
        }
    }
    for (int i=0; i<arvore->setores; i++) {
        if (node->setor[i] != NULL) {
            RadialTreeImpl radial_aux;
            radial_aux.setores = arvore->setores;
            radial_aux.raiz = node->setor[i];

            Node NoAux = procuraNoRadialT(&radial_aux, f, aux);
            if (NoAux != NULL) return NoAux;
        }
    }
}

bool printDotRadialTree(RadialTree t, char *fn) {

    RadialTreeImpl* arvore = (RadialTreeImpl*)t;
    NodeImpl* node = arvore->raiz;
    if (node == NULL) return false;

    FILE* dot = fopen(fn, "a+");
    if (dot == NULL) return false;
    for (int i=0; i<arvore->setores; i++) {
        char PaiRemovido[5] = "", FilhoRemovido[5] = "";
        if (node->setor[i] != NULL) {
            if (node->removido) strncpy(PaiRemovido, "*", 5);
            if (node->setor[i]->removido) strncpy(FilhoRemovido, "*", 5); 
            fprintf (dot, "\t\"(%d, %d) %d%s\" -> \"(%d, %d) %d%s\";\n", (int)GetX(node->item), (int)GetY(node->item), GetID(node->item), PaiRemovido,
                        (int)GetX(node->setor[i]->item), (int)GetY(node->setor[i]->item), GetID(node->setor[i]->item), FilhoRemovido);
            if (node->removido) fprintf (dot, "\t\"(%d, %d) %d%s\" [style=filled, fillcolor=red, fontcolor=black];\n", 
                                    (int)GetX(node->item), (int)GetY(node->item), GetID(node->item), PaiRemovido);
        }
    }
    for (int i=0; i<arvore->setores; i++) {
        if (node->setor[i] != NULL) {
            RadialTreeImpl radial_aux;
            radial_aux.setores = arvore->setores;
            radial_aux.raiz = node->setor[i];

            printDotRadialTree(&radial_aux, fn);
        }
    }
    fclose(dot);
    return true;
}

void killRadialTree(RadialTree t) {

    RadialTreeImpl* arvore = (RadialTreeImpl*)t;

    if (arvore != NULL) {
        NodeImpl* node = arvore->raiz;

        if (node != NULL) {
            for (int i = 0; i < arvore->setores; i++) {
                if (node->setor[i] != NULL) {
                    RadialTreeImpl radial_aux;
                    radial_aux.setores = arvore->setores;
                    radial_aux.raiz = node->setor[i];
                    
                    killRadialTree(&radial_aux);
                }
            }
            free(node);
        }
    }
}