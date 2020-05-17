#include <iostream>
#include <fstream>
#include <cmath>
#include "init.hpp"

const int nodes = 15;
const double xMin = -1.0, xMax = 1.0;
double const flagNode = (xMax - xMin) / (nodes - 1);

double fun(double x) {
    return 1.0 / (1.0 + 10.0 * pow(x, 6));
}

double Lagrange(double x, const double *xi, const double *yi) {
    double *product= vecAlloc(nodes);
    double out = 0.0;

    for (int i = 0; i < nodes; i++) {
        product[i] = 1.0;
        for (int j = 0; j < nodes; j++)
            if (j != i)
                product[i] = product[i] * ((x - xi[j]) / (xi[i] - xi[j]));
    }

    for (int i = 0; i < nodes; i++)
        out = out + yi[i] * product[i];
    vectorDel(product);
    return out;
}

double Czybyszew(double x) {
    double *xCz = vecAlloc(nodes);
    double *yCz= vecAlloc(nodes);

    for (int i = 0; i < nodes; i++) {
        xCz[i] = cos(((2.0 * i + 1.0) * M_PI) / (2.0 * nodes));
        yCz[i] = fun(xCz[i]);
    }
    return Lagrange(x, xCz, yCz);


}

double rwnOdlegle(double x) {
    double *xi = vecAlloc(nodes);
    double *yi = vecAlloc(nodes);

    int i = 0;

    for (double z = xMin; z <= xMax; z += flagNode) {
        xi[i] = z; // poczatek przedzialu
        yi[i] = fun(z); // wyliczenie funkcji dla wezla
        i++;
    }
    return Lagrange(x, xi, yi);
}