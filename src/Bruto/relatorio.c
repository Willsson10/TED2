#include "relatorio.h"

void RelatorioInfo (Item item, void* txt, void* aux) {
    
    if (GetType(item) == 1) RelatorioCirculo(item, txt);
    else if (GetType(item) == 2) RelatorioLinha(item, txt);
    else if (GetType(item) == 3) RelatorioRetangulo(item, txt);
    else if (GetType(item) == 4) RelatorioTexto(item, txt);  
}

void RelatorioCirculo (Info item, FILE* txt) {

    char status[10];
    double dano = GetLife(item)/GetPeso(item);

    if (dano < 0.25) strncpy(status, "morreu", 10);
    else strncpy(status, "viva", 10);

    fprintf(txt, "Abobora\nID: %d\nÂncora: (%lf, %lf)\nRaio: %lf\nCor da Borda: %s\nCor do preenchimento: %s\nArea: %lf\nPeso inicial: %lf\nPeso atual: %lf (%.2lf)\nStatus: %s\n\n",
                    GetID(item), GetX(item), GetY(item), GetCircleRaio(item), GetCircleCorb(item), GetCircleCorp(item), GetCircleArea(item), GetPeso(item), GetLife(item), dano, status);
}

void RelatorioLinha (Info item, FILE* txt) {

    char status[10];
    double dano = GetLife(item)/GetPeso(item);

    if (dano < 0.25) strncpy(status, "morreu", 10);
    else strncpy(status, "viva", 10);
    

    fprintf(txt, "Mato(linha)\nID: %d\nÂncoras: (%lf, %lf) (%lf, %lf)\nCor: %s\nComprimento: %lf\nPeso inicial: %lf\nPeso atual: %lf (%.2lf)\nStatus: %s\n\n",
                    GetID(item), GetX(item), GetY(item), GetLineX2(item), GetLineY2(item), GetLineCor(item), GetLineLength(item), GetPeso(item), GetLife(item), dano, status);
}

void RelatorioRetangulo (Info item, FILE* txt) {

    char status[10];
    double dano = GetLife(item)/GetPeso(item);

    if (dano < 0.25) strncpy(status, "morreu", 10);
    else strncpy(status, "viva", 10);

    if (IsColheitadera(item)) {
        fprintf(txt, "Colheitadera\nID: %d\nÂncora: (%lf, %lf)\nLargura: %lf\nAltura: %lf\nCor da borda: %s\nCor de preenchimento: %s\nArea: %lf\nPeso inicial: %lf\nPeso atual: %lf (%.2lf)\nStatus: %s\n\n",
                    GetID(item), GetX(item), GetY(item), GetRectangleWidth(item), GetRectangleHeight(item), GetRectangleCorb(item), GetRectangleCorp(item),
                    GetRectangleArea(item), GetPeso(item), GetLife(item), dano, status);
    }
    else {
        fprintf(txt, "Repolho\nID: %d\nÂncora: (%lf, %lf)\nLargura: %lf\nAltura: %lf\nCor da borda: %s\nCor de preenchimento: %s\nArea: %lf\nPeso inicial: %lf\nPeso atual: %lf (%.2lf)\nStatus: %s\n\n",
                        GetID(item), GetX(item), GetY(item), GetRectangleWidth(item), GetRectangleHeight(item), GetRectangleCorb(item), GetRectangleCorp(item),
                        GetRectangleArea(item), GetPeso(item), GetLife(item), dano, status);
    }

}

void RelatorioTexto (Info item, FILE* txt) {

    char hortalica[20];
    char status[10];
    double dano = GetLife(item)/GetPeso(item);

    if (dano < 0.25) strncpy(status, "morreu", 10);
    else strncpy(status, "viva", 10);

    if (strcmp(GetTextContents(item), "@") == 0) strncpy(hortalica, "Cebola", 20);
    else if (strcmp(GetTextContents(item), "%") == 0) strncpy(hortalica, "Cenoura", 20);
    else if (strcmp(GetTextContents(item), "*") == 0) strncpy(hortalica, "Morango", 20);
    else strncpy(hortalica, "Mato(texto)", 20);

    fprintf(txt, "%s\nID: %d\nÂncora: (%lf, %lf)\nCor da borda: %s\nCor de preenchimento: %s\nConteudo: %s\nPeso inicial: %lf\nPeso atual: %lf (%.2lf)\nStatus: %s\n\n",
                    hortalica, GetID(item), GetX(item), GetY(item), GetTextCorb(item), GetTextCorp(item), GetTextContents(item), GetPeso(item), GetLife(item), dano, status);
}

void ContabilidadeTotal (RadialTree arvore, Lista ColheitaGeral, FILE* txt) {

    double pesos[7] = {0, 0, 0, 0, 0, 0, 0}; //Vetor para armazena a contabilidade total das colheitas
    if (!isEmptyLst(ColheitaGeral)) fold(ColheitaGeral, Contagem, NULL, pesos); //Realizando a contagem geral das colheitas
    fprintf(txt, "Contabilidade total (Colhidos):\nCebola: %lf g\nCenoura: %lf g\nMorango: %lf g\nAbobora: %lf g\nRepolho: %lf g\nMato(texto): %lf g\nMato(linha): %lf g\n\n",
                pesos[0], pesos[1], pesos[2], pesos[3], pesos[4], pesos[5], pesos[6]); //Relatando contabilidade total das colheitas
    for (int i=0; i<7; i++) pesos[i] = 0;
    visitaProfundidadeRadialT(arvore, Contagem2, pesos);
    fprintf(txt, "Contabilidade total (Nao colhidos):\nCebola: %lf g\nCenoura: %lf g\nMorango: %lf g\nAbobora: %lf g\nRepolho: %lf g\nMato(texto): %lf g\nMato(linha): %lf g\n\n",
                pesos[0], pesos[1], pesos[2], pesos[3], pesos[4], pesos[5], pesos[6]); //Relatando elementos que nao foram colhidos
}