
#ifndef UNTITLED5_FUNC_H
#define UNTITLED5_FUNC_H
#include <iostream>

using namespace std;



class vec {
private:
    int size;
    double* array;
public:
    vec(const int size = 6) {
        if (size > 0)
            this->size = size;
        else
            exit(-1);
        this->array = new double[this->size];
    }
    virtual ~vec() { delete[] array; };
    void print() {
        for (int i = 0; i < this->size; i++) {
            cout << this->array[i]<<"\t";
        }
        cout << endl;
    }
    void fill(double* x) {
        for (int i = 0; i < this->size; i++)
            this->array[i] = x[i];
    }
    double* returnArr() {
        return this->array;
    }
    void nullify() {
        for (int i = 0; i < this->size; i++)
            this->array[i] = 0.0;
    }
    double& operator()(int x) {
        return this->array[x];
    }
};

class sqmatrix {
private:
    int size;
    vec* w1, * w2, * w3;
public:
    explicit sqmatrix(const int rozmiar=6){
        if (rozmiar > 0) this->size = rozmiar;
        else {
            cout << "failM" << endl;
            exit(-1);
        }
        this->w1 = new vec(rozmiar);
        this->w2 = new vec(rozmiar);
        this->w3 = new vec(rozmiar);
    }
    virtual ~sqmatrix() {
        delete this->w1;
        delete this->w2;
        delete this->w3;
    };
    vec* retU() {
        return this->w1;
    }
    vec* retD() {
        return this->w2;
    }
    vec* retL() {
        return this->w3;
    }
};
void NI(vec& U, vec& D, vec& L, int size);
void R(vec& L, vec& D, vec& B, int size);
void X(vec& x, vec& D, vec& B, vec& U, int size);
void X(vec& x, vec& D, vec& B, vec& U, int size);
void thomasAlg(vec& U, vec& D, vec& L, vec& B, int size);

#endif //UNTITLED5_FUNC_H
