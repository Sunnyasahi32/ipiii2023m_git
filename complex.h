//complex.h

#ifndef __COMPLEX_H__
#define __COMPLEX_H__
#define N 10000

typedef struct {
    double real;
    double image;
} complex;

typedef struct {
    complex data[N];
    int head;
} stack;

complex makeComp(double real, double image);
complex addComp(complex a, complex b);
complex subComp(complex a, complex b);
complex mulComp(complex a, complex b);
complex divComp(complex a, complex b);
complex invComp(complex a);
complex cmulComp(complex a, double k);
complex makeCompRT(double r, double theta);
complex conjComp(complex a);
double getR2(complex a);
double getR(complex a);
double getTheta(complex a);
void printComp(complex a);
void printCompRT(complex a);
double atofX(char *lp);
complex atoc(char *lp);
void initStack(stack *sp);
complex currentStack(stack *sp);
void pushStack(stack *sp, complex val);
complex pullStack(stack *sp);
void printStack(stack *sp);
void addStack(stack *sp);
void subStack(stack *sp);
void mulStack(stack *sp);
void divStack(stack *sp);
void parallelStack(stack *sp);
void squareStack(stack *sp);

#endif
