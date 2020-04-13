#include <fstream>
#include <iostream>

using namespace std;
#ifndef UNTITLED4_FUNC_H
#define UNTITLED4_FUNC_H

void print_matrix(double** tab, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << tab[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
void print_vec(double* vec, int n) {
    for (int i = 0; i < n; i++) {
        cout << vec[i] << "\t";
    }
    cout << endl;
}
void LU(double **A, double** L, double ** U, int n, int *tab)
{
    for (int i = 0; i < n ; i++){
        print_matrix(U, n);
        print_matrix(L, n);
        L[i][i] = 1;

        if (U[i][i] == 0) {
            int p = i;
            int ak = p;
            double maxn=-99999999;
            while (p < n) {
                if (U[p][i] > maxn && U[p][i] != 0){
                    maxn = U[p][i];
                    ak = p;
                }
                p++;
            }
            cout << "max: " << maxn << endl;
            double* temp = U[i];
            U[i] = U[ak];
            U[ak] = temp;
            temp = L[i];
            L[i] = L[ak];
            L[ak] = temp;
            L[i][i]=1;
            double z=tab[i];
            tab[i]=tab[ak];
            tab[ak]=z;
        }
        for (int k = i + 1; k < n; k++){
            double w = U[k][i] / U[i][i];
            L[k][i] = w;
            for (int j = 0; j <= n; j++)
                U[k][j] =U[k][j] - w * U[i][j];
        }
    }
}
void vec_b(double *y, double *b, double **L, int n, int *tab) {
    for(int i=0;i<n;i++){
        if(tab[i] !=i){
            double z=b[i];
            b[i]=b[tab[i]];
            b[tab[i]]=z;
            int v=tab[i];
            tab[i]=i;
            tab[v]=v;
        }
    }

    y[0] = b[0];
    for (int i = 1; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++) {
            y[i] = y[i] -L[i][j] * y[j];
        }
    }
}
void vec_x(double *x, double *y, double **U, int n)
{
    x[n - 1] = y[n - 1] / U[n - 1][ n - 1];
    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++) {
            x[i] = x[i] - U[i][j] * x[j];
        }
        x[i] = x[i] / U[i][i];
    }
}



#endif //UNTITLED4_FUNC_H
