/*
 * GREŚ KRZYSZTOF 130319
 * projekt 11-5
 * Dyskretyzacje - KMB, Laasonen
 * Algorytmy - Thomas, LU
 * */
#include "func.hpp"

int main() {

    auto* dt_vec = new double[N];
    auto* h_vec = new double[M];
    double** analit_matrix = allocMatrix(N, M);

    ustaw(dt_vec, h_vec);

    analit_matrix = analitycznie(dt_vec, h_vec, N, M);

    zapis_do_pliku("analityczne_wartosci.txt", analit_matrix, N, M);

    //wyniki(dt_l, h_vec, analit_matrix, LAMBDA, "KMB"); //PRZED ODPALENIEM ZMIENIC LAMBDE W PLIKU INIT NA 0.4 ALE WTEDY ZAKOMENTOWAC TO CO PONIZEJ

    wyniki(dt_vec, h_vec, analit_matrix, LAMBDA, "Thomas");

    wyniki(dt_vec, h_vec, analit_matrix, LAMBDA, "LU");

    return 0;
}
