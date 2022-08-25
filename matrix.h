//  #ifndef MATRIX_H
//  #define MATRIX_H
#pragma once
#include <stdexcept>  // std::runtime_error
#include <cstdlib>  // std::rand

class Matrix {
private:
    double** matrix;
    int row, col;
public:
    void Init(int row, int col);  // инициализация матрицы (нулями), выделение памяти
    void Rand();  // случайное заполнение матрицы
    static void Multiple(const Matrix& input, const double* weights, int sizeof_weights, double* output);  // умножение входного слоя на веса
    static void SumVector(double* a, const double* b, int n);
    static void Multiple_T(const Matrix& input, const double* weights, int sizeof_weights, double* output);

    double& operator()(int i, int j);
    friend std::ostream& operator << (std::ostream& os, const Matrix& m);
    friend std::istream& operator >> (std::istream is, const Matrix& m);
};

//  #endif // MATRIX_H
