
#ifndef UNTITLED3_FUNC_H
#define UNTITLED3_FUNC_H
#include <iostream>
#include <cmath>

using namespace std;

typedef double (*function)(double);

double f1_w(double x){
    return sin(x / 4.0) * sin(x / 4.0) - x;
}

double f2_w(double x){
    return tan(2.0 * x) - x - 1.0;
}

double fp1_w(double x){
    return (1.0 / 4.0) * (sin(x / 2.0)) - 1;}
double fp2_w(double x){
    return -1.0 + 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

double f1_wpic(double x){
    return sin(x / 4.0) * sin(x / 4.0);
}
double f2_wpic(double x){
    return tan(2.0 * x) - 1.0;
}

double f1p_wpic(double x){
    return 1.0 / 4.0 * sin(x / 2.0);
}
double f2p_wpic(double x){
    return 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

double Picard(function f, function f_iter, function fp, double x, int n_max, double TOLX, double TOLF){
    if (fabs(fp(x)) >= 1){
        cout << "rozbieznosc!. pierwiastek nie zostanie przyblizony";
        return 0;

    }
    double estymator = 0;
    double reziduum = 0;
    double nowe_przyblizenie = x;

    cout << "Wartosc x=" << x << endl;
    for (int i = 0; i < n_max; i++){
        cout << "i= " << i;
        nowe_przyblizenie = f_iter(nowe_przyblizenie);
        cout << ", wartosc przyblizona = " << nowe_przyblizenie;
        estymator = fabs(nowe_przyblizenie - x);
        x = nowe_przyblizenie;
        reziduum = fabs(f(x));

        cout << ", residuum=" << reziduum << ", estymator bledu=" << estymator << endl;

        if ((reziduum <= TOLF || estymator <= TOLX))
            break;
    }
    return nowe_przyblizenie;
}

double Bisekcji(function f, double a, double b, int n_max, double TOLX, double TOLF){
    double srodek_przedzialu = 0;

    for (int i = 0; i < n_max; i++){
        cout << "i= " << i;
        if ((f(a) < 0 && f(b) < 0) || (f(a) > 0 && f(b) > 0)){
            cout << "Zly przedział" << endl;
            return EXIT_FAILURE;
        }
        else{
            cout << ", a= " << a ;
            cout << ", b= " << b ;
            srodek_przedzialu = (a + b) / 2.0;
            double estymator = (b - a) / 2.0;
            cout << ", srodek_przedzialu= " << srodek_przedzialu << ",estymator= " << fabs(estymator) << ", reziduum= " << fabs(f(srodek_przedzialu)) << endl;
            if ((f(a) < 0 && f(srodek_przedzialu) > 0) or (f(srodek_przedzialu) < 0 && f(a) > 0)){
                b = srodek_przedzialu;
            }
            else{
                a = srodek_przedzialu;
            }

        }
        if ((fabs(f(srodek_przedzialu)) <= TOLF) || (fabs((b - a) / 2) <= TOLX)) break;
    }
    if (!f(srodek_przedzialu)) cout << "x0= " << srodek_przedzialu << "(" << f(srodek_przedzialu) << ")" << endl;
}

double Newtona(function f, function p, double x, int n_max, double TOLX, double TOLF){
    double x0 = x;
    double x1;
    double estymator = 0;
    for (int i = 0; i < n_max; i++){
        x1 = x0 - (f(x0) / p(x0));
        estymator = fabs(x0 - x1);
        x0 = x1;

        cout << "i= " << i;
        cout << ", x1= " << x1 << ", estymator= " << estymator << ", reziduum=" << f(x0) << endl;
        if (fabs(f(x0)) <= TOLF or estymator <= TOLX) break;
    }
}

double Siecznych(function f, double x0, double x1, int n_max, double TOLX, double TOLF){
    double x2 = 0;
    double estymator = 0;
    cout << "x0=" << x0 << ", x1=" << x1 << endl;
    for (int i = 0; i < n_max; i++){

        x2 = x1 - f(x1) / ((f(x1) - f(x0)) / (x1 - x0));
        estymator = fabs(x2 - x1);

        cout << "i= " << i;
        cout << ", x2=" << x2 << ", estymator= " << fabs(estymator) << ", reziduum=" << fabs(f(x2)) << endl;

        x0 = x1;
        x1 = x2;

        if (fabs(f(x2)) <= TOLF || estymator <= TOLX) break;
    }

    return x2;
}
#endif //UNTITLED3_FUNC_H
