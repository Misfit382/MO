#include <iostream>
#include <cmath>
#include "init.hpp"

using namespace std;

const double p = 1.0, q = 0.0, r = -4.0,
        alf = 0.0, bet = 1.0, gam = -1.0,fi = 0.0,
        psi = 1.0, teta = 0.0,
        beginSection = 0.0, endSection = 1.0; //poczatek i koniec przedzialu

double fun(double x)  {
    return ( exp( 2.0-2.0*x ) - 4*exp( 4.0 - x * 2.0  )+ 4*exp( x * 2.0 ) - exp( 2.0 + 2.0*x ) - x + x*exp(4.0)) / ( 4.0 - 4*exp(4.0) );
}

void thomasalg( const double *l, const double *d, const double *u, const double *b, double *x, int N ) { //alg thomasa
    auto *bCopy = vecAlloc<double>(N);
    auto *dCopy = vecAlloc<double>(N);

    dCopy[0] = d[0];
    bCopy[0] = b[0];

    for (int i = 1; i < N; i++)
        dCopy[i] = d[i] - l[i - 1] * (u[i - 1] / dCopy[i - 1]);

    for (int i = 1; i < N; i++)
        bCopy[i] = b[i] - l[i - 1] * bCopy[i - 1] / dCopy[i - 1];

    x[N - 1] = bCopy[N - 1] / dCopy[N - 1];

    for (int i = N - 2; i >= 0; i--)
        x[i] = (bCopy[i] - u[i] * x[i + 1]) / dCopy[i];

    vecDel<double>(dCopy);
    vecDel<double>(bCopy);
}

int biggestErr(double *blad, int N ) {
    double maximum = fabs(blad[0] );
    int flag = 0;
    for (int i = 0; i < N; i++)
        if (fabs( blad[i] ) > maximum) {
            maximum = fabs(blad[i]);
            flag=i;
        }
    return flag;
}

double numericDis(double h, int N ) { //numerowa dyskretyzacja
    fstream rowNum, analytic;
    rowNum.open("outNum.txt", ios_base::app );
    analytic.open("outAnal.txt", ios_base::app);
    analytic << scientific;
    rowNum << scientific;

    double *l= vecAlloc<double>(N),
            *d= vecAlloc<double>(N),
            *u= vecAlloc<double>(N),
            *b= vecAlloc<double>(N),
            *x= vecAlloc<double>(N),
            *errs= vecAlloc<double>(N),
            xp1 = beginSection, xp2 = beginSection;

    u[0] = alf / h;
    d[0] = bet - alf / h;
    b[0] = -gam;

    for(int i = 1; i < N - 1; i++) {
        l[i - 1] = p / (h * h) + r / 12.0;
        d[i] = (-2.0 * p) / (h * h) + r * (10.0 / 12.0);
        u[i] = p / (h * h) + r / 12.0;
        b[i] = (xp1 + i * h - h) / 12.0 + (10.0 / 12.0) *  (xp1 + i * h) + (xp1 + i * h + h) / 12.0;
    }

    l[N - 2] = -fi / h;
    d[N - 1] = -fi / h + psi;
    b[N - 1] = -teta;

    thomasalg( l, d, u, b, x, N );

    for ( int i = 0; i < N; i++ ) {
        errs[i] = fabs(x[i] - fun(xp2) );
        xp2 += h;
    }
    int flag = biggestErr(errs, N);



    if(N==162) {
        for ( int i = 0; i < N; i++ ) {
            rowNum << xp1 << "\t" << x[i] << "\t" << endl;
            analytic << xp1 << "\t" << fun(xp1) << endl;
            xp1 += h;
        }
    }

    vecDel<double>(l);
    vecDel<double>(d);
    vecDel<double>(u);
    vecDel<double>(x);
    vecDel<double>(b);
    analytic.close();
    rowNum.close();
    return errs[flag];
}

double threePointDis(double h, int N ) {
    fstream konw;
    konw.open("outKonw.txt", ios_base::app);
    konw << scientific;
    cout.precision(10);

    double *l= vecAlloc<double>(N),
            *d= vecAlloc<double>(N),
            *u= vecAlloc<double>(N),
            *b= vecAlloc<double>(N),
            *x= vecAlloc<double>(N),
            *errs= vecAlloc<double>(N),
            xp1 = beginSection, xp2 = beginSection;

    u[0] = alf / h;
    d[0] = bet - alf / h;
    b[0] = -gam;

    for ( int i = 1; i < N - 1; i++ )
    {
        l[i - 1] = p / ( h * h ) - q / ( 2.0 * h );
        d[i] = ( -2.0 * p ) / ( h *h ) + r;
        u[i] = p / ( h * h ) + q / ( 2.0 * h );
        b[i] = (xp1+i*h);
    }

    l[N - 2] = -fi / h;
    d[N - 1] = -fi / h + psi;
    b[N - 1] = -teta;

    thomasalg( l, d, u, b, x, N );

    for ( int i = 0; i < N; i++ )
    {
        errs[i] = fabs(x[i] - fun(xp2) );
        xp2 += h;
    }



    int flag = biggestErr(errs, N);
    if(N==162)
    {
        for ( int i = 0; i < N; i++ )
        {
            konw << xp1 << "\t" << x[i] << endl;
            xp1 += h;
        }
    }

    vecDel<double>(l);
    vecDel<double>(d);
    vecDel<double>(u);
    vecDel<double>(x);
    vecDel<double>(b);

    return errs[flag];
}
