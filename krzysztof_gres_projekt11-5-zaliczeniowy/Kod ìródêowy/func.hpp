#include "init.hpp"

void oblicz_bledy(double** err, double** analit, double** calculatedValues, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            err[i][j] = abs(calculatedValues[i][j] - analit[i][j]);
}

double** analitycznie(const double* dt_vec, const double* h_vec, int n, int m) {
    double** flag = allocMatrix(n, m);
    for (int i = 0; i < m; i++)
        flag[0][i] = 0.0;
    for (int i = 0; i < n; i++) {
        flag[i][M - 1] = 0.0;
        flag[i][0] = 1.0;
    }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m - 1; j++)
            flag[i][j] = erfc(h_vec[j] / (2.0 * sqrt(D * dt_vec[i])));
    return flag;
}

void metodaBezposrenia(double** U, double lambda, int n, int m) {
    for (int i = 0; i < m; i++)
        U[0][i] = 0;
    for (int i = 0; i < n; i++) {
        U[i][M - 1] = 0.0;
        U[i][0] = 1.0;
    }

    for (int k = 1; k < n; k++)
        for (int i = 1; i < m - 1; i++)
            U[k][i] = U[k - 1][i] + lambda * (U[k - 1][i - 1] - (2 * U[k - 1][i]) + U[k - 1][i + 1]);
}


void thomasalg(double **matrix, const double *b, double *wyn)  {
    double *beta, *gamma;
    beta = new double[M]; gamma = new double[M];

    beta[0] = - (matrix[0][1] / matrix[0][0]);
    gamma[0] = (b[0] / matrix[0][0]);

    for(int i=1; i<M; i++) {
        if (i<=M-2)
            beta[i] = - ((matrix[i][2 + i - 1]) / ((matrix[i][i - 1] * beta[i - 1]) + matrix[i][1 + i - 1]));

        gamma[i] = (b[i] - (matrix[i][i - 1] * gamma[i - 1])) / (matrix[i][i - 1] * beta[i - 1] + matrix[i][1 + i - 1]);
    }
    beta[M-1] = 0;

    wyn[M-1]=gamma[M-1];
    for(int i = M - 2; i>=0; i--)
        wyn[i] = beta[i]*wyn[i+1]+gamma[i];

    delete beta;
}

void dekompozycja_LU(double **matrix, const double *b, double *wyn)  {
    double x;
    for(int k=0; k<M-1; k++) {
        for(int i=k+1; i<M; i++) {
            x = matrix[i][k] / matrix[k][k];
            matrix[i][k] = x;
            for(int j=k+1; j<M; j++) {
                matrix[i][j] = matrix[i][j] - (x * matrix[k][j]);
            }
        }
    }

    double suma;
    auto *z = new double[M];

    for(int i=0; i<M; i++) {
        suma = 0;
        for(int j=0; j<=i-1; j++) {
            suma += matrix[i][j] * z[j];
        }

        z[i] = b[i]-suma;
    }

    for(int i=M-1; i>=0; i--) {
        suma = 0;
        for(int j=i+1; j<M; j++) {
            suma += matrix[i][j] * wyn[j];
        }

        wyn[i] = (z[i]-suma) / matrix[i][i];
    }
}

void rozwiazanie_lassonen(double **laasonen, const string& funkcja, double lambda, int n, int m) {
    auto *b = new double[m];
    auto *wyn = new double[m];

    auto **matrix = new double *[m];
    for(int i = 0; i < m; i++) matrix[i] = new double [m];

    for(int i = 0; i < m; i++)
        for(int j = 0; j < m; j++)
            matrix[i][j] = 0;

    for(int j=0; j < m; j++)
        laasonen[0][j]=0;

    for(int i = 0; i < n; i++ )
        laasonen[i][0] = 1;
    for(int i = 0; i < n; i++ )
        laasonen[i][m - 1] = 0;

    for(int k = 1; k < n; k++ ) {
        matrix[0][0] = 1;
        b[0] = 1;

        for(int i = 1; i < m - 1; i++ ) {
            matrix[i][i] = -(1 + (2 * lambda) );
            matrix[i][i + 1] = lambda;
            matrix[i][i - 1] = lambda;
            b[i] = -laasonen[k-1][i];
        }

        b[m - 1] = 0;
        matrix[m - 1][m - 1] = 1;

        if(funkcja == "Thomas")
            thomasalg(matrix, b, wyn);
        if(funkcja == "LU")
            dekompozycja_LU(matrix, b, wyn);

        for(int i = 1; i < m - 1; i++ )
            laasonen[k][i] = wyn[i];
    }

    for(int i= m - 1; i >= 0; i--) delete []matrix[i];
    delete[]matrix;

    delete[] b;
}


void wyniki(double* dt_vec, double* h_l, double** analityczne, double lambda, const string &method) {
    double** U = allocMatrix(N, M);
    double** errorMatrix = allocMatrix(N, M);
    string filename1 = method +"errors.txt";
    string filename2 = method +"values.txt";

    if(method == "LU")
        rozwiazanie_lassonen(U,"LU", lambda, N, M);
    else if(method == "Thomas")
        rozwiazanie_lassonen(U,"Thomas", lambda, N, M);
    else if(method == "KMB")
        metodaBezposrenia(U, lambda, N, M);


    oblicz_bledy(errorMatrix, analityczne, U, N, M);
    zapis_do_pliku(filename1, errorMatrix, N, M);
    zapis_do_pliku(filename2, U, N, M);

    ofstream file04;
    ofstream file10;
    ofstream file16;

    string filename3 = method +"_analit04.txt";
    string filename4 = method +"_analit10.txt";
    string filename5 = method +"_analit16.txt";


    file04.open(filename3);
    file10.open(filename4);
    file16.open(filename5);
    if(method != "KMB") {
        for (int i = 0; i < N; i++) {
            if (abs(h_l[i + 1]) < eps || abs(U[40][i + 1]) < eps)
                break;
            file04 << h_l[i + 1] << "\t" << U[40][i + 1] << "\t" << analityczne[40][i + 1] << endl; // d_t = 0.3
        }

        for (int i = 0; i < N; i++) {
            if (abs(h_l[i + 1]) < eps || abs(U[100][i + 1]) < eps)
                break;
            file10 << h_l[i + 1] << "\t" << U[100][i + 1] << "\t" << analityczne[100][i + 1] << endl; // d_t = 1.0
        }

        for (int i = 0; i < N; i++) {
            if (abs(h_l[i + 1]) < eps || abs(U[160][i + 1]) < eps)
                break;
            file16 << h_l[i + 1] << "\t" << U[160][i + 1] << "\t" << analityczne[160][i + 1] << endl; // d_t = 1.7
        }
    }
    else {
        for (int i = 0; i < N; i++) {
            if (abs(h_l[i + 1]) < eps || abs(U[100][i + 1]) < eps)
                break;
            file04 << h_l[i + 1] << "\t" << U[100][i + 1] << "\t" << analityczne[100][i + 1] << endl; // d_t = 0.3
        }

        for (int i = 0; i < N; i++) {
            if (abs(h_l[i + 1]) < eps || abs(U[250][i + 1]) < eps)
                break;
            file10 << h_l[i + 1] << "\t" << U[250][i + 1] << "\t" << analityczne[250][i + 1] << endl; // d_t = 1.0
        }

        for (int i = 0; i < N; i++) {
            if (abs(h_l[i + 1]) < eps || abs(U[400][i + 1]) < eps)
                break;
            file16 << h_l[i + 1] << "\t" << U[400][i + 1] << "\t" << analityczne[400][i + 1] << endl; // d_t = 1.7
        }
    }


    double* maxerrors = maxErrFL(errorMatrix, N, M);
    ofstream filemaxerrors;
    string filename6 = method+"-time.txt";
    filemaxerrors.open(filename6);
    for (int i = 0; i < N - 1; i++){
        if (abs(dt_vec[i + 1]) < eps || (maxerrors[i + 1]) < eps)
            break;
        filemaxerrors << dt_vec[i + 1] << "\t" << maxerrors[i + 1] << endl;
    }

    cout << method << " " <<  H << " " << maxerrors[M - 1] << endl;

    filemaxerrors.close();

    deleteMatrix(U, N);
    deleteMatrix(errorMatrix, N);
    delete[] maxerrors;
}
