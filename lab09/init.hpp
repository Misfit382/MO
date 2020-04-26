#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <fstream>

using namespace std;


template< typename T >
T* vecAlloc(const int w) {
    T* vector = new T[w];
    return vector;
}

template< typename T >
void vecDel(T* vector) {
        delete [] vector;

}