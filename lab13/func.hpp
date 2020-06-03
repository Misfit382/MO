#include "calerf.h"
#include<cmath>

#define constans 2.0/(sqrt(M_PI))

long double fun(long double x) {
    return exp(-1*pow(x,2.0));
}

long double rect_a(long double b,long  double h) {
    long double y, x;
    x = y = 0;
    long double n=(0+b)/h;
    for (int i = 0; i < n; i++) {
        y += h * fun(x);
        x += h;
    }

    return constans * y;
}


long double rect_b(long double b,long  double h) {
    long double y=0;
    long double x = h;
    long double n=(0+b)/h;

    for (int i = 0; i < n; i++) {
        y += h * fun(x);
        x += h;
    }

    return constans * y;
}

long double rect_c(long double b,long double h) {
    long double y=0;
    long double n=(0+b)/h;
    long double x = 0;

    for (int i = 0; i < n; i++) {
        x = x + h/2;
        y += h * fun(x);
        x += h/2;
    }

    return constans * y;
}

long double trapezes(long double b,long double h) {
    long double n=(0+b)/h;
    long double y = 0.0;
    long double x = y;
    long double y1,y2;
    for (int i = 0; i < n; i++) {
        y1= fun(x);
        y2= fun(x + h);
        y += h * (y1+y2) / 2.0;
        x = x + h;
    }

    return constans * y;

}

long double parab(long double b,long double h) {
    long double n = (0.0 + b) / h;
    long double y = 0.0;
    long double x = y;

    for(int i = 0; i < n; i++) {
        y += h * ((fun(x) + 4.0 * fun(x + h / 2.0) + fun(x + h)) / 6.0);
        x+=h;
    }

    return constans * y;
}

long double exac(long double b) {
    long double exac;
    exac = calerf::CALERFL(b, 0);
    return exac;
}
long double errs(long double num) {
    return log10(std::fabs(num));
}