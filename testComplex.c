// testComplex.c（複素数計算のテストプログラム）

#include <math.h>
#include <stdio.h>

#include "complex.h"
#include "testCommon.h"

void testMakeComp() {
    complex ans;
    testStart("makeComp");
    // 1+2jを作成
    ans = makeComp(1.0, 2.0);
    assertEqualsDouble(ans.real, 1.0);
    assertEqualsDouble(ans.image, 2.0);
    // 3.4+5.6jを作成
    ans = makeComp(3.4, 5.6);
    assertEqualsDouble(ans.real, 3.4);
    assertEqualsDouble(ans.image, 5.6);
}

void testsubComp() {
    complex in1, in2, ans;
    testStart("subComp");
    in1 = makeComp(7.0, 2.0);
    in2 = makeComp(3.0, 14.0);
    ans = subComp(in1, in2);
    assertEqualsComplex(ans, makeComp(4.0, -12.0));
    in1 = makeComp(1.1, 8.2);
    in2 = makeComp(4.8, 3.7);
    ans = subComp(in1, in2);
    assertEqualsComplex(ans, makeComp(-3.7, 4.5));
}

void testmulComp() {
    complex in1, in2, ans;
    testStart("mulComp");
    in1 = makeComp(7.0, 2.0);
    in2 = makeComp(3.0, 14.0);
    ans = mulComp(in1, in2);
    assertEqualsComplex(
        ans, makeComp(7.0 * 3.0 - 2.0 * 14.0, 2.0 * 3.0 + 7.0 * 14.0));
    in1 = makeComp(1.1, 8.2);
    in2 = makeComp(4.8, 3.7);
    ans = mulComp(in1, in2);
    assertEqualsComplex(ans,
                        makeComp(1.1 * 4.8 - 8.2 * 3.7, 8.2 * 4.8 + 1.1 * 3.7));
}

void testconjComp() {
    complex in1, ans;
    testStart("conjComp");
    in1 = makeComp(4.0, 7.0);
    ans = conjComp(in1);
    assertEqualsComplex(ans, makeComp(4.0, -7.0));
    in1 = makeComp(-2.3, -9.7);
    ans = conjComp(in1);
    assertEqualsComplex(ans, makeComp(-2.3, 9.7));
    in1 = makeComp(-6.0, 8.0);
    ans = conjComp(in1);
    assertEqualsComplex(ans, makeComp(-6.0, -8.0));
    in1 = makeComp(5.5, -2.7);
    ans = conjComp(in1);
    assertEqualsComplex(ans, makeComp(5.5, 2.7));
}

void testGetTheta() {
    double ans, ans2;
    testStart("getTheta");
    // 第1象限 45°
    ans = getTheta(makeComp(1.0, 1.0));
    ans2 = getTheta(makeComp(1.0, sqrt(3.0)));
    assertEqualsDouble(ans, 45 * (M_PI / 180));
    assertEqualsDouble(ans2, 60 * (M_PI / 180));
    // 第2象限 135°
    ans = getTheta(makeComp(-1.0, 1.0));
    ans2 = getTheta(makeComp(-1.0, sqrt(3.0)));
    assertEqualsDouble(ans, 135 * (M_PI / 180));
    assertEqualsDouble(ans2, 120 * (M_PI / 180));
    // 第3象限 225°
    ans = getTheta(makeComp(-1.0, -1.0));
    ans2 = getTheta(makeComp(1.0, -sqrt(3.0)));
    assertEqualsDouble(ans, -135 * (M_PI / 180));
    assertEqualsDouble(ans2, -60 * (M_PI / 180));
    // 第4象限 315°
    ans = getTheta(makeComp(1.0, -1.0));
    ans2 = getTheta(makeComp(-1.0, -sqrt(3.0)));
    assertEqualsDouble(ans, -45 * (M_PI / 180));
    assertEqualsDouble(ans2, -120 * (M_PI / 180));
}

void testPrintCompRT() {
    testStart("printCompRT");
    printCompRT(makeComp(2.0, 30.0));
    printf("%f∠%f\n", sqrt(2.0 * 2.0 + 30.0 * 30.0),
           atan2(30.0, 2.0) * 180 / M_PI);

    printCompRT(makeComp(-85.00, -135.0));
    printf("%f∠%f\n", sqrt(-85.0 * -85.0 + (-135.0) * -135.0),
           atan2(-135.0, -85.0) * 180 / M_PI);
}

void testMakeCompRT() {
    complex ans;
    testStart("makeCompRT");
    // 3∠0
    ans = makeCompRT(3.0, 0.0);
    assertEqualsComplex(ans, makeComp(3.0, 0));
    // 2∠π/2
    ans = makeCompRT(2.0, M_PI / 2.0);
    assertEqualsComplex(ans, makeComp(0, 2.0));
    // 1∠(-π/4)
    ans = makeCompRT(1.0, -M_PI / 4.0);
    assertEqualsComplex(ans, makeComp(sqrt(0.5), -sqrt(0.5)));
}

void testAddComp() {
    complex in1, in2, ans;
    testStart("addComp");
    in1 = makeComp(7.0, 2.0);
    in2 = makeComp(3.0, 14.0);
    ans = addComp(in1, in2);  // 足し合わせる式
    assertEqualsComplex(
        ans, makeComp(10.0, 16.0));  // 1+2j + 3+4j なら ans=4+6jとなる
    in1 = makeComp(1.1, 8.2);
    in2 = makeComp(4.8, 3.7);
    ans = addComp(in1, in2);
    assertEqualsComplex(ans, makeComp(5.9, 11.9));
}

void testcmulComp() {
    complex in1, ans;
    double k;
    testStart("cmulComp");
    in1 = makeComp(4.0, 7.0);
    k = 5.0;  // 　定数倍の式
    ans = cmulComp(in1, k);
    assertEqualsComplex(ans, makeComp(4.0 * 5.0, 7.0 * 5.0));
    in1 = makeComp(2.3, 9.7);
    k = -4.3;  // 　定数倍の式
    ans = cmulComp(in1, k);
    assertEqualsComplex(ans, makeComp(2.3 * -4.3, 9.7 * -4.3));
}

void testgetR2() {
    complex in1;
    double ans;
    testStart("getR2");
    in1 = makeComp(5.0, 7.0);
    ans = getR2(in1);
    assertEqualsDouble(ans, 5.0 * 5.0 + 7.0 * 7.0);
    in1 = makeComp(-6.1, 8.2);
    ans = getR2(in1);
    assertEqualsDouble(ans, -6.1 * -6.1 + 8.2 * 8.2);
}
//
void testInvComp() {
    complex in1, ans;
    testStart("invComp");
    in1 = makeComp(2.0, 5.0);
    ans = invComp(in1);
    assertEqualsComplex(ans, makeComp((1 / (2.0 * 2.0 + 5.0 * 5.0)) * 2.0,
                                      (1 / (2.0 * 2.0 + 5.0 * 5.0)) * -5.0));
    in1 = makeComp(4.3, -9.2);
    ans = invComp(in1);
    assertEqualsComplex(ans, makeComp((1 / (4.3 * 4.3 + -9.2 * -9.2)) * 4.3,
                                      (1 / (4.3 * 4.3 + -9.2 * -9.2)) * 9.2));
}

void testDivComp() {
    complex in1, in2, ans;
    testStart("divComp");
    in1 = makeComp(-9.0, -2.0);
    in2 = makeComp(13.0, 7.0);
    ans = divComp(in1, in2);
    assertEqualsComplex(
        ans, makeComp((-9.0 * 13.0 - 2.0 * 7.0) / (13.0 * 13.0 + 7.0 * 7.0),
                      (-2.0 * 13.0 + 9.0 * 7.0) / (13.0 * 13.0 + 7.0 * 7.0)));

    in1 = makeComp(4.2, 5.3);
    in2 = makeComp(8.9, -26.9);
    ans = divComp(in1, in2);
    assertEqualsComplex(
        ans, makeComp((4.2 * 8.9 - 5.3 * 26.9) / (8.9 * 8.9 + 26.9 * 26.9),
                      (5.3 * 8.9 + 4.2 * 26.9) / (8.9 * 8.9 + 26.9 * 26.9)));
}

void testGetR() {
    complex in1;
    double ans;
    testStart("getR");
    in1 = makeComp(-1.0, 9.0);
    ans = getR(in1);
    assertEqualsDouble(ans, sqrt(-1.0 * -1.0 + 9.0 * 9.0));
    in1 = makeComp(6.7, 2.13);
    ans = getR(in1);
    assertEqualsDouble(ans, sqrt(6.7 * 6.7 + 2.13 * 2.13));
}

void testPrintComp() {
    testStart("printComp");
    printComp(makeComp(2.10, 3.11));
    printf("2.100000+3.110000j\n");
    printComp(makeComp(-5.9, -7.1));
    printf("-5.900000-7.100000j\n");
}

void testAtofX() {
    testStart("atofX");
    assertEqualsDouble(atofX("1.0"), 1.0);
    assertEqualsDouble(atofX("1.2K"), 1.2e3);
    assertEqualsDouble(atofX("3.4M"), 3.4e6);
    assertEqualsDouble(atofX("5.6G"), 5.6e9);
    assertEqualsDouble(atofX("7.8T"), 7.8e12);
    assertEqualsDouble(atofX("1.2m"), 1.2e-3);
    assertEqualsDouble(atofX("3.4u"), 3.4e-6);
    assertEqualsDouble(atofX("5.6n"), 5.6e-9);
    assertEqualsDouble(atofX("7.8p"), 7.8e-12);
}

void testAtoc() {
    testStart("atoc");
    assertEqualsComplex(atoc("1.0"), makeComp(1.0, 0.0));
    // 複素数は「,」で区切る
    assertEqualsComplex(atoc("1.0,2.0"), makeComp(1.0, 2.0));
    // スペースが入っていても Ok
    assertEqualsComplex(atoc("3.1, 4.1"), makeComp(3.1, 4.1));
    // R∠θ(デグリー)は「;」で区切る
    assertEqualsComplex(atoc("2.0;45"), makeComp(sqrt(2.0), sqrt(2.0)));
    // スペースが入っていても Ok
    assertEqualsComplex(atoc("1.0; -60"), makeComp(0.5, -sqrt(3.0 / 4.0)));
    // K などにも対応
    assertEqualsComplex(atoc("1.0K,2.0M"), makeComp(1.0e3, 2.0e6));
    // K などにも対応
    assertEqualsComplex(atoc("1.0u;45"),
                        makeComp(sqrt(0.5) * 1e-6, sqrt(0.5) * 1e-6));
}

void testInitStack() {
    stack my_stack;
    testStart("initStack");
    my_stack.head = 0;
    initStack(&my_stack);
    assertEqualsInt(my_stack.head, N);
}

void testCurrentStack() {
    stack my_stack;
    complex ans;
    testStart("currentStack");
    initStack(&my_stack);
    // スタックが空のときはnanを返す
    ans = currentStack(&my_stack);
    assertNotEqualsInt(isnan(ans.real), 0);
    // スタックに値を入れる
    my_stack.head = N - 1;
    my_stack.data[N - 1] = makeComp(1.0, 2.0);
    ans = currentStack(&my_stack);
    assertEqualsComplex(ans, makeComp(1.0, 2.0));
}

void testPushStack() {
    stack my_stack;
    testStart("pushStack");
    initStack(&my_stack);
    pushStack(&my_stack, makeComp(1.0, 1.1));
    assertEqualsComplex(currentStack(&my_stack), makeComp(1.0, 1.1));
    assertEqualsInt(my_stack.head, N - 1);
    pushStack(&my_stack, makeComp(3.14, 1.34));
    assertEqualsComplex(currentStack(&my_stack), makeComp(3.14, 1.34));
    assertEqualsInt(my_stack.head, N - 2);
    pushStack(&my_stack, makeComp(2.71, -5.81));
    assertEqualsComplex(currentStack(&my_stack), makeComp(2.71, -5.81));
    assertEqualsInt(my_stack.head, N - 3);
}

void testPullStack() {
    stack my_stack;
    complex ans;
    testStart("pullStack");
    initStack(&my_stack);
    pushStack(&my_stack, makeComp(1.0, 2.0));
    pushStack(&my_stack, makeComp(3.14, -3.1));
    ans = pullStack(&my_stack);
    assertEqualsComplex(ans, makeComp(3.14, -3.1));
    assertEqualsInt(my_stack.head, N - 1);
    ans = pullStack(&my_stack);
    assertEqualsComplex(ans, makeComp(1.0, 2.0));
    assertEqualsInt(my_stack.head, N);
    ans = pullStack(&my_stack);
    assertNotEqualsInt(isnan(ans.real), 0);
}

void testPrintStack() {
    stack my_stack;
    testStart("printStack");
    initStack(&my_stack);
    pushStack(&my_stack, makeComp(1.0, 2.0));
    pushStack(&my_stack, makeComp(3.14, 1.31));
    pushStack(&my_stack, makeComp(2.71, -3.1));
    pushStack(&my_stack, makeComp(-53.0, 3.5));
    printStack(&my_stack);
}

void testAddStack() {
    stack my_stack;
    testStart("addStack");
    initStack(&my_stack);
    pushStack(&my_stack, makeComp(1.0, 2.0));
    pushStack(&my_stack, makeComp(3.14, 3.1));
    addStack(&my_stack);
    assertEqualsComplex(currentStack(&my_stack), makeComp(4.14, 5.1));
    assertEqualsInt(my_stack.head, N - 1);
    addStack(&my_stack);
    assertNotEqualsInt(isnan(currentStack(&my_stack).real), 0);
    assertEqualsInt(my_stack.head, N - 1);
}

void testMulStack() {
    stack my_stack;
    testStart("mulStack");
    initStack(&my_stack);
    pushStack(&my_stack, makeComp(2.0, 1.0));
    pushStack(&my_stack, makeComp(3.14, 2.0));
    mulStack(&my_stack);
    assertEqualsComplex(
        currentStack(&my_stack),
        makeComp(2.0 * 3.14 - 1.0 * 2.0, 2.0 * 2.0 + 1.0 * 3.14));
    assertEqualsInt(my_stack.head, N - 1);
    addStack(&my_stack);
    assertNotEqualsInt(isnan(currentStack(&my_stack).real), 0);
    assertEqualsInt(my_stack.head, N - 1);
}

void testSubStack() {
    stack my_stack;
    testStart("subStack");
    initStack(&my_stack);
    pushStack(&my_stack, makeComp(4.0, 1.0));
    pushStack(&my_stack, makeComp(3.14, 2.0));
    subStack(&my_stack);
    assertEqualsComplex(currentStack(&my_stack), makeComp(0.86, -1.0));
    assertEqualsInt(my_stack.head, N - 1);
    addStack(&my_stack);
    assertNotEqualsInt(isnan(currentStack(&my_stack).real), 0);
    assertEqualsInt(my_stack.head, N - 1);
}

void testDivStack() {
    stack my_stack;
    testStart("divStack");
    initStack(&my_stack);
    pushStack(&my_stack, makeCompRT(5.0, 0.0));
    pushStack(&my_stack, makeCompRT(2.0, M_PI / 2.0));
    divStack(&my_stack);
    assertEqualsComplex(currentStack(&my_stack),
                        makeCompRT(5.0 / 2.0, 0.0 - M_PI / 2.0));
    assertEqualsInt(my_stack.head, N - 1);
    addStack(&my_stack);
    assertNotEqualsInt(isnan(currentStack(&my_stack).real), 0);
    assertEqualsInt(my_stack.head, N - 1);
}

void testParallelStack() {  // 並列回路の計算
    stack my_stack;
    testStart("parallelStack");
    initStack(&my_stack);
    pushStack(&my_stack, makeComp(1.0, 0.0));
    pushStack(&my_stack, makeComp(3.0, 0.0));
    parallelStack(&my_stack);
    assertEqualsComplex(currentStack(&my_stack), makeComp(3.0 / 4.0, 0.0));
    assertEqualsInt(my_stack.head, N - 1);
    addStack(&my_stack);
    assertNotEqualsInt(isnan(currentStack(&my_stack).real), 0);
    assertEqualsInt(my_stack.head, N - 1);
}

/* main関数の記述部 */
int main() {
    testMakeComp();
    testsubComp();
    testmulComp();
    testconjComp();
    testGetTheta();
    testPrintCompRT();
    testMakeCompRT();
    testAddComp();
    testcmulComp();
    testgetR2();
    testInvComp();
    testDivComp();
    testGetR();
    testPrintComp();
    void testAtofX();
    void testAtoc();
    testInitStack();
    testCurrentStack();
    testPushStack();
    testPullStack();
    testErrorCheck();
    testPrintStack();
    testAddStack();
    testMulStack();
    testSubStack();
    testDivStack();
    testParallelStack();
    testErrorCheck();
    return 0;
}
