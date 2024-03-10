#include "ordenacao.h"

double DistEntrePontos (double x1, double y1, double x2, double y2) {

    return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

int PontoNoSetor(int n, double x, double y, double a, double b) {

    double anguloSetor = 2 * pi / n; // Ângulo do setor circular em radianos

    // Calcula o ângulo do ponto (a, b) em relação ao ponto central (x, y)
    double anguloPonto = atan2(b - y, a - x);
    if (anguloPonto < 0) {
        anguloPonto += 2 * pi; // Ajusta o ângulo para o intervalo [0, 2pi)
    }

    // Calcula o índice do setor em que o ponto está
    int indiceSetor = (int) (anguloPonto / anguloSetor);
    return indiceSetor;
}

void PreencherSetores(int s, double x1, double y1, double x2, double y2, double a, double b, int vetor[]) {
    
    if (GetPontoDentroRetangulo(a, b, x1, y1, x2, y2)) for (int i=0; i<s; i++) vetor[i] = 1;

    else if (y2 <= b) {
        if (x1 >= a) for (int i=PontoNoSetor(s, a, b, x1, y1); i<=PontoNoSetor(s, a, b, x2, y2); i++) vetor[i] = 1;
        else if (x2 <= a) for (int i=PontoNoSetor(s, a, b, x1, y2); i<=PontoNoSetor(s, a, b, x2, y1); i++) vetor[i] = 1;
        else for (int i=PontoNoSetor(s, a, b, x1, y2); i<=PontoNoSetor(s, a, b, x2, y2)+1; i++) vetor[i] = 1;
    }

    else if (y1 >= b) {
        if (x1 >= a) for (int i=PontoNoSetor(s, a, b, x2, y1); i<=PontoNoSetor(s, a, b, x1, y2); i++) vetor[i] = 1;
        if (x2 <= a) for (int i=PontoNoSetor(s, a, b, x2, y2); i<=PontoNoSetor(s, a, b, x1, y1); i++) vetor[i] = 1;
        else for (int i=PontoNoSetor(s, a, b, x2, y1); i<=PontoNoSetor(s, a, b, x1, y1); i++) vetor[i] = 1;
    }

    else if (x2 <= a) for (int i=PontoNoSetor(s, a, b, x2, y2); i<=PontoNoSetor(s, a, b, x2, y1); i++) vetor[i] = 1;

    else {
        for (int i=0; i<=PontoNoSetor(s, a, b, x1, y1); i++) vetor[i] = 1;
        for (int i=PontoNoSetor(s, a, b, x1, y2); i<s; i++) vetor[i] = 1;
    }
}

bool ConfereSetorDoRetangulo (int s, int n, double x1, double y1, double x2, double y2, double a, double b) {

    int vetor[n];
    for (int i=0; i<n; i++) vetor[i] = 0;
    PreencherSetores(n, x1, y1, x2, y2, a, b, vetor);

    for (int i=0; i<n; i++) {
        if (vetor[i] == 1 && s == i) return true; //Conferindo se o retangulo (x1, y1) (x2, y2) esta no setor s
    }

    return false;
}

bool GetPontoDentroRetangulo (double a, double b, double x1, double y1, double x2, double y2) {

    if (x1 > x2) {
        double aux = x1;
        x1 = x2;
        x2 = aux;
    }
    if (y1 > y2) {
        double aux = y1;
        y1 = y2;
        y2 = aux;
    }

    if (a < x1 || a > x2 || b < y1 || b > y2) return false;
    else return true; 
}

bool GetInfoDentroRetangulo (Info i, double x1, double y1, double x2, double y2) {

    if (GetType(i) == 1) { //Confere se um circulo esta inteiramente dentro de um retangulo
        if (GetX(i) - GetCircleRaio(i) >= x1 && GetX(i) + GetCircleRaio(i) <= x2 &&
            GetY(i) - GetCircleRaio(i) >= y1 && GetY(i) + GetCircleRaio(i) <= y2) return true;
        else return false;
    }
    else if (GetType(i) == 2) { //Confere se uma linha esta inteiramente dentro de um retangulo
        if (GetPontoDentroRetangulo(GetX(i), GetY(i), x1, y1, x2, y2) && 
                                    GetPontoDentroRetangulo(GetLineX2(i), GetLineY2(i), x1, y1, x2, y2)) return true;
        else return false;
    }
    else if (GetType(i) == 3) { //Confere se um retangulo esta inteiramente dentro de um retangulo
        if (IsColheitadera(i)) return false;
        if ((GetX(i) >= x1 && GetX(i) + GetRectangleWidth(i) <= x2 && GetY(i) >= y1 && GetY(i) + GetRectangleHeight(i) <= y2) && !IsColheitadera(i)) return true;
        else return false;
    }
    else if (GetType(i) == 4) { //Confere se um ponto esta inteiramente dentro de um retangulo
        return GetPontoDentroRetangulo(GetX(i), GetY(i), x1, y1, x2, y2);
    }
}

bool GetPontoDentroInfo (Info i, double x, double y) {

    if (GetType(i) == 1) { //Confere se o ponto (x ,y) esta dentro de um circulo
        if (DistEntrePontos(x, y, GetX(i), GetY(i)) <= GetCircleRaio(i)) return true;
        else return false;
    }
    else if (GetType(i) == 2) { //Confere se o ponto (x ,y) esta sobre uma linha
        if (DistEntrePontos(x, y, GetX(i), GetY(i)) + DistEntrePontos(x, y, GetLineX2(i), GetLineY2(i)) == GetLineLength(i)) return true;
        else return false;
    }
    //Confere se o ponto (x, y) esta dentro de um retangulo
    else if (GetType(i) == 3) return GetPontoDentroRetangulo(x, y, GetX(i), GetY(i), 
                                        GetX(i) + GetRectangleWidth(i), GetY(i) + GetRectangleHeight(i));
    else if (GetType(i) == 4) { //Confere se as coordenadas de dois pontos sao muito proximas
        if (fabs(x - GetX(i) < 0.0000001 && fabs(y - GetY(i) < 0.0000001))) return true;
        else return false;
    }
}

void CentroFicticio (RadialTree t, double centro[]) {

    double retangulo[4] = {0, 0, 0, 0};
    visitaProfundidadeRadialT(t, DelimitaRetangulo, retangulo); //Delimitando o retangulo

    centro[0] = retangulo[2] - (retangulo[2] - retangulo[0])/2; //Definindo a x do centro
    centro[1] = retangulo[3] - (retangulo[3] - retangulo[1])/2; //Defininfo o y do centro

}

void DelimitaRetangulo (Info i, double x, double y, void* aux) {

    double* vetor = (double*)aux;
    //Definindo os pontos extremos de um retangulo, o qual cobre toda uma arvore radial
    if (x < vetor[0]) vetor[0] = x; //x mais a esquerda
    if (y > vetor[1]) vetor[1] = y; //y mais "alto"
    if (x > vetor[2]) vetor[2] = x; //x mais a direita
    if (y < vetor[3]) vetor[3] = y; //y mais "baixo"
}

void AtualizaDistancia (Info i, double x, double y, void* aux) {

    double* vetor = (double*)aux;
    /*Atualizo a distancia entre uma informacao i e o centro ficticio de um retangulo que "cobre"
    //uma arvore radial*/
    SetDistanciaCentro(i, DistEntrePontos(x, y, vetor[0], vetor[1])); 
}

void NoParaLista (Info i, double x, double y, void* aux) {

    insertLst(aux, i);
}

void AdicionarNoAoVetor(RadialTree t, void* aux) {
    
    Info* vetor = (Info*)aux;
    Lista lista = createLst(-1);
    visitaProfundidadeRadialT(t, NoParaLista, lista);
    int TamanhoVetor = lengthLst(lista);

    Iterador iter = createIterador(lista, false);
    Info item;

    for (int i=0; i<TamanhoVetor; i++) {
        item = getIteratorNext(lista, iter);
        vetor[i] = item;
    }
}

int OrdenaDistancia (const void* Ponto1, const void* Ponto2) {

    if (GetDistanciaCentro((Info*)Ponto1) == GetDistanciaCentro((Info*)Ponto2)) return 0;
    else if (GetDistanciaCentro((Info*)Ponto1) > GetDistanciaCentro((Info*)Ponto2)) return 1;
    else return -1;
}

RadialTree ReorganizaArvore (RadialTree t, int TamanhoVetor, int setores, double fd) {

    double centro[2];
    CentroFicticio(t, centro); //Definindo centro ficticio do retangulo
    visitaProfundidadeRadialT(t, AtualizaDistancia, centro); //Definindo/Atualizando a distancia entre os nos e esse ponto

    Info VetorArvore[TamanhoVetor]; //Vetor o qual vai armazenar as informacoes da arvore 
    AdicionarNoAoVetor(t, VetorArvore);
    qsort(VetorArvore, TamanhoVetor, sizeof(Info), OrdenaDistancia); //Ordenando o vetor com base na funcao OrdenaDistancia

    RadialTree ArvoreAux = newRadialTree(setores, fd); //Criando arvore auxiliar
    for (int i=0; i < TamanhoVetor; i++) {
        Info informacao = VetorArvore[i];
        insertRadialT(ArvoreAux, GetX(informacao), GetY(informacao), informacao); //Preenchendo arvore auxiliar
    }

    return ArvoreAux;
}
