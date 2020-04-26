#ifndef LAB7MO_FUNC_HPP
#define LAB7MO_FUNC_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "init_operations.hpp"

#define MAX_ITERATION 100

using namespace std;
double* vecSubstract(const double* vec1, const double* vec2) {
    auto* buf = new double[w];
    for(int i = 0; i < w; i++){
        buf[i] = vec1[i] - vec2[i];
    }
    return buf;
}

double scalarMatrix(double** matrix, const double* x, int i) {
    double scalar = 0;
    for(int j = 0; j < w; ++j) {
        if(i != j) {
            scalar += matrix[i][j] * x[j];
        }
    }
    return scalar;
}

double normalizeVec(double* vector) {
    double norm = fabs(vector[0]);
    for(int i = 0; i < w - 1; i++)
        if(fabs(vector[i]) < fabs(vector[i + 1]))
            norm = fabs(vector[i + 1]);
    return norm;
}

double* residuumVec(double** matrix, const double* x, const double* b) {
    double sum;
    auto* resVec = new double[w];
    for(int i = 0; i < w; i++){
        sum = 0;
        for(int j = 0; j < w; j++){
            sum += matrix[i][j] * x[j];
        }
        resVec[i] = sum - b[i];
    }
    return resVec;
}

double estymatorfunc(double* vector_1, double* vector_2) {
    double* buf;
    buf = vecSubstract(vector_1, vector_2);
    double error = normalizeVec(buf);
    return error;
}

double residuumfunc(double** matrix, double* x, double* b) {
    double* resVec = residuumVec(matrix, x, b);
    return normalizeVec(resVec);
}

bool storeInFile(double** matrix, double* oldX, double* newX, double* b, int step, const char *filename, const char *funcname) {
    double estymator = estymatorfunc(oldX, newX);
    double residuum  = residuumfunc(matrix, newX, b);
    stringstream stream;
    if(!step)
        stream <<funcname<<endl<< "ITER" ;

    stream << endl << step << "\t" << vec2string(newX) << "\t" << "Residuum = " << residuum << "\t" << "Estymator = " << estymator << endl;
    addStringToFile(stream.str(), filename);
    return !(residuum < EPS or estymator < EPS);
}
double* jacob(double** matrix, double* b, double* x) {
    double* xAprox   = vecInit();

    for(int step = 0; step < MAX_ITERATION; step++) {
        for(int i = 0; i < w; i++) {
            xAprox[i] = (b[i] - scalarMatrix(matrix, x, i)) / matrix[i][i];
        }
        if(!storeInFile(matrix, x, xAprox, b, step, "out.txt","Jacob"))
            break;
        for(int i=0;i<w;i++)
            x[i]=xAprox[i];
    }
    return xAprox;
}

double* gSeidel(double** matrix, double* b, double* x) {
    double* prev_x = vecInit();

    for(int step = 0; step < MAX_ITERATION; step++) {
        for(int i = 0; i < w; i++) {
            prev_x[i] = x[i];
            x[i] = (b[i] - scalarMatrix(matrix, x, i)) / matrix[i][i];
        }
        if(!storeInFile(matrix, x, prev_x, b, step, "out.txt", "Gauss Seidel"))
            break;
    }
    return x;
}
double* sor(double** matrix, double* b, double* x, double omega) {
    double* prev_x = vecInit();

    for(int step = 0; step < MAX_ITERATION; step++) {
        for(int i = 0; i < w; i++) {
            prev_x[i] = x[i];
            x[i] = (1 - omega) * x[i] + omega * (b[i] - scalarMatrix(matrix, x, i)) / matrix[i][i];
        }
        if(!storeInFile(matrix, x, prev_x, b, step, "out.txt","SOR"))
            break;
    }
    return x;
}
#endif //LAB7MO_FUNC_HPP