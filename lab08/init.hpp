#include <iostream>
#include <fstream>

using namespace std;

void string2file(const string& line, const char *filename) {
    ofstream file(filename, ios::out);
    if(file.is_open()) {
        file << line;
        file.close();
    }
}

template< typename T >
T** matrix_allocate(const int w, const int k) {
    T** matrix = new T*[w];
    for(int i = 0; i < k; i++) {
        matrix[i] = new T[k];
    }
    return matrix;
}

template< typename T >
T* vecAlloc(const int w) {
    T* vector = new T[w];
    return vector;
}