#include "headers.h"

int main (int argc, char** argv) {

    char *PathEntrada, *PathSaida, *NomeGeo, *NomeQry = "";
    int NsValor; double FdValor;
    int* Ns = &NsValor;
    double* Fd = &FdValor;

    PassaArgumentos(&PathSaida, &PathEntrada, &NomeGeo, &NomeQry, Ns, Fd, argc, argv); //"Preenchendo as strings com seus diretorios"

    //Colocando '/' no final das strings que representam os diretorios de entrada e saida, caso nao a tenham
    if(PathSaida[strlen(PathSaida)-1]!='/') strcat(PathSaida,"/");
    if(PathEntrada[strlen(PathEntrada)-1]!='/') strcat(PathEntrada,"/");

    //Removendo uma '/' inicial caso haja
    char* aux = calloc(256,sizeof(char));
    if (strcmp(NomeQry, "") != 0) {
        strcpy(aux,NomeQry);
        aux = strchr(aux,'/');
        if(aux[0] == '/') memmove(aux, aux + 1, strlen(aux));
    }

    //Gerando nome padrao dos arquivos de saida
    char* NomeArq = CriaNomeArq(NomeGeo, aux);
    NomeArq = ConcatenaPath(PathSaida, NomeArq);

    NomeGeo = ConcatenaPath(PathEntrada, NomeGeo); //Gerando nome do .geo
    FILE* geo = fopen(NomeGeo, "r"); //Abrindo arquivo para leitura

    strcat(NomeArq, ".svg"); //Gerando nome do .svg
    ArqSvg svg = AbreSvg(NomeArq);
    RadialTree arvore = newRadialTree(*Ns, *Fd);
    LerGeo(geo, arvore); //Lendo .geo

    //Caso tenha arquivo .qry
    if (strcmp(NomeQry, "") != 0) {

        NomeQry = ConcatenaPath(PathEntrada, NomeQry); //Gerando nome do .qry
        FILE* qry = fopen(NomeQry, "r");

        //Gerando nome do .txt
        strtok(NomeArq, ".");
        strcat(NomeArq, ".txt");
        FILE* txt = fopen(NomeArq, "w");

        LerQry(arvore, qry, svg, txt); //Lendo o .qry
        fclose(qry);
        fclose(txt);
    }

    visitaProfundidadeRadialT(arvore, EscreveArvoreSvg, svg); //Escrevendo .svg da arvore radial
    FechaSvg(svg);

    //Gerando nome do .dot
    strtok(NomeArq, ".");
    strcat(NomeArq, ".dot");
    InicioDot(NomeArq);
    printDotRadialTree(arvore, NomeArq);
    FimDot(NomeArq);

    killRadialTree(arvore);

    return 0;
}