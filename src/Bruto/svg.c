#include "svg.h"

ArqSvg AbreSvg (char* fn) {

    FILE* svg = fopen(fn, "w");
    fprintf(svg, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<svg viewBox=\"-110 -110 6000 1800\" xmlns=\"http://www.w3.org/2000/svg\">");

    return svg;
}

void FechaSvg (FILE* svg) {

    fprintf(svg, "\n</svg>");

    fclose(svg);
}

void EscreveArvoreSvg (Info i, double x, double y, void* aux) {

    if (GetType(i) == 1) CirculoSvg(i, aux);
    else if (GetType(i) == 2) LinhaSvg(i, aux);
    else if (GetType(i) == 3) RetanguloSvg(i, aux);
    else if (GetType(i) == 4) TextoSvg(i, aux);
}

void CirculoSvg (Info i, FILE* svg) {

    fprintf (svg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\" />",
                                                 GetX(i), GetY(i), GetCircleRaio(i), GetCircleCorb(i), GetCircleCorp(i));
}

void LinhaSvg (Info i, FILE* svg) {

    fprintf (svg, "\n\t<line x1=\"%lf\" x2=\"%lf\" y1=\"%lf\" y2=\"%lf\" stroke=\"%s\" />",
                                            GetX(i), GetLineX2(i), GetY(i), GetLineY2(i), GetLineCor(i));
}

void RetanguloSvg (Info i, FILE* svg) {

    fprintf (svg, "\n\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" style=\"fill:%s;stroke:%s\" />",
                                                     GetX(i), GetY(i), GetRectangleWidth(i), GetRectangleHeight(i), GetRectangleCorp(i), GetRectangleCorb(i));
}

void TextoSvg (Info i, FILE* svg) {

    fprintf (svg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"%s\" stroke=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" text-anchor=\"%s\" >%s</text>",
                                     GetX(i), GetY(i), GetTextCorp(i), GetTextCorb(i), GetTextFamily(i), GetTextWeight(i), GetTextSize(i), GetTextAncora(i), GetTextContents(i));
}