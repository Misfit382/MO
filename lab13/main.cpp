#include<iostream>
#include<fstream>
#include "func.hpp"

int main() {
    std::ofstream out, graph;
    out.open("out.txt");
    graph.open("graph.txt");

    out << std::scientific;
    graph << std::scientific;

    long double h=0.1;
    long double wynik=0;

    for(long double b = 1.0;b<=3.0;b++) {
        wynik= exac(b);

        h=0.1;
        while(h>1e-5){
            out << h << " ";
            out << rect_a(b, h) << " ";
            out << rect_b(b, h) << " ";
            out << rect_c(b, h) << " ";
            out << trapezes(b, h) << " ";
            out << parab(b, h) << " ";
            out << std::endl;

            if(b==3) {
                graph << log10(h) << " ";
                graph << errs((rect_a(b, h) - wynik) / wynik) << " ";
                graph << errs((rect_b(b, h) - wynik) / wynik) << " ";
                graph << errs((rect_c(b, h) - wynik) / wynik) << " ";
                graph << errs((trapezes(b, h) - wynik) / wynik) << " ";
                graph << errs((parab(b, h) - wynik) / wynik) << " ";
                graph << std::endl;
            }

            h=h/2;
        }

    }

}

