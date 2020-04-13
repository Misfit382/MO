#include<iostream>
#include "func.h"
#include <algorithm>
using namespace std;
/*Napisz program w języku „C/C++”, realizujący dekompozycję LU macierzy A, przy zastosowaniu eliminacji Gaussa z
 * częściowym wyborem elementu podstawowego, a następnie rozwiązujący układ równań Ax= b.
 * Uwaga: należy zaimplementować wariant dekompozycji omawiany na wykładzie.Program należy zrealizować
 * w postaci dwóch odrębnych procedur: jednej, która operuje wyłącznie na macierzy A, i drugiej, która operuje wyłącznie na wektorze  b,
 * korzystając z wyników działania procedury pierwszej
 *
 * Greś Krzysztof
 * */
int matrix_size() {
    ifstream file;
    file.open("../matrix_size.txt");
    int n;
    file >> n;
    file.close();
    return n;
}

void fill_everything(double **A, double **L, double **U, double *b, double *x, double *y, int n) {
    ifstream file;
    file.open("../data.txt");
    if (!file.good()) {
        cout << "File error, matrix not found." << endl;
        exit(1);
    }
    double r;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            file >> r;
            A[i][j] = r;
            U[i][j] = r;
            L[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        file >> r;
        b[i] = r;
    }
    fill(x, x+n, 0);
    fill(y, y+n, 0);
}

int main(){
    int n=matrix_size();
    double **A, ** U, ** L,*W,*x,*y,*b;

    A = new double* [n];
    L = new double* [n];
    U = new double* [n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
        L[i] = new double[n];
        U[i] = new double[n];
    }

    x= new double[n];
    y= new double[n];
    b = new double[n];

    fill_everything(A,L,U,b,x,y,n);

    cout<<"matrix A: (input one)\n";
    print_matrix(A, n);
    cout<<"matrix U: \n";
    print_matrix(U, n);
    cout<<"matrix L: \n";
    print_matrix(L, n);

    cout<<"vector b: \n";
    print_vec(b, n);

    int *tab;
    tab = new int[n];
    for(int i=0;i<n;i++)
        tab[i]=i;
    LU(A,L,U,n,tab);
    vec_b(y, b, L, n, tab);
    vec_x(x, y, U, n);

    cout<<"vector y: \n";
    print_vec(y, n);
    cout<<"vector x: \n";
    print_vec(x, n);

    return 0;
}


