//complex.c

#include "complex.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EN 8

complex makeComp(double real, double image) { //複素数の生成
    complex ans;
    ans.real = real;
    ans.image = image;
    return ans;
}
 
//複素数同士の四則演算
complex addComp(complex a, complex b) {
    return makeComp(a.real + b.real, a.image + b.image);
}
complex subComp(complex a, complex b) {
    return makeComp(a.real - b.real, a.image - b.image);
}
complex mulComp(complex a, complex b) {
    return makeComp(a.real * b.real - a.image * b.image,
                    a.real * b.image + a.image * b.real);
}
complex divComp(complex a, complex b) {
    return makeComp((a.real * b.real + a.image * b.image) / getR2(b),
                    (a.image * b.real - a.real * b.image) / getR2(b));
}


complex invComp(complex a) {  //逆数
     return (cmulComp(conjComp(a), 1 / getR2(a))); 
} 
complex cmulComp(complex a, double k) {  //複素数と実数の積
    return makeComp(k * a.real, k * a.image);
}
complex makeCompRT(double r, double theta) {  //極座標から複素数を生成
    return makeComp(r * cos(theta), r * sin(theta));
}
complex conjComp(complex a) {  //共役複素数
    return makeComp(a.real, -1 * a.image); 
}  


double getR2(complex a) {  //実数と虚数の2乗の和
     return a.real * a.real + a.image * a.image; 
}
double getR(complex a) {   //絶対値
    return sqrt(getR2(a)); 
}
double getTheta(complex a) {   //偏角
    return atan2(a.image, a.real); 
}
void printComp(complex a) {   //複素数の表示
    printf("%f%+fj", a.real, a.image); 
}
void printCompRT(complex a) {  //極座標表示
    printf("%f∠%f", getR(a), getTheta(a) * 180 / M_PI);
}

double atofX(char *lp) {  //文字列をdouble型に変換
    char *eßxtentions = "TGMKmunp";
    double mul[EN] = {1e12, 1e9, 1e6, 1e3, 1e-3, 1e-6, 1e-9, 1e-12};
    double m = 1.0;
    char *ep;
    int i;
    for (ep = lp; *ep != '\0'; ep++) {
        char c = *ep;
        if (!isdigit(c) && c != 'e' && c != '-' && c != '.') {
            break;
        }
    }
    for (i = 0; i < EN; i++) {
        if (*ep == eßxtentions[i]) {
            m = mul[i];
            break;
        }
    }
    return atof(lp) * m;
}

complex atoc(char *lp) {  //文字列を複素数に変換
    complex ans;
    char *cp = strchr(lp, ',');
    char *sp = strchr(lp, ';');
    if (cp != NULL) {
        return makeComp(atofX(lp), atofX(cp + 1));
    } else if (sp != NULL) {
        return makeCompRT(atofX(lp), atofX(sp + 1) * M_PI / 180);
    } else {
        return makeComp(atofX(lp), 0.0);
    }
    return ans;
}


//スタックの操作
void initStack(stack *sp) { sp->head = N; }  //スタックの初期化
complex currentStack(stack *sp) {
    return sp->head == N ? makeComp(sqrt(-1.0), sqrt(-1.0))
                         : sp->data[sp->head];
}
void pushStack(stack *sp, complex val) {  //スタックにプッシュ
    sp->head--;
    sp->data[sp->head] = val;
}
complex pullStack(stack *sp) {  //スタックからプル
    return sp->head == N ? makeComp(sqrt(-1.0), sqrt(-1.0))
                         : sp->data[sp->head++];
}
void printStack(stack *sp) {  //現在のスタックの中身を表示
    int i;
    for (i = N - 1; i >= sp->head; i--) {
        printComp(sp->data[i]);
        printf(" ( ");
        printCompRT(sp->data[i]);
        printf(" ) \n");
    }
}

//演算のスタック操作
//四則演算
void addStack(stack *sp) {
    pushStack(sp, addComp(pullStack(sp), pullStack(sp)));
}
void subStack(stack *sp) {
    complex b = pullStack(sp);
    pushStack(sp, subComp(pullStack(sp), b));
}
void mulStack(stack *sp) {
    pushStack(sp, mulComp(pullStack(sp), pullStack(sp)));
}
void divStack(stack *sp) {
    complex c = pullStack(sp);
    pushStack(sp, divComp(pullStack(sp), c));
}

void parallelStack(stack *sp) {  //並列インピーダンス
    pushStack(sp,invComp(addComp(invComp(pullStack(sp)), invComp(pullStack(sp)))));
}

void squareStack(stack *sp) {  //スタックのトップの複素数を2乗
    pushStack(sp, makeComp(getR(pullStack(sp)), 0.0));
}