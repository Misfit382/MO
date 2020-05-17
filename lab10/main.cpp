#include <iostream>
#include <cmath>
#include <fstream>
#include "func.hpp"
using namespace std;

const int N = 1000;

void init() {
    double mbeS = 0.0, mbeNS = 0.0, mpe = 0.0, mt = 0.0;

    ofstream bledy, stabilne, niestabilne;

    bledy.open("../bledy.txt");
    stabilne.open("../stabilne.txt");
    niestabilne.open("../niestabilne.txt");

    for (double step = 100; step > 1e-20; step = step / 2.5) {
        mbeS = log10(errsMBE(step, N));
        mpe = log10(errsMPE(step, N));
        mt = log10(errMT(step, N));
        bledy << log10(step) << "\t" << mbeS << "\t" << mpe << "\t" << mt << endl;
    }

    for (double t = 0.0, step = 0.025; t < 5.0; t += step) {
        mbeS = bezposreniaEulera(step, t);
        mpe = posredniaEulera(step, t);
        mt = mTrapezow(step, t);
        stabilne << t << "\t" << rozwiazanieAnalityczne(t) << "\t" << mbeS << "\t" << mpe << "\t" << mt << endl;
    }

    for (double t = 0.0, step = 0.25; t < 5.0; t += step) {
        mbeNS = bezposreniaEulera(step, t);
        niestabilne << t << "\t" << rozwiazanieAnalityczne(t) << "\t" << mbeNS << endl;
    }
    bledy.close();
    stabilne.close();
    niestabilne.close();
}
int main(){
    init(); 
    return 0;
}