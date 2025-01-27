
//complexMain.c

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "complex.h"
#define LEN 200

int main() {
    char line[LEN];
    stack my_stack;
    double w;
    initStack(&my_stack);
    printf(
        "+, -, *, /,: 演算, d: ドロップ, e: 終了, 数値: "
        "スタックにプッシュ\n"
        "Cコンデンサの値: -1/ωC を代入, Lコイルの値: ωL を代入, wをωに設定\n");

    while (1) {
        printf("\nInput value or operator: ");
        fgets(line, LEN, stdin);
        if (!strcmp(line, "e\n")) {
            printf("終了します\n");
            break;
        } else if (strcmp(line, "+\n") == 0) {  
            addStack(&my_stack);
        } else if (strcmp(line, "-\n") == 0) {
            subStack(&my_stack);
        } else if (strcmp(line, "*\n") == 0) {
            mulStack(&my_stack);
        } else if (strcmp(line, "/\n") == 0) {
            divStack(&my_stack);
        } else if (strcmp(line, "//\n") == 0) {
            parallelStack(&my_stack);
        } else if (strcmp(line, "d\n") == 0) {
            printComp(pullStack(&my_stack));
            printf("をドロップしました\n\n");
        } else if (strcmp(line, "w\n") == 0) {
            w = pullStack(&my_stack).real;
            printf("ωを %g に設定しました\n\n", w);
        } else if (line[0] == 'C') {
            double c = atofX(line + 1);
            pushStack(&my_stack, makeComp(0.0, -1.0 / (w * c)));
        } else if (line[0] == 'L') {
            double l = atofX(line + 1);
            pushStack(&my_stack, makeComp(0.0, w * l));
        } else if (strcmp(line, "Z\n") == 0) {
            pushStack(&my_stack, makeComp(getR(pullStack(&my_stack)), 0.0));
        } else {
            pushStack(&my_stack, atoc(line));
        }

        printStack(&my_stack);
    }
    return 0;
}
