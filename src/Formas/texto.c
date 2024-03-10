#include "texto.h"

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
    char corb[50];
    char corp[50];
    char* ancora;
    char conteudo[50];
    char family[50];
    char weight[50];
    char size[50];
} TextoImpl;

void SetPeso (void* item, double i) {

    TextoImpl* tex = (TextoImpl*)item;

    tex->peso = i;
}

Texto InicializaTexto (int id, double x, double y, char* corb, char* corp, char* ancora, char* conteudo) {

    TextoImpl* tex = (TextoImpl*)malloc(sizeof(TextoImpl));
    tex->id = id;
    tex->tipo = 4;
    tex->x = x;
    tex->y = y;
    strncpy(tex->corb, corb, 50);
    strncpy(tex->corp, corp, 50);
    tex->ancora = ancora;
    strncpy(tex->conteudo, conteudo, 50);
    strncpy(tex->family, "sans (sans-serif)", 50);
    strncpy(tex->weight, "normal", 50);
    strncpy(tex->size, "16px", 50);
    tex->DistanciaCentro = 0.0;
    if (strcmp(tex->conteudo, "@") == 0) tex->peso = 200.0;
    else if (strcmp(tex->conteudo, "%") == 0) tex->peso = 70.0;
    else if (strcmp(tex->conteudo, "*") == 0) tex->peso = 20.0;
    else tex->peso = 15.0;
    tex->vida = tex->peso;
    tex->dano = 1.0;
    tex->adubagem = 0.0;
    return (Texto)tex;
}

char* GetTextCorb (Texto tex) {

    return ((TextoImpl*)tex)->corb;
}

char* GetTextCorp (Texto tex) {

    return ((TextoImpl*)tex)->corp;
}

char* GetTextAncora (Texto tex) {

    char* aux = ((TextoImpl*)tex)->ancora;
    if (strcmp(((TextoImpl*)tex)->ancora, "i") == 0) aux = "start";
    else if (strcmp(((TextoImpl*)tex)->ancora, "m") == 0) aux = "middle";
    else if (strcmp(((TextoImpl*)tex)->ancora, "f") == 0) aux = "end";
    return aux;
}

char* GetTextContents (Texto tex) {

    return ((TextoImpl*)tex)->conteudo;
}

char* GetTextFamily (Texto tex) {

    return ((TextoImpl*)tex)->family;
}

char* GetTextWeight (Texto tex) {

    return ((TextoImpl*)tex)->weight;
}

char* GetTextSize (Texto tex) {

    return ((TextoImpl*)tex)->size;
}

void SetTextCorb (Texto tex, char* corb) {

    strncpy(((TextoImpl*)tex)->corb, corb, 50);
}

void SetTextCorp (Texto tex, char* corp) {

    strncpy(((TextoImpl*)tex)->corp, corp, 50);
}

void SetTextContents (Texto tex, char* conteudo) {

    strncpy(((TextoImpl*)tex)->conteudo, conteudo, 50);
}

void SetTextStyle (Texto tex, char* family, char* weight, char* size) {

    strncpy(((TextoImpl*)tex)->family, family, 50);
    strncpy(((TextoImpl*)tex)->size, size, 50);

    if (strcmp(weight, "n") == 0) strncpy(((TextoImpl*)tex)->weight, "normal", 50);
    else if (strcmp(weight, "b") == 0) strncpy(((TextoImpl*)tex)->weight, "bold", 50);
    else if (strcmp(weight, "b+") == 0) strncpy(((TextoImpl*)tex)->weight, "bolder", 50);
    else if (strcmp(weight, "l") == 0) strncpy(((TextoImpl*)tex)->weight, "lighter", 50);
}