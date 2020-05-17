#include <iostream>
#include <fstream>
#include "init.hpp"
#include "func.hpp"

using namespace std;

void init() {
    fstream dane;
    const int N = 100;

    double x = xMin;
    double *funNode = vecAlloc(N + 1);
    double *czybNode = vecAlloc(N + 1);
    double *rwnNode = vecAlloc(N + 1);
    double jmp = (xMax - xMin) / N;


    dane.open("wyniki.txt", fstream::out);
    for (int i = 0; i < N + 1; i++) {
        funNode[i] = fun(x);
        czybNode[i] = Czybyszew(x);
        rwnNode[i] = rwnOdlegle(x);
        dane << x << "\t" << funNode[i] << "\t" << czybNode[i] << "\t" << rwnNode[i] << endl;
        x += jmp;
    }
    dane.close();
    vectorDel(funNode);
    vectorDel(czybNode);
    vectorDel(rwnNode);

}

int main() {
    init();
    return 0;
}