#include <iostream>
#include <cmath>
#include "func.h"
using namespace std;

void start_sinus(const int max_iteracja, double e){
    cout << "Dla sinusa\nMetoda Picarda:" << endl;
    Picard(f1_w, f1_wpic, f1p_wpic, 0.5, max_iteracja, e, e);
    cout << endl << endl << "Metoda Bisekcji:" << endl;
    Bisekcji(f1_w, -0.5, 0.9, max_iteracja, e, e);
    cout << endl << endl << "Metoda Newtona" << endl;
    Newtona(f1_w, fp1_w, -0.3, max_iteracja, e, e);
    cout << endl << endl << "Metoda Siecznych" << endl;
    Siecznych(f1_w, -0.5, 0.6, max_iteracja, e, e);
}
void start_tangens(const int max_iteracja, double e){
    cout << "Dla tangensa\nMetoda Picarda:" << endl;
    Picard(f2_w, f2_wpic, f2p_wpic, 0.5, max_iteracja, e, e);
    cout << endl << endl << "Metoda Bisekcji:" << endl;
    Bisekcji(f2_w, 0.4, 0.5, max_iteracja, e, e);
    cout << endl << endl << "Metoda Newtona" << endl;
    Newtona(f2_w, fp2_w, 0.6, max_iteracja, e, e);
    cout << endl << endl << "Metoda Siecznych" << endl;
    Siecznych(f2_w, 0.4, 0.5, max_iteracja, e, e);
}

int main(){

    const int max_iteracja = 100;
    double e = 1e-8;
    start_sinus(max_iteracja,e);
    start_tangens(max_iteracja,e);
    return 0;
}
