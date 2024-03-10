#include "leitura.h"

#define LIMITE 65536

char** ler_linha(FILE* arq) {
    char linha[LIMITE];
    if (fgets(linha, LIMITE, arq) == NULL) return NULL;  // Verifica se chegou ao final do arquivo

    linha[strcspn(linha, "\n")] = '\0'; // Remove o '\n' da linha, se houver

    int i = 0;
    char** palavras = NULL;
    for (char* token = strtok(linha, " \t"); token != NULL; token = strtok(NULL, " \t")) {
        int length = strlen(token);
        while (length > 0 && (token[length - 1] == '\n' || token[length - 1] == '\t' || token[length - 1] == '\r')) {
            token[--length] = '\0';
        }

        int word_length = strlen(token);
        palavras = realloc(palavras, (i + 1) * sizeof(char*));
        palavras[i] = malloc((word_length + 1) * sizeof(char)); // Aloca memória para a palavra
        strcpy(palavras[i], token); // Copia a palavra para a posição correta do array
        i++;
    }
    if (i == 0) return NULL;  // Retorna NULL se a linha está vazia

    return palavras;
}

void LerGeo (FILE* geo, RadialTree arvore) {

    if (geo == NULL) return;
    else {
        char** aux;
        char family[50] = "sans (sans-serif)";
        char weight[50] = "normal";
        char size[50] = "16px";
        while (!feof(geo)) {
            aux = ler_linha(geo);
            if (aux == NULL) break;

            Interpreta_GEO(aux, family, weight, size, arvore);
        }
    }
    fclose(geo);
}

void LerQry (RadialTree arvore, FILE* qry, FILE* svg, FILE* txt) {

    if (qry == NULL) return;
    else {
        char** aux;
        Lista ColheitaGeral = createLst(-1);
        while (!feof(qry)) {
            aux = ler_linha(qry);
            if (aux == NULL) break;

            if (strcmp(aux[0], "cl") == 0) Funcao_cl(arvore, aux); //Realiza o comando "cl" do .qry
            else if (strcmp(aux[0], "hvt") == 0) Funcao_hvt(arvore, aux, txt, svg, ColheitaGeral); //Realiza o comando "hvt" do .qry
            else if (strcmp(aux[0], "mv") == 0) Funcao_mv(arvore, aux, txt); //Realiza o comando "mv" do .qry
            else if (strcmp(aux[0], "ct") == 0) Funcoes_ct_cr_ad(arvore, aux, txt, svg); //Realiza o comando "ct" do .qry
            else if (strcmp(aux[0], "cr") == 0) Funcoes_ct_cr_ad(arvore, aux, txt, svg); //Realiza o comando "cr" do .qry
            else if (strcmp(aux[0], "ad") == 0) Funcoes_ct_cr_ad(arvore, aux, txt, svg); //Realiza o comando "ad" do .qry
            else if (strcmp(aux[0], "st") == 0) Funcao_st(arvore, aux, txt, svg); //Realiza o comando "st" do .qry
            else if (strcmp(aux[0], "d?") == 0) Funcao_d(arvore, aux, txt); //Realiza o comando "d?" do .qry
            else if (strcmp(aux[0], "c?") == 0) Funcao_c(arvore, aux, txt); //Realiza o comando "c?" do .qry
        }

        ContabilidadeTotal(arvore, ColheitaGeral, txt); //Escrevendo a colheita total de elementos colhidos e nao colhidos
    }
}