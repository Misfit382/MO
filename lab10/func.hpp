#include <cmath>

using namespace std;

double rozwiazanieAnalityczne(double t){
    return 1.0 - exp(-10.0 * (t + atan(t)));
}

double bezposreniaEulera(double h, double t_Max) {
    double y = 0.0;
    for (double i = 0.0; i < t_Max; i += h) {
        y += h * (-((10.0 * i * i + 20.0) / (i * i + 1.0)) * (y - 1.0));
    }
    return y;
}

double errsMBE(double h, int N)  {
    double err = 0.0, t = h, y = 0.0, wDok;
    err = abs(rozwiazanieAnalityczne(t) - bezposreniaEulera(h, t));
    for (int i = 0; i < N; i++, t += h) {
        wDok = rozwiazanieAnalityczne(t);
        y = bezposreniaEulera(h, t);
        wDok = abs(wDok - y);
        if (wDok > err)
            err = wDok;
    }
    return err;
}

double posredniaEulera(double h, double t_Max) {
    double y = 0.0, u1 = 0.0;
    for (double i = 0.0; i < t_Max; i += h) {
        u1 = (10.0 * (i + h) * (i + h) + 20.0) / ((i + h) * (i + h) + 1.0);
        y = (y + h * u1) / (1.0 + h * u1);
    }
    return y;
}
double errsMPE(double h, int N)  {
    double err = 0.0, t = h, y = 0.0, wDok;
    err = abs(rozwiazanieAnalityczne(t) - posredniaEulera(h, t));

    for (int i = 0; i < N; i++, t += h) {
        wDok = rozwiazanieAnalityczne(t);
        y = posredniaEulera(h, t);
        wDok = abs(wDok - y);
        if (wDok > err)
            err = wDok;
    }
    return err;
}

double mTrapezow(double h, double t_Max) {
    double y = 0.0, u1 = 0.0, u2 = 0.0;
    for (double i = 0.0; i < t_Max; i += h) {
        u1 = (10.0 * i * i + 20.0) / (i * i + 1.0);
        u2 = (10.0 * (i + h) * (i + h) + 20.0) / ((i + h) * (i + h) + 1.0);
        y = ((-h / 2.0) * (u1 * (y - 1.0) - u2) + y) / (1.0 + (h / 2.0) * u2);
    }
    return y;
}

double errMT(double h, int N) {
    double err = 0.0, t = h, y = 0.0, wDok;
    err = abs(rozwiazanieAnalityczne(t) - mTrapezow(h, t));

    for (int i = 0; i < N; i++, t += h) {
        wDok = rozwiazanieAnalityczne(t);
        y = mTrapezow(h, t);
        wDok = abs(wDok - y);
        if (wDok > err)
            err = wDok;
    }

    return err;
}