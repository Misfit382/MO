#ifndef LAB7MO_INIT_OPERATIONS_HPP
#define LAB7MO_INIT_OPERATIONS_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
using namespace std;


#define MAX_ITERATION 100



void vectorDel(const double *vector) {
    delete [] vector;
}

double* vecAlloc(int w) {
    auto* vector = new double[w];
    return vector;
}



#endif //LAB7MO_INIT_OPERATIONS_HPP