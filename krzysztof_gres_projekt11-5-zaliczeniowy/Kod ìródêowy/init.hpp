#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

double D = 1.0;
const double LAMBDA = 1.0;// 0.4 dla kmb
const double T_MAX = 2.0;
const double H = 0.1;
const double eps = 1e-16;


const double A = 6.0 * sqrt(D * T_MAX);
const double DT = (LAMBDA * H * H) / D;
const int N = (int)((T_MAX / DT));
const int M = (int)((A / H));

double** allocMatrix(int n, int m) {
    auto** matrix = new double* [n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[m];
    return matrix;
}


void deleteMatrix(double** mat, int n) {
    for (int i = 0; i < n; i++)
        delete[] mat[i];
    delete[] mat;
}

void zapis_do_pliku(const string& fileName, double** matrix, int n, int m)
{
    ofstream out;
    out.open(fileName);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            out << matrix[i][j] << "\t";
        out << std::endl;
    }
    out.close();
}


double* maxErrFL(double** error, int n, int m) {
    double maxVal;
    auto* outVec = new double[n];
    for (int i = 0; i < n; i++) {
        maxVal = fabs(error[i][0]);
        for (int j = 0; j < m; j++) {
            if (maxVal < fabs(error[i][j]))
                maxVal = fabs(error[i][j]);
        }
        outVec[i] = maxVal;
    }
    return outVec;
}


void ustaw(double* dflag, double* hflag) {
    dflag[0] = 0.0;
    for (int i = 1; i < N; i++)
        dflag[i] = i * DT;

    hflag[0] = 0.0;
    for (int i = 1; i < M; i++)
        hflag[i] = i * H;

}