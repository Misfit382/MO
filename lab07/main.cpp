#include <iostream>
#include "init_operations.hpp"
#include "func.hpp"
using namespace std;

void loop(double** A, double* b, const double* x, double omega) {
    for(int i = 0; i < 3; i++) {
        double* orginal_x_vector = vecInit();
        for(int j=0;j<w;j++)
            orginal_x_vector[j]=x[i];
        switch(i) {
            case 0:
                jacob(A, b, orginal_x_vector);
                break;
            case 1:
                gSeidel(A, b, orginal_x_vector);
                break;
            case 2:
                sor(A, b, orginal_x_vector, omega);
                break;
            default:
                break;
        }
    }
}
int main() {
    double** A = matrixAllocate();
    auto*  b = vecInit();
    auto*  x = vecInit();
    fillVec_with_num(x,1.0);

    double omega=0.5;
    loadMatrixFF(A,"../matrix.txt");
    loadVectorFF(b,"../vector.txt");
    loop(A,b,x,omega);
    matrixDel(A);
    vectorDel(b);
    vectorDel(x);
    return 0;
}
