#include "func.h"

void NI(vec& U, vec& D, vec& L, int size) {
    for (int i = 1; i < size; i++) D(i) = D(i) - (L(i) / D(i - 1) * U(i - 1));
}

void R(vec& L, vec& D, vec& B, int size) {
    for (int i = 1; i < size; i++) B(i) = B(i) - (L(i) / D(i - 1) * B(i - 1));
}

void X(vec& x, vec& D, vec& B, vec& U, int size) {
    x(size - 1) = B(size - 1) / D(size - 1);
    for (int i = size - 2; i >= 0; i--) x(i) = (B(i) - U(i) * x(i + 1)) / D(i);
}

void thomasAlg(vec& U, vec& D, vec& L, vec& B, int size) {
    vec x(size);
    x.nullify();
    NI(U, D, L, size);
    cout << "ni: ";
    D.print();
    cout << "u: ";
    U.print();
    cout << "l: ";
    L.print();
    R(L, D, B, size);
    cout << "r:  ";
    B.print();
    X(x, D, B, U, size);
    cout << "x: ";
    x.print();
    cout << endl;
}
