#include "funcoes.h"

Info BuscaPorID (RadialTree t, int id) {

    Lista lista = createLst(-1);
    Circulo qualquer = InicializaCirculo(id, 0, 0, 0, "0", "0");
    insertLst(lista, qualquer);

    visitaProfundidadeRadialT(t, ConfereID, lista);
    Info item = getLst(lista, getLastLst(lista));

    return item; //Retorna a informacao de id igual a id
}

void ConfereID (Info i, double x, double y, void* aux) {

    Lista* lista = (Lista*)aux;
    if (GetID(i) == GetID(getLst(lista, getFirstLst(lista)))) insertLst(lista, i);
}

Info CriaCopia (Info item, double dx, double dy) {

    if (GetType(item) == 1) { //Caso seja um circulo
        Circulo cir = InicializaCirculo(GetID(item), GetX(item) + dx, GetY(item) + dy,
                                        GetCircleRaio(item),GetCircleCorb(item), GetCircleCorp(item));
        return cir;
    }
    else if (GetType(item) == 2) { //Caso seja uma linha
        Linha lin = InicializaLinha(GetID(item), GetX(item) + dx, GetY(item) + dy,
                                    GetLineX2(item) + dx, GetLineY2(item) + dy, GetLineCor(item));
        return lin;
    }
    else if (GetType(item) == 3) { //Caso seja um retangulo
        Retangulo ret = InicializaRetangulo(GetID(item), GetX(item) + dx, GetY(item) + dy,
                                            GetRectangleWidth(item), GetRectangleHeight(item),GetRectangleCorb(item), GetRectangleCorp(item));
        if (IsColheitadera(item)) { //Caso seja uma colheitadera
            SetColheitadera(ret, true); 
            SetContador(ret, GetColheitaderaContador(item));
            SetColhidos(ret, NULL, GetColheitadeColhidos(item));
        }
        return ret;
    }
    else if (GetType(item) == 4) { //Caso seja um texto
        Texto tex = InicializaTexto(GetID(item), GetX(item) + dx, GetY(item) + dy,
                                    GetTextCorb(item), GetTextCorp(item),GetTextAncora(item), GetTextContents(item));
        return tex;
    }
}

void ProcuraColheitadera (Info i, double x, double y, void* aux) {
    
    if (GetType(i) != 3) return;
    if (IsColheitadera(i)) insertLst(aux, i); //Inserindo informacoes que sejam consideradas colheitaderas
}

void EliminaColheita (Info item, RadialTree t, void* aux) {

    if (getNodeRadialT(t, GetX(item), GetY(item), 0.0000001) == NULL && !IsColheitadera(item)) return;
    removeNoRadialT(t, getNodeRadialT(t, GetX(item), GetY(item), 0.0000001)); 
}

Lista DelimitaGoticulas (double x, double y, double w, double h, double r) {

    Lista Goticulas = createLst(-1); //Criando lista que ira armazenar as goticulas

    int quantidade = (int)(h / (2*r));
    int atualizaY = (-1);

    //Laco para determinar a posicao de cada goticula dentro do retangulo
    for (int i=0; i < quantidade; i++) {
        atualizaY = atualizaY + 2;
        int atualizaX = 1;

        double Xc = x + atualizaX * r;
        double Yc = y + atualizaY * r;
        while (Xc < (x + w)) {
            Circulo cir = InicializaCirculo((-1), Xc, Yc, r, "none", "none"); //Inserindo goticulas na lista
            insertLst(Goticulas, cir);
            atualizaX = atualizaX + 2;
            Xc = x + atualizaX * r;
        }
    }

    return Goticulas; //Retornando lista com todas as goticulas dentro do retangulo

}

bool ConfereCirculoNaInformacao (Info i, double x, double y, double r) {

    if (GetType(i) == 1) { //Conferindo se um circulo esta inteiramente dentro de outro circulo e vice versa
        if ((DistEntrePontos(x, y, GetX(i), GetY(i)) + r) <= GetCircleRaio(i)) return true;
        else if ((DistEntrePontos(x, y, GetX(i), GetY(i)) + GetCircleRaio(i)) <= r) return true;
        else return false;
    }
    else if (GetType(i) == 2) { //Conferindo se uma linha esta inteiramente dentro de um circulo
        if (DistEntrePontos(x, y, GetX(i), GetY(i)) <= GetCircleRaio(i) &&
            DistEntrePontos(x, y, GetLineX2(i), GetLineY2(i)) <= r) return true;
        else return false;
    }
    else if (GetType(i) == 3) { //Conferindo se um circulo esta inteiramente dentro de um retangulo e vice versa
        if (IsColheitadera(i)) return false;
        else if ((x - r) >= GetX(i) && (x + r) >= GetX(i) + GetRectangleWidth(i) && (y - r) >= GetY(i) && (y + r) <= GetY(i) + GetRectangleHeight(i)) return true;
        else if (DistEntrePontos(x, y, GetX(i), GetY(i)) < r && DistEntrePontos(x, y, GetX(i) + GetRectangleWidth(i), GetY(i)) < r && 
                DistEntrePontos(x, y, GetX(i), GetY(i) + GetRectangleHeight(i)) < r && 
                DistEntrePontos(x, y, GetX(i) + GetRectangleWidth(i), GetY(i) + GetRectangleHeight(i)) < r) return true;
        else return false;
    }
    else if (GetType(i) == 4) { //Conferidno se um ponto esta dentro de um circulo
        if (DistEntrePontos(x, y, GetX(i), GetY(i)) < r) return true;
        else return false;
    }
}

void CausaDanoInfos (Item item, RadialTree t, void* aux) {

    char** comando = (char**)aux;
    double areaGoticula = pi * strtod(comando[5], NULL);
    double dano;

    //Definindo os valor do dano/cura causado(a)
    if (GetType(item) == 1) dano = areaGoticula/GetCircleArea(item);
    else if (GetType(item) == 2 || GetType(item) == 4) dano = 0.1;
    else if (GetType(item) == 4) dano = areaGoticula/GetRectangleArea(item);

    if (getNodeRadialT(t, GetX(item), GetY(item), 0.0000001) == NULL) return;
    Info info = getInfoRadialT(t, getNodeRadialT(t, GetX(item), GetY(item), 0.0000001));

    //Atualizando o dano
    if (strcmp(comando[0], "ct") == 0) SetDano(info, dano * (-1));
    else if (strcmp(comando[0], "cr") == 0) SetDano(info, dano);
    else if (strcmp(comando[0], "ad") == 0) SetAdubagem(info, dano);

    SetLife(info); //Atualizando a vida
    //Removendo caso ja tenha sido muito destruido
    if (GetLife(info)/GetPeso(info) < 0.25) removeNoRadialT(t, getNodeRadialT(t, GetX(info), GetY(info), 0.0000001));
}

void ComparaListas (Item item, Lista lista, void* aux) {

    fold(lista, ComparaInformacoes, item, aux);
}

void ComparaInformacoes (Item item, Item circulo, void* aux) {

    if (ConfereCirculoNaInformacao(item, GetX(circulo), GetY(circulo), GetCircleRaio(circulo))) insertLst(aux, item);
}

void MarcaXSvg (Item item, void* svg, void* aux) {

    if (GetLife(item)/GetPeso(item) < 0.25) fprintf (svg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"red\" stroke=\"red\" >x</text>",
                                                    GetX(item), GetY(item));
}

void ContaHortalicas (Item item, void* vetor, void* aux) {

    int* quantidade = (int*)vetor;

    //Atualizo a quantidade de uma horatalica especifica
    if (GetType(item) == 4) {
       if (strcmp(GetTextContents(item), "@") == 0) quantidade[0]++;
       else if (strcmp(GetTextContents(item), "%") == 0) quantidade[1]++;
       else if (strcmp(GetTextContents(item), "*") == 0) quantidade[2]++;
       else quantidade[5]++;
       return;
    }
    else if (GetType(item) == 1) quantidade[3]++;
    else if (GetType(item) == 3 && !IsColheitadera(item)) quantidade[4]++;
    else if (GetType(item) == 2) quantidade[6]++;
    return;
}

void GeraCopiasSementes (Lista lista, Lista Infos, int vetor[], int* j, double fd) {

    Info item;
    double raio, widht, height;
    double comprimento = 0;
    Iterador iter = createIterador(Infos, false);
    Item elem;

    //Descobrindo raio das circunferencias e largura e altura de retangulos, a serem gerados copias
    for (int i=0; i<lengthLst(Infos); i++) {
        elem = getIteratorNext(Infos, iter);
        if (GetType(elem) == 1) raio = GetCircleRaio(elem);
        if (GetType(elem) == 2) {
            if (GetLineLength(elem) > comprimento) comprimento = GetLineLength(elem);
        }
        else if (GetType(elem) == 3) {
            widht = GetRectangleWidth(elem);
            height = GetRectangleHeight(elem);
        }
    }

    for (int i=0; i<7; i++) vetor[i] = vetor[i] * fd; //Sabendo a quantidade de copias a serem geradas
    for (int i=0; i<7; i++) {
        for (int k=0; k<vetor[i]; k++) {
            if (i == 0) item = InicializaTexto(*j, 0, 0, "none", "#6600FF", "m", "@");
            else if (i == 1) item = InicializaTexto(*j, 0, 0, "none", "#D4AA00", "m", "%");
            else if (i == 2) item = InicializaTexto(*j, 0, 0, "none", "#FFAAEE", "m", "*");
            else if (i == 3) item = InicializaCirculo(*j, 0, 0, raio, "#803300", "#FF6600");
            else if (i == 4) item = InicializaRetangulo(*j, 0, 0, widht, height, "#447821", "#71C837");
            else if (i == 5) item = InicializaTexto(*j, 0, 0, "black", "black", "m", "#");
            else if (i == 6) item = InicializaLinha(*j, 0, 0, 0, comprimento, "#165016");
            (*j)++;
            insertLst(lista, item);
        }
    }
}

void EspalhaCopiasNoRetangulo (Lista copias, double x1, double y1, double x2, double y2, RadialTree t) {

    Iterador iter = createIterador(copias, false);
    Item elem;
    double x, y;
    srand((unsigned)time(NULL));

    for (int i=0; i<lengthLst(copias); i++) { //Percorrendo a lista com as copias
        elem = getIteratorNext(copias, iter);
        x = x1 + (rand() % (int)(x2 - x1)); //Gerando coordenada x aleatoria para a copia
        y = y1 + (rand() % (int)(y2 - y1)); //Gerando coordenada y aleatoria para a copia
        if (GetType(elem) == 1) {
            while (x - GetCircleRaio(elem) < x1 || x + GetCircleRaio(elem) > x2 || y - GetCircleRaio(elem) < y1 || y + GetCircleRaio(elem) > y2
                    || getNodeRadialT(t, x, y, 0.0000001) != NULL) { //Evitando que gere informacoes fora do retangulo, ou com mesmo (x, y) de outras informacoes da arvore
                x = x1 + (rand() % (int)(x2 - x1));
                y = y1 + (rand() % (int)(y2 - y1));
            }
        }
        else if (GetType(elem) == 2) {
            while (y + GetLineLength(elem) > y2 || getNodeRadialT(t, x, y, 0.0000001) != NULL) {
                x = x1 + (rand() % (int)(x2 - x1));
                y = y1 + (rand() % (int)(y2 - y1));
            }
            SetLineX2(elem, x);
            SetLineY2(elem, y + GetLineLength(elem));
        }
        else if (GetType(elem) == 3) {
            while (x < x1 || x > x2 || y < y1 || y > y2 || getNodeRadialT(t, x, y, 0.0000001) != NULL) { //Evitando que gere informacoes fora do retangulo, ou com mesmo (x, y) de outras informacoes da arvore
                x = x1 + (rand() % (int)(x2 - x1));
                y = y1 + (rand() % (int)(y2 - y1));
            }
        }
        SetX(elem, x); //Definindo x da copia
        SetY(elem, y); //Definindo y da copia
        insertRadialT(t, x, y, elem); //Inserindo copia na arvore radial t
    }
}

void Contagem (Item item, void* p, void* aux) {

    double* vetor = (double*)aux;

    if (GetType(item) == 1) vetor[0] = vetor[0] + GetLife(item); //Caso seja um circulo
    else if (GetType(item) == 2) vetor[6] = vetor[6] + GetLife(item); //Caso seja uma linha
    else if (GetType(item) == 3 && !IsColheitadera(item)) vetor[4] = vetor[4] + GetLife(item); //Caso seja um retangulo
    else if (GetType(item) == 4) {
        if (strcmp(GetTextContents(item), "@") == 0) vetor[0] = vetor[0] + GetLife(item); //Caso seja uma cebola
        else if (strcmp(GetTextContents(item), "%") == 0) vetor[1] = vetor[1] + GetLife(item); //Caso seja uma cenoura
        else if (strcmp(GetTextContents(item), "*") == 0) vetor[2] = vetor[2] + GetLife(item); //Caso seja um morango
        else vetor[5] = vetor[5] + GetLife(item); //Caso seja um mato
    }
}

void Contagem2 (Info i, double x, double y, void* aux) {

    double* vetor = (double*)aux;

    if (GetType(i) == 1) vetor[0] = vetor[0] + GetLife(i); //Caso seja um circulo
    else if (GetType(i) == 2) vetor[6] = vetor[6] + GetLife(i); //Caso seja uma linha
    else if (GetType(i) == 3 && !IsColheitadera(i)) vetor[4] = vetor[4] + GetLife(i); //Caso seja um retangulo
    else if (GetType(i) == 4) {
        if (strcmp(GetTextContents(i), "@") == 0) vetor[0] = vetor[0] + GetLife(i); //Caso seja uma cebola
        else if (strcmp(GetTextContents(i), "%") == 0) vetor[1] = vetor[1] + GetLife(i); //Caso seja uma cenoura
        else if (strcmp(GetTextContents(i), "*") == 0) vetor[2] = vetor[2] + GetLife(i); //Caso seja um morango
        else vetor[5] = vetor[5] + GetLife(i); //Caso seja um mato
    }
}

Info AndaHVT (char** aux, Info item, FILE* svg) {

    //Definindo variacao de posicao
    double dx = 0;
    double dy = 0;
    if (strcmp(aux[3], "n") == 0) dy = (atoi(aux[2]) - 1) * GetRectangleHeight(item); //Caso seja para o norte
    else if (strcmp(aux[3], "s") == 0) dy = (atoi(aux[2]) - 1) * GetRectangleHeight(item) * (-1); //Caso seja para o sul
    else if (strcmp(aux[3], "l") == 0) dx = (atoi(aux[2]) - 1) * GetRectangleWidth(item) * (-1); //Caso seja para o leste
    else if (strcmp(aux[3], "o") == 0) dx = (atoi(aux[2]) - 1) * GetRectangleWidth(item); //Caso seja para o oeste

    //"Desenhando" a decoracao que representa a area colhida
    if (strcmp(aux[3], "n") == 0 || strcmp(aux[3], "o") == 0) {
        fprintf (svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke-dasharray=\"5.5\" style=\"fill:none;stroke:red\" />",
                        GetX(item), GetY(item), GetRectangleWidth(item) + dx, GetRectangleHeight(item) + dy);
    }
    else {
        fprintf (svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke-dasharray=\"5.5\" style=\"fill:none;stroke:red\" />",
                        GetX(item) + dx, GetY(item) + dy, GetRectangleWidth(item) + dx, GetRectangleHeight(item) + dy);
    }
    
    Info copia = CriaCopia(item, dx, dy);
    return copia;
}

void ColheHVT (RadialTree arvore, char** aux, Info item, Info copia, Lista colhidos, Lista ColheitaGeral) {

    if (strcmp(aux[3], "n") == 0 || strcmp(aux[3], "o") == 0) {
        getInfosDentroRegiaoRadialT(arvore, GetX(item), GetY(item), GetX(copia) + GetRectangleWidth(copia),
                                    GetY(copia) + GetRectangleHeight(copia), GetInfoDentroRetangulo, colhidos);
        getInfosDentroRegiaoRadialT(arvore, GetX(item), GetY(item), GetX(copia) + GetRectangleWidth(copia),
                                    GetY(copia) + GetRectangleHeight(copia), GetInfoDentroRetangulo, ColheitaGeral);
    }
    else {
        getInfosDentroRegiaoRadialT(arvore, GetX(item) + GetRectangleWidth(item), GetY(item) + GetRectangleHeight(item), GetX(copia),
                                    GetY(copia), GetInfoDentroRetangulo, colhidos);
        getInfosDentroRegiaoRadialT(arvore, GetX(item) + GetRectangleWidth(item), GetY(item) + GetRectangleHeight(item), GetX(copia),
                                    GetY(copia), GetInfoDentroRetangulo, ColheitaGeral);
    }
    SetColhidos(copia, NULL, colhidos); //Atualizando os elementos colhidos pela colheitadera
    insertRadialT(arvore, GetX(copia), GetY(copia), copia); //inserindo copia na arvore radial
}