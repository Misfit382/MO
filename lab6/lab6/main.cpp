#include <iostream>
#include "func.h"

using namespace std;


int main() {
    int const size = 6;
    sqmatrix m = sqmatrix(size);
    vec wektor = vec(size);

    double b[size] = {31, 165. / 4, 917. / 30, 851. / 28, 3637. / 90, 332. / 11};
    double u[size] = {0.0, 1. / 2, 1. / 4, 1. / 6, 1. / 8, 1. / 10};
    double d[size] = {10, 20, 30, 30, 20, 10};
    double l[size] = {1. / 3, 1. / 5, 1. / 7, 1. / 9, 1. / 11, 0.0};

    wektor.fill(b);
    m.retU()->fill(u);
    m.retD()->fill(d);
    m.retL()->fill(l);
    cout << endl;


    thomasAlg(*(m.retU()), *(m.retD()), *(m.retL()), wektor, size);

    return 0;
}