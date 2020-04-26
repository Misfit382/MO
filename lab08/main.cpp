#include <iostream>
#include <iomanip>
#include <cmath>
#include "func.hpp"
#include "init.hpp"

const int maxSteps = 20;
const int maxIterMeth = 9;

template< typename T >
T fun(T x){
    T l = T(2);
    return sin(x);
}
template< typename T >
T Derivative(T x){
    T l = T(2);
    return  cos(x);
}

template< typename T >
void storeInFile(T* steps, T** results){
    string type_name = typeid(T).name();
    type_name = "lab8_" + type_name + ".txt";

    stringstream stream;
    for(int i = 0; i < maxSteps; i++) {
        stream << log10(steps[i]) << " ";
        for(int j = 0; j < maxIterMeth; j++) {
            stream << results[j][i] << " ";
        }
        stream << endl;
    }
    string2file(stream.str(), type_name.c_str());
}
template< typename T, T (*ptrFun)(T x) >
void rzad(T** wyniki, string s) {
    T i=wyniki[0][1];
    for(int i=0;i<9;i++)
    cout<<s<<"DLA METODY NR."<<i+1<<" RZAD: "<<abs((((wyniki[i][1]))-(wyniki[i][0]))/((wyniki[9][1])-(wyniki[9][0])))<<endl;

}

template< typename T, T (*ptrFun)(T x) >
void differencesFunc(T* steps, T** wyniki, string s){
    T start = 0;
    T central = M_PI /2.0;
    T end = M_PI;
    T krok = 0.1;
    for(int i = 0; i < maxSteps; i++) {
        steps[i] = krok;
        wyniki[0][i] = log10(abs(Derivative(start) - forwDiff<T, ptrFun>(start, krok)));
        wyniki[1][i] = log10(abs(Derivative(start) - fdThreePoint<T, ptrFun>(start, krok)));
        wyniki[2][i] = log10(abs(Derivative(central) - fdThreePoint<T, ptrFun>(central, krok)));
        wyniki[3][i] = log10(abs(Derivative(central) - forwDiff<T, ptrFun>(central, krok)));
        wyniki[4][i] = log10(abs(Derivative(central) - centrDiff<T, ptrFun>(central, krok)));
        wyniki[5][i] = log10(abs(Derivative(central) - forwDiff<T, ptrFun>(central, krok)));
        wyniki[6][i] = log10(abs(Derivative(central) - bdThreePoint<T, ptrFun>(central, krok)));
        wyniki[7][i] = log10(abs(Derivative(end) - backDiff<T, ptrFun>(end, krok)));
        wyniki[8][i] = log10(abs(Derivative(end) - bdThreePoint<T, ptrFun>(end, krok)));
        krok /= 10;
    }
    rzad<T, ptrFun>(wyniki,s);
}
template< typename T, T (*ptrFun)(T x) >
void wyniki(string s){
    T* steps = vecAlloc<T>(maxSteps+1);
    T** results = matrix_allocate< T > (maxIterMeth+1, maxSteps+1);
    differencesFunc<T, ptrFun>(steps, results,s);
    storeInFile<T>(steps, results);
}

int main(){
    wyniki<float, fun>("double ");
    wyniki<double, fun>("float ");
    return 0;
}
