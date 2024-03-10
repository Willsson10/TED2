#include "geo_qry.h"

void Interpreta_GEO (char** aux, char family[], char weight[], char size[], RadialTree arvore) {

    if (strcmp(aux[0], "c") == 0) { //Caso seja um circulo, inicializa um circulo e insere na arvore radial
         Circulo cir = InicializaCirculo(atoi(aux[1]), strtod(aux[2], NULL), strtod(aux[3], NULL), strtod(aux[4], NULL), aux[5], aux[6]);
         insertRadialT(arvore, GetX(cir), GetY(cir), (Circulo)cir);
    }
    else if (strcmp(aux[0], "l") == 0) { //Caso seja uma linha, inicializa uma linha e insere na arvore radial
        Linha lin = InicializaLinha(atoi(aux[1]), strtod(aux[2], NULL), strtod(aux[3], NULL), strtod(aux[4], NULL), strtod(aux[5], NULL), aux[6]);
        insertRadialT(arvore, GetX(lin), GetY(lin), (Linha)lin);
    }
    else if (strcmp(aux[0], "r") == 0) { //Caso seja um retangulo, inicializa um retangulo e insere na arvore radial
        Retangulo ret = InicializaRetangulo(atoi(aux[1]), strtod(aux[2], NULL), strtod(aux[3], NULL), strtod(aux[4], NULL), strtod(aux[5], NULL), aux[6], aux[7]);
        insertRadialT(arvore, GetX(ret), GetY(ret), (Retangulo)ret);
    }
    else if (strcmp(aux[0], "t") == 0) { //Caso seja um texto, inicializa um texto e insere na arvore radial
        Texto tex = InicializaTexto(atoi(aux[1]), strtod(aux[2], NULL), strtod(aux[3], NULL), aux[4], aux[5], aux[6], aux[7]);
        SetTextStyle(tex, family, weight, size);
        insertRadialT(arvore, GetX(tex), GetY(tex), (Texto)tex);
    }
    else if (strcmp(aux[0], "ts") == 0) { //Caso seja o comando "ts", altera as especificacoes de um texto
        strncpy(family, aux[1], 50);
        strncpy(weight, aux[2], 50);
        strncpy(size, aux[3], 50);
    }
}

void Funcao_cl (RadialTree arvore, char** aux) {

    Info item = BuscaPorID(arvore, atoi(aux[1])); //Fazendo a busca por id
    SetColheitadera(item, true); //Definindo o retangulo de id aux[1] como colheitadera
}

void Funcao_hvt (RadialTree arvore, char** aux, FILE* txt, FILE* svg, Lista ColheitaGeral) {

    Info item = BuscaPorID(arvore, atoi(aux[1])); //Fazendo busca por id
    removeNoRadialT(arvore, getNodeRadialT(arvore, GetX(item), GetY(item), 0.0000001)); //removendo o no de id aux[1] da arvore

    Info copia = AndaHVT(aux, item, svg); //Realiza a "movimentacao" da colheitadera, e gera copia desta, com variacao de posicao
    Lista colhidos = createLst(-1); //Criando lista para armazenar os elementos colhidos

    ColheHVT(arvore, aux, item, copia, colhidos, ColheitaGeral); //Realiza a colheita. Preenchendo as listas colhidos e ColheitaGeral
                
    fprintf(txt, "[*] hvt %s %s %s\n\n", aux[1], aux[2], aux[3]);
    RelatorioInfo(item, txt, NULL);
    fprintf(txt, "Posicao inicial: (%lf, %lf)\nPosicao final: (%lf, %lf)\n\n", //Relatando posicao inicial e final
                        GetX(item), GetY(item), GetX(copia), GetY(copia));
                
    double pesos[7] = {0, 0, 0, 0, 0, 0, 0}; //Vetor para armazena a contabilidade parcial da colheita
    if (!isEmptyLst(colhidos)) fold(colhidos, Contagem, NULL, pesos); //Realizando a contagem parcial da colheita
    fprintf(txt, "Contabilidade parcial:\nCebola: %lf g\nCenoura: %lf g\nMorango: %lf g\nAbobora: %lf g\nRepolho: %lf g\nMato(texto): %lf g\nMato(linha): %lf g\n\n",
                    pesos[0], pesos[1], pesos[2], pesos[3], pesos[4], pesos[5], pesos[6]); //Relatando contabilidade parcial desta colheita

    fprintf(txt, "ELEMENTOS COLHIDOS:\n\n");
    if (!isEmptyLst(colhidos)) fold(colhidos, RelatorioInfo, txt, NULL); //Relatando informacoes sobre os elementos colhidos  
    
    if (!isEmptyLst(colhidos)) fold(colhidos, EliminaColheita, arvore, NULL); //Remove os elementos colhidos da arvore radials
}

void Funcao_mv (RadialTree arvore, char** aux, FILE* txt) {

    Info item = BuscaPorID(arvore, atoi(aux[1])); //Fazendo a busca por id
    removeNoRadialT(arvore, getNodeRadialT(arvore, GetX(item), GetY(item), 0.0000001)); //removendo o no de id aux[1] da arvore

    Info copia = CriaCopia(item, strtod(aux[2], NULL), strtod(aux[3], NULL)); //criando copia desse no, com variacao de posicao
    insertRadialT(arvore, GetX(copia), GetY(copia), copia); //inserindo copia na arvore radial

    fprintf(txt, "[*] mv %s %s %s\n\n", aux[1], aux[2], aux[3]);
    RelatorioInfo(item, txt, NULL); //Escrevendo relatorio geral da informacao
    fprintf(txt, "Posicao inicial: (%lf, %lf)\nPosicao final: (%lf, %lf)\n\n", //Relatando posicao inicial e final
                GetX(item), GetY(item), GetX(copia), GetY(copia));
}

void Funcoes_ct_cr_ad (RadialTree arvore, char** aux, FILE* txt, FILE* svg) {

    Lista Goticulas = createLst(-1); //Criando lista para armazenar as goticulas
    Goticulas = DelimitaGoticulas(strtod(aux[1], NULL), strtod(aux[2], NULL), strtod(aux[3], NULL), 
                                                strtod(aux[4], NULL), strtod(aux[5], NULL)); //Preenchendo lista Goticulas

    Lista Infos = createLst(-1); //Criando lista para armazenas as informacoes dentro do retangulo
    getNodesDentroRegiaoRadialT(arvore, strtod(aux[1], NULL), strtod(aux[2], NULL), strtod(aux[1], NULL) + strtod(aux[3], NULL),
                                               strtod(aux[2], NULL) + strtod(aux[4], NULL), Infos); //Preenchendo lista Infos
                
    Lista final = createLst(-1); //Criando lista para armazenar as informacoes afetadas pelas goticulas
    if (!isEmptyLst(Goticulas)) fold(Goticulas, ComparaListas, Infos, final); //Preenchendo lista final

    if (!isEmptyLst(final)) {
        fold(final, CausaDanoInfos, arvore, aux); //Causando dano nas informacoes
        fprintf (txt, "[*] %s %s %s %s %s %s\n\n", aux[0], aux[1], aux[2], aux[3], aux[4], aux[5]);
        fold (final, RelatorioInfo, txt, NULL); //Escrevendo relatorio das informacoes
    }

    if (!isEmptyLst(final)) fold(final, MarcaXSvg, svg, NULL);
    char CorCirculo[10];
    //Definindo cor do circulo no .svg, de acordo com o comando do .qry
    if (strcmp(aux[0], "cr") == 0) strncpy(CorCirculo, "red", 10);
    else if (strcmp(aux[0], "ct") == 0) strncpy(CorCirculo, "yellow", 10);
    else strncpy(CorCirculo, "green", 10);
    fprintf (svg, "\n\t<rect x=\"%s\" y=\"%s\" width=\"%s\" height=\"%s\" stroke-dasharray=\"5.5\" style=\"fill:none;stroke:red\" />",
                aux[1], aux[2], aux[3], aux[4]); //Desenhando a area onde foram "tacadas" as goticulas
    fprintf (svg, "\n\t<circle cx=\"%s\" cy=\"%s\" r=\"%s\" stroke=\"%s\" fill=\"none\" />",
                    aux[1], aux[2], aux[5], CorCirculo); //Desenhando circulo na ancora da area retangular
}

void Funcao_st (RadialTree arvore, char** aux, FILE* txt, FILE* svg) {

    Lista Infos = createLst(-1); //Criando lista para armazenar as informacoes dentro da regiao retangular
    getInfosDentroRegiaoRadialT(arvore, strtod(aux[1], NULL), strtod(aux[2], NULL), strtod(aux[1], NULL) + strtod(aux[3], NULL),
                                    strtod(aux[2], NULL) + strtod(aux[4], NULL), GetInfoDentroRetangulo, Infos); //preenchendo a lista Infos

    int Quantidade[7] = {0, 0, 0, 0, 0, 0, 0}; //Vetor para armazenar a quantidade de cada hortalica na area retangular
    if (!isEmptyLst(Infos)) fold(Infos, ContaHortalicas, Quantidade, NULL); //Contabilizando a quantidade de cada hortalica, e armazenando no vetor Quantidade
     
    Lista Copias = createLst(-1); //Criando lista para armazenar as copias geradas
    int auxiliar = atoi(aux[8]);
    int* j = &auxiliar;
    if (!isEmptyLst(Infos)) GeraCopiasSementes(Copias, Infos, Quantidade, j, strtod(aux[5], NULL)); //Gerando as copias e preenchendo a lista Copias
 
    EspalhaCopiasNoRetangulo(Copias, strtod(aux[1], NULL) + strtod(aux[6], NULL), strtod(aux[2], NULL) + strtod(aux[7], NULL), 
                            strtod(aux[1], NULL) + strtod(aux[6], NULL) + strtod(aux[3], NULL), 
                            strtod(aux[2], NULL) + strtod(aux[7], NULL) + strtod(aux[4], NULL), arvore);

    fprintf (txt, "[*] st %s %s %s %s %s %s %s %s\n\nELEMENTOS ATINGIDOS:\n\n", aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
    if (!isEmptyLst(Infos)) fold(Infos, RelatorioInfo, txt, NULL); //Relatando informacoes atingidas
    fprintf (txt, "CLONES:\n\n");
    if (!isEmptyLst(Copias)) fold(Copias, RelatorioInfo, txt, NULL); //Relatando clones

    fprintf (svg, "\n\t<rect x=\"%s\" y=\"%s\" width=\"%s\" height=\"%s\" stroke-dasharray=\"5.5\" style=\"fill:none;stroke:red\" />",
            aux[1], aux[2], aux[3], aux[4]); //Desenhando regiao atingida pelo retangulo
    fprintf (svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%s\" height=\"%s\" style=\"fill:none;stroke:red\" />",
            strtod(aux[1], NULL) + strtod(aux[6], NULL), strtod(aux[2], NULL) + strtod(aux[7], NULL), aux[3], aux[4]); //Desenhando regiao onde estarao as copias
    fprintf (svg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"7.50\" stroke=\"green\" fill=\"none\" />",
            strtod(aux[1], NULL) + strtod(aux[6], NULL), strtod(aux[2], NULL) + strtod(aux[7], NULL)); //Desenhando circulo na ancora da area retangular
}

void Funcao_d (RadialTree arvore, char** aux, FILE* txt) {

    Info item = BuscaPorID(arvore, atoi(aux[1])); //Fazendo a busca por id
    fprintf(txt, "[*] d?\n\n"); 
    RelatorioInfo(item, txt, NULL); //Escrevendo relatorio geral da informacao
}

void Funcao_c (RadialTree arvore, char** aux, FILE* txt) {

    Lista listaColheitaderas = createLst(-1); //Criando uma lista para armazenar colheitaderas
    visitaProfundidadeRadialT(arvore, ProcuraColheitadera, listaColheitaderas); //Preechendo a lista

    fprintf(txt, "[*] c?\n\n");
    fold(listaColheitaderas, RelatorioInfo, txt, NULL); //Escrevendo o relatorio de cada colheitadera
}