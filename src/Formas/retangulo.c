#include "retangulo.h"

typedef struct {
    int id;
    int tipo;
    double x;
    double y;
    double vida;
    double DistanciaCentro;
    double peso;
    double dano;
    double adubagem;
    double w;
    double h;
    char* corb;
    char* corp;
    double area;
    int contador;
    Lista Colhidos;
    bool Colheitadera;
} RetanguloImpl;

Retangulo InicializaRetangulo (int id, double x, double y, double w, double h, char* corb, char* corp) {

    RetanguloImpl* ret = (RetanguloImpl*)malloc(sizeof(RetanguloImpl));
    ret->id = id;
    ret->tipo = 3;
    ret->x = x;
    ret->y = y;
    ret->w = w;
    ret->h = h;
    ret->corb = corb;
    ret->corp = corp;
    ret->area = w * h;
    ret->DistanciaCentro = 0.0;
    ret->contador = 0;
    Lista Colhidos = createLst(-1);
    ret->Colhidos = Colhidos;
    ret->Colheitadera = false;
    ret->peso = 1000;
    ret->vida = ret->peso;
    ret->dano = 1.0;
    ret->adubagem = 0.0;
    return (Retangulo)ret;
}

double GetRectangleWidth (Retangulo ret) {

    return ((RetanguloImpl*)ret)->w;
}

double GetRectangleHeight (Retangulo ret) {

    return ((RetanguloImpl*)ret)->h;
}

char* GetRectangleCorb (Retangulo ret) {

    return ((RetanguloImpl*)ret)->corb;
}

char* GetRectangleCorp (Retangulo ret) {

    return ((RetanguloImpl*)ret)->corp;
}

double GetRectangleArea (Retangulo ret) {

    return ((RetanguloImpl*)ret)->area;
}

int GetColheitaderaContador (Retangulo ret) {

    return ((RetanguloImpl*)ret)->contador;
}

Lista GetColheitadeColhidos (Retangulo ret) {

    return ((RetanguloImpl*)ret)->Colhidos;
}

void SetRectangleCorb (Retangulo ret, char* corb) {

    RetanguloImpl* r = (RetanguloImpl*)ret;

    r->corb = corb;
}

void SetRectangleCorp (Retangulo ret, char* corp) {

    RetanguloImpl* r = (RetanguloImpl*)ret;

    r->corp = corp;
}

void SetContador (Retangulo ret, int contador) {

    RetanguloImpl* r = (RetanguloImpl*)ret;

    if (r->Colheitadera) r->contador = contador;
}

void SetColhidos (Retangulo ret, Info item, Lista lista) {

    RetanguloImpl* r = (RetanguloImpl*)ret;

    if (lista != NULL) {
        r->Colhidos = lista;
    }
    else if (r->Colheitadera) insertLst(r->Colhidos, item);
}

void SetColheitadera (Retangulo ret, bool x) {

    RetanguloImpl* r = (RetanguloImpl*)ret;

    r->Colheitadera = x;
}

bool IsColheitadera (Retangulo ret) {

    RetanguloImpl* r = (RetanguloImpl*)ret;

    if (r->Colheitadera) return true;
    else return false;
}