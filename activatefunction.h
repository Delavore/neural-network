//#ifndef ACTIVATEFUNCTION_H
//#define ACTIVATEFUNCTION_H
#pragma once
#include <iostream>
#include <cmath>

enum activateFunc { sigmoid = 1, ReLU, thanx };

class ActivateFunction
{
private:
    activateFunc actFunc;
public:
    void set();
    void use(double* value, int n);
    void useDer(double* value, int n);
    double useDer(double value);
};

//#endif // ACTIVATEFUNCTION_H
