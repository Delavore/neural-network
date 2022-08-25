#include "activatefunction.h"


void ActivateFunction::set() {
    std::cout << "Set actFunc\n1 - sigmoid \n2 - ReLu\n3 - thanx\n";

    int number_of_func;
    std::cin >> number_of_func;
    switch(number_of_func) {
    case sigmoid:
        actFunc = sigmoid;
        break;
    case ReLU:
        actFunc = ReLU;
        break;
    case thanx:
        actFunc = thanx;
        break;
    default:
        throw std::runtime_error("Error read actFunc");
    }
}

void ActivateFunction::use(double* input, int sizeof_input) {
    switch (actFunc) {
    case activateFunc::sigmoid:
        for (int i = 0; i < sizeof_input; i++)
            input[i] = 1 / (1 + exp(-input[i]));
        break;
    case activateFunc::ReLU:
        for (int i = 0; i < sizeof_input; i++) {
            if (input[i] < 0)
                input[i] *= 0.01;
            else if (input[i] > 1)  // ограничили сверху, чтобы значения лежали в диапазоне от 0 до 1
                input[i] = 1. + 0.01 * (input[i] - 1.);
            //  else input[i] = input[i]

        }
        break;
    case activateFunc::thanx:
        for (int i = 0; i < sizeof_input; i++) {
            //  ограничен снизу у 0
            if (input[i] < 0)
                input[i] = 0.01 * (exp(input[i]) - exp(-input[i])) / (exp(input[i]) + exp(-input[i]));
            else
                input[i] = (exp(input[i]) - exp(-input[i])) / (exp(input[i]) + exp(-input[i]));
        }
    }
}

void ActivateFunction::useDer(double* input, int sizeof_input) {
    switch (actFunc) {
    case activateFunc::sigmoid:
        for (int i = 0; i < sizeof_input; i++)
            input[i] = input[i] * (1 - input[i]);
        break;
    case activateFunc::ReLU:
        for (int i = 0; i < sizeof_input; i++) {
            if (input[i] < 0 || input[i] > 1)
                input[i] = 0.01;
            else
                input[i] = 1;
        }
        break;

    case activateFunc::thanx:
        for (int i = 0; i < sizeof_input; i++) {
            if (input[i] < 0)
                input[i] = 0.01 * (1 - input[i] * input[i]);
            else
                input[i] = 1 - input[i] * input[i];
        }
        break;
    default:
        throw std::runtime_error("errr actFuncDer \n");
    }
}

double ActivateFunction::useDer(double value) {
    switch (actFunc) {
    case activateFunc::sigmoid:

            value = value * (1 - value);
        break;
    case activateFunc::ReLU:

            if (value < 0 || value > 1)
                value = 0.01;
            else
                value = 1;

        break;

    case activateFunc::thanx:

            if (value < 0)
                value = 0.01 * (1 - value * value);
            else
                value = 1 - value * value;

        break;
    default:
        throw std::runtime_error("errr actFuncDer \n");
    }
    return value;
}
