#include "circulo.h"

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
    double r;
    char* corb;
    char* corp;
    double area;
} CirculoImpl;

Circulo InicializaCirculo (int id, double x, double y, double r, char* corb, char* corp) {

    CirculoImpl* cir = (CirculoImpl*)malloc(sizeof(CirculoImpl));
    cir->id = id;
    cir->tipo = 1;
    cir->x = x;
    cir->y = y;
    cir->r = r;
    cir->corb = corb;
    cir->corp = corp;
    cir->area = pi * r * r;
    cir->DistanciaCentro = 0.0;
    cir->peso = 2000;
    cir->vida = cir->peso;
    cir->dano = 1.0;
    cir->adubagem = 0.0;
    return (Circulo)cir;
}

double GetCircleRaio (Circulo cir) {

    return ((CirculoImpl*)cir)->r;
}

char* GetCircleCorb (Circulo cir) {

    return ((CirculoImpl*)cir)->corb;
}

char* GetCircleCorp (Circulo cir) {

    return ((CirculoImpl*)cir)->corp;
}

double GetCircleArea (Circulo cir) {

    return ((CirculoImpl*)cir)->area;
}

void SetCircleCorb (Circulo cir, char* corb) {

    CirculoImpl* c = (CirculoImpl*)cir;

    c->corb = corb;
}

void SetCircleCorp (Circulo cir, char* corp) {

    CirculoImpl* c = (CirculoImpl*)cir;

    c->corp = corp;
}