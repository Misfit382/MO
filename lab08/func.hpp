#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <fstream>

using namespace std;
template< typename T, T (*ptrFun)(T x) >
T forwDiff(T arg, T h){
    return (ptrFun(arg + h) - ptrFun (arg)) / h;
}

template< typename T, T (*ptrFun)(T x) >
T backDiff(T arg, T h){
    return (ptrFun(arg) - ptrFun (arg - h)) / h;
}

template< typename T, T (*ptrFun)(T x) >
T centrDiff(T arg, T h){
    T l = T(2);
    return (ptrFun(arg + h) - ptrFun (arg - h)) / (l * h);
}

template< typename T, T (*ptrFun)(T x) >
T fdThreePoint(T arg, T h){
    return (T(-3) * ptrFun(arg) + T(4) * ptrFun(arg + h) - ptrFun(arg + T(2) * h)) / (T(2) * h);
}

template< typename T, T (*ptrFun)(T x) >
T bdThreePoint(T arg, T h){
    return (ptrFun(arg - T(2) * h) - T(4) * ptrFun(arg - h) + T(3) * ptrFun(arg)) / (T(2) * h);
}