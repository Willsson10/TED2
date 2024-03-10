#include "path.h"

void PassaArgumentos (char** PathSaida, char** PathEntrada, char** NomeGeo, char** NomeQry, int* Ns, double* Fd, int argc, char** argv) {

    for (int i=1; i<argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && (i+1) < argc) *PathEntrada = argv[++i];
        else if (strcmp(argv[i], "-o") == 0 && (i+1) < argc) *PathSaida = argv[++i];
        else if (strcmp(argv[i], "-f") == 0 && (i+1) < argc) *NomeGeo = argv[++i];
        else if (strcmp(argv[i], "-q") == 0 && (i+1) < argc) *NomeQry = argv[++i];
        else if (strcmp(argv[i], "-ns") == 0 && (i+1) < argc) *Ns = atoi(argv[++i]);
        else if (strcmp(argv[i], "-fd") == 0 && (i+1) < argc) *Fd = strtod(argv[++i], NULL)/100; 
    }
}

char* CriaNomeArq (char* NomeGeo, char* NomeQry) {

    char* nome = calloc(strlen(NomeGeo)+5+strlen(NomeQry),sizeof(char));
    strcpy(nome,NomeGeo);
    strtok(nome,".");

    if (strcmp(NomeQry, "") == 0) return nome;
    
    strcat(nome,"-");
    char* Qry = calloc(strlen(NomeQry)+1,sizeof(char));
    strcpy(Qry,NomeQry);
    strtok(Qry,".");
    strcat(nome,Qry);

    return nome;
}

char* ConcatenaPath (char* Path, char* nome) {

    char* aux = calloc(strlen(Path) + strlen(nome) + 5, sizeof(char));
    strcpy(aux, Path); //Copiando path para aux
    strcat(aux, nome); //Copiando nome para aux

    return aux;
}