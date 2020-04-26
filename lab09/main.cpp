#include <iostream>
#include <cmath>
#include <fstream>
#include "func.hpp"
using namespace std;

int main() {
	double h, errN, errK;

	fstream errs;
	errs.open("errs.txt", fstream::out );
	errs << scientific;
	cout.precision(10);

	for (int i = 2 ; i < 30000; i += 50) {
		h = (endSection - beginSection ) / (i - 1 );
        errK = (threePointDis(h, i) );
        errN =(numericDis(h, i) );
		errs << log10(h) << "\t" << log10(errK) << "\t" << log10(errN) << endl;
	}
	errs.close();
	return 0;
}
