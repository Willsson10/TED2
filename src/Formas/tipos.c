#include "tipos.h"

typedef struct{
    int id;
    int tipo;
    double x;
    double y;
    double vida;
    double DistanciaCentro;
    double peso;
    double dano;
    double adubagem;
}FormaGenericaImpl;

int GetID (void* item) {

    return ((FormaGenericaImpl*)item)->id;
}

int GetType (void* item) {

    return ((FormaGenericaImpl*)item)->tipo;
}

double GetX (void* item) {

    return ((FormaGenericaImpl*)item)->x;
}

double GetY (void* item) {

    return ((FormaGenericaImpl*)item)->y;
}

double GetLife (void* item) {

    return ((FormaGenericaImpl*)item)->vida;
}

double GetDistanciaCentro (void* item) {

    return ((FormaGenericaImpl*)item)->DistanciaCentro;
}

double GetPeso (void* item) {

    return ((FormaGenericaImpl*)item)->peso;
}

double GetDano (void* item) {

    return ((FormaGenericaImpl*)item)->dano;
}

double GetAdubagem (void* item) {
    
    return ((FormaGenericaImpl*)item)->adubagem;
}

void SetX (void* item, double x) {

    FormaGenericaImpl* i = (FormaGenericaImpl*)item;

    i->x = x;
}

void SetY (void* item, double y) {

    FormaGenericaImpl* i = (FormaGenericaImpl*)item;

    i->y = y;
}

void SetLife (void* item) {

    FormaGenericaImpl* i = (FormaGenericaImpl*)item;

    i->vida = GetPeso(i) * GetDano(i) * (1 + 0.1 * (int)(GetAdubagem(i) + 0.0000001)); 
}

void SetDistanciaCentro (void* item, double DistanciaCentro) {

    FormaGenericaImpl* i = (FormaGenericaImpl*)item;

    i->DistanciaCentro = DistanciaCentro;
}

void SetDano (void* item, double dano) {

    FormaGenericaImpl* i = (FormaGenericaImpl*)item;

    i->dano = i->dano + dano;
    if (i->dano > 1) i->dano = 1;
}

void SetAdubagem (void* item, double adubagem) {

    FormaGenericaImpl* i = (FormaGenericaImpl*)item;

    i->adubagem = i->adubagem + adubagem;
}