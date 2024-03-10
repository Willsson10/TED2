#include "linha.h"

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
    double x2;
    double y2;
    char* cor;
    double comprimento;
} LinhaImpl;

Linha InicializaLinha (int id, double x1, double y1, double x2, double y2, char* cor) {

    LinhaImpl* lin = (LinhaImpl*)malloc(sizeof(LinhaImpl));
    lin->id = id;
    lin->tipo = 2;
    lin->x = x1;
    lin->y = y1;
    lin->x2 = x2;
    lin->y2 = y2;
    lin->cor = cor;
    lin->comprimento = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    lin->DistanciaCentro = 0.0;
    lin->peso = 10 * lin->comprimento;
    lin->vida = lin->peso;
    lin->dano = 1.0;
    lin->adubagem = 0.0;
    return (Linha)lin;
}

double GetLineX2 (Linha lin) {

    return ((LinhaImpl*)lin)->x2;
}

double GetLineY2 (Linha lin) {

    return ((LinhaImpl*)lin)->y2;
}

char* GetLineCor (Linha lin) {

    return ((LinhaImpl*)lin)->cor;
}

double GetLineLength (Linha lin) {

    return ((LinhaImpl*)lin)->comprimento;
}

void SetLineX2 (Linha lin, double x2) {

    LinhaImpl* l = (LinhaImpl*)lin;

    l->x2 = x2;
}

void SetLineY2 (Linha lin, double y2) {

    LinhaImpl* l = (LinhaImpl*)lin;

    l->y2 = y2;
}

void SetLineCor (Linha lin, char* cor) {

    LinhaImpl* l = (LinhaImpl*)lin;

    l->cor = cor;
}