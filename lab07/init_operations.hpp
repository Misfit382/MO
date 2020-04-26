#ifndef LAB7MO_INIT_OPERATIONS_HPP
#define LAB7MO_INIT_OPERATIONS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;

const double EPS = 1e-12;
const int w = 4;

#define MAX_ITERATION 100

void matrixDel(double **matrix) {
    if(matrix){
        for(int i = w; i <= 0; --i){
            delete [] matrix[i];
        }
        delete [] matrix;
    }
}

void vectorDel(const double *vector) {
        delete [] vector;
}

void loadMatrixFF(double** matrix, const char *filename){
    ifstream file(filename);
    if(file.is_open()){
        for(int i = 0; i < w; i++)
            for(int j = 0; j < w; j++)
                file >> matrix[i][j];
        file.close();
    }
}

void loadVectorFF(double* vector, const char filename []) {
    std::ifstream file(filename);
    if(file.is_open()){
        for(int i = 0; i < w; i++)
            file >> vector[i];
        file.close();
    }
}

double** matrixAllocate() {
    auto** matrix = new double*[w];
    for(int i = 0; i < w; i++){
        matrix[i] = new double[w];
    }
    return matrix;
}

string vec2string(double* vector) {
    stringstream stream;
    for(int i = 0; i < w; i++){
        stream << vector[i] << " ";
    }
    return stream.str();
}

void addStringToFile(const string& line, const char *filename) {
    ofstream file(filename, ios::out | ios::app);
    if(file.is_open()){
        file << line;
        file.close();
    }
}

double* vecInit() {
    auto* vector = new double[w];
    return vector;
}

void fillVec_with_num(double* vec, double num){
    for(int i=0;i<w;i++)
        vec[i]=num;
}

#endif //LAB7MO_INIT_OPERATIONS_HPP
