#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct StNode {
    struct StNode *prox;
    struct StNode *ant;
    Item info;
};

struct StLista {
    struct StNode *prim;
    struct StNode *ult;
    int capac;
    int lenght;
};

typedef struct StLista ListaImpl;
typedef struct StNode Node;

struct StIterator {
    Node *curr;
    bool reverso;
};

typedef struct StIterator IteradorImpl;

Lista createLst (int capacidade) {

    ListaImpl *newLista = (ListaImpl *)calloc(1,sizeof(ListaImpl));
    newLista->prim = NIL;
    newLista->ult = NIL;
    newLista->capac = capacidade;
    newLista->lenght = 0;
    return (newLista);
}

int lengthLst (Lista L) {

    ListaImpl *lst = (ListaImpl *)L;
    return lst->lenght;
}

int maxLengthLst (Lista L) {

    ListaImpl *lst = (ListaImpl *)L;
    return lst->capac;
}

bool isEmptyLst (Lista L) {

    ListaImpl *lst = (ListaImpl *)L;
    return lst->lenght == 0;
}

bool isFullLst (Lista L) {

    ListaImpl *lst = (ListaImpl *)L;
    return lst->lenght == lst->capac;
}

Posic insertLst (Lista L, Item info) {

    ListaImpl *lst = (ListaImpl *)L;
    Node *newNode = (Node *)calloc(1,sizeof(Node));
    newNode->info = info;
    newNode->prox = NIL;

    if (isEmptyLst(lst)) lst->prim = newNode;
    else lst->ult->prox = newNode;

    newNode->ant = lst->ult;
    lst->ult = newNode;
    lst->lenght++;
    return (Posic)newNode;
}

Item popLst (Lista L) {

    ListaImpl *lst = (ListaImpl *)L;
    Item item = lst->prim->info;
    Node *paux;
    paux = lst->prim;
    lst->prim = paux->prox;

    if (paux->prox == NIL) lst->ult = NIL;
    else paux->prox->ant = NIL;

    lst->lenght--;
    free (paux);
    return item;
}

void removeLst (Lista L, Posic p) {

    ListaImpl *lst = (ListaImpl *)L;
    Node *paux = (Node *)p;

    if (getLastLst(lst) == getFirstLst(lst)) {
        lst->prim = NIL;
        lst->ult = NIL;
    }
    else if (paux == lst->prim) {
        lst->prim = paux->prox;
        lst->prim->ant = NIL;
        paux->prox = NIL;
    }
    else if (paux == lst->ult) {
        lst->ult = paux->ant;
        paux->ant->prox = NIL;
    }
    else {
        paux->ant->prox = paux->prox;
        paux->prox->ant = paux->ant;
    }

    lst->lenght--;
    free (paux);
}

Item getLst(Lista L, Posic p) {

    ListaImpl *lst = (ListaImpl *)L;
    Node *paux = (Node *)p;
    Node *aux = lst->prim;
    
    if (paux == lst->prim) return paux->info;
    else while (aux != paux && aux != NIL) aux = aux->prox;

    if (aux == NIL) return NIL;
    else return paux->info;
}

Posic insertBefore(Lista L, Posic p, Item info) {

    ListaImpl *lst = (ListaImpl *)L;
    Node *newNode = (Node *)calloc(1,sizeof(Node));
    newNode->info = info;
    Node *paux = (Node *)p;
    Node *aux = lst->prim;
    
    while (aux != paux && aux != NIL) aux = aux->prox;

    if (aux == NIL) return NIL;
    else {
        if (paux == lst->prim) {
            newNode->prox = paux;
            paux->ant = newNode;
            newNode->ant = NIL;
        }
        else {
            newNode->prox = paux;
            paux->ant->prox = newNode;
            newNode->ant = paux->ant;
            paux->ant = newNode;
        }
    }

    lst->lenght++;
    return (newNode);
}

Posic insertAfterLst(Lista L, Posic p, Item info) {

    ListaImpl *lst = (ListaImpl *)L;
    Node *newNode = (Node *)calloc(1,sizeof(Node));
    newNode->info = info;
    Node *paux = (Node *)p;
    Node *aux = lst->prim;
    
    while (aux != paux && aux != NIL) aux = aux->prox;

    if (aux == NIL) return NIL;
    else {
        if (paux == lst->ult) {
            newNode->prox = NIL;
            newNode->ant = paux;
            paux->prox = newNode;
        }
        else {
            newNode->ant = paux;
            newNode->prox = paux->prox;
            paux->prox->ant = newNode;
            paux->prox = newNode;
        }
    }

    lst->lenght++;
    return (newNode);
}

Posic getFirstLst(Lista L) {

    ListaImpl *lst = (ListaImpl *)L;

    if (lst->lenght == 0) {
        return NIL;
    }
    else {
        return lst->prim;
    }
}

Posic getNextLst(Lista L, Posic p) {

    ListaImpl *lst = (ListaImpl *)L;
    Node *paux = (Node *)p;
    Node *aux = lst->prim;
    
    while (aux != paux && aux != NIL) aux = aux->prox;

    if (aux == NIL) return NIL;
    else {
        if (paux == lst->ult) {
            return NIL;
        }
        else {
            return paux->prox;
        }
    }
}

Posic getLastLst(Lista L) {

    ListaImpl *lst = (ListaImpl *)L;

    if (lst->lenght == 0) {
        return NIL;
    }
    else {
        return lst->ult;
    }
}

Posic getPreviousLst(Lista L,Posic p) {

    ListaImpl *lst = (ListaImpl *)L;
    Node *paux = (Node *)p;
    Node *aux = lst->prim;

    while (aux != paux && aux != NIL) aux = aux->prox;

    if (aux == NIL) return NIL;
    else {
        if (paux == lst->prim) {
            return NIL;
        }
        else {
            return paux->ant;
        }
    }
}

void killLst(Lista L) {

    ListaImpl *lst = (ListaImpl *)L;
    Node *paux = lst->prim;

    if (lst->prim == NIL) return;

    while (paux != NIL) {
        Node *aux = paux;
        paux = paux->prox;
        free (aux);
    }

    free (lst);
    L = NIL;
}

Iterador createIterador(Lista L, bool reverso) {

    ListaImpl *lst = (ListaImpl *)L;
    IteradorImpl *newIter = (IteradorImpl *)calloc(1,sizeof(IteradorImpl));

    if (reverso) newIter->curr = getLastLst(lst);
    else newIter->curr = getFirstLst(lst);

    newIter->reverso = reverso;

    return (Iterador)newIter;
}

bool isIteratorEmpty(Lista L, Iterador it) {

    IteradorImpl *Iter = (IteradorImpl *)it;

    if (Iter->reverso) {
        if (Iter->curr == ((Node *)getFirstLst(L))->ant) return true;
        else return false;
    }
    else {
        if (Iter->curr == ((Node *)getLastLst(L))->prox) return true;
        else return false;
    }
}

Item getIteratorNext(Lista L, Iterador it) {

    ListaImpl *lst = (ListaImpl *)L;
    IteradorImpl *Iter = (IteradorImpl *)it;

    Item aux = Iter->curr->info;

    if (Iter->reverso) Iter->curr = (Node *)getPreviousLst(lst,Iter->curr);
    else Iter->curr = (Node *)getNextLst(lst,Iter->curr);

    return (aux);
}

void killIterator(Lista L, Iterador it) {

    if (L == NULL || it == NULL) return;

    free(it);
}

Lista map(Lista L, Apply f) {

    Lista newLst = createLst(-1);
    Iterador iter = createIterador(L, false);

    while (!isIteratorEmpty(L, iter))
    {
        Item info = getIteratorNext(L, iter);
        Item newInfo = f(info);
        insertLst(newLst, newInfo);
    }

    killIterator(L, iter);

    return newLst;
}

Lista filter(Lista L, Check f) {

    Lista newLst = createLst(-1);
    Iterador iter = createIterador(L, false);

    while (!isIteratorEmpty(L, iter))
    {
        Item info = getIteratorNext(L, iter);
        if (f(info))
        {
            insertLst(newLst, info);
        }
    }

    killIterator(L, iter);

    return newLst;
}

void fold(Lista L, ApplyClosure f, Clausura c, void* aux) {

    ListaImpl *lst = (ListaImpl *)L;
    Iterador iter = createIterador(lst, false);

    while (!isIteratorEmpty(lst, iter))
    {
        Item info = getIteratorNext(lst, iter);
        f(info, c, aux);
    }

    killIterator(lst, iter);
}