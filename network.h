//#ifndef NETWORK_H
//#define NETWORK_H
#pragma once
#include "activatefunction.h"
#include "matrix.h"
#include <fstream>
#include <iostream>


struct data_network {
    int numberof_layers;
    int* sizeof_layer;
};

class Network
{
private:
    int numberof_layers;
    int* sizeof_layer;
    ActivateFunction actFunc;
    Matrix* weights;
    double** bias;
    double** neurons_value, ** neurons_error;
    double* neurons_bias_value;
public:
    void Init(data_network data);
    void PrintConfig();
    void SetInput(double* values);
    int SearchMaxIndex(double* value);
    double ForwardFeed();
    void PrintValues(int numberof_layers);
    void BackPropagation(double expect);
    void WeightsUpdater(double lr);
    void SaveWeights();
    void ReadWeights();
};

//#endif // NETWORK_H
