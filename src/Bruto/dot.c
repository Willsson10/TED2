#include "dot.h"

void InicioDot (char* fn) {

    FILE* dot = fopen(fn, "w");

    fprintf(dot, "digraph RadialTree {\n\trankdir=LR;\n\n");
    
    fclose(dot);
}

void FimDot (char* fn) {

    FILE* dot = fopen(fn, "a+");

    fprintf(dot, "}");

    fclose(dot);
}