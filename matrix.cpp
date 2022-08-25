#include "matrix.h"

void Matrix::Init(int row, int col) {
    this->row = row;
    this->col = col;

    //  выделение памяти
    matrix = new double* [row];
    for (int i = 0; i < row; i++)
        matrix[i] = new double[col];

    //  инициализация 0
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = 0;
}

void Matrix::Rand() {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            matrix[i][j] = ((rand() % 100)) * 0.03 / (row + 35);  //  генерации псевдослучайных чисел, заполнение ими матрицы
}

//  выполняем умножение по правилу умножения матриц
void Matrix::Multiple(const Matrix& input, const double* weights, int sizeof_weights, double* output) {

    //  столбцы первой матрицы должны быть равны столбцам второй матрицы
    if (input.col != sizeof_weights)
        throw std::runtime_error("Error Multiple\n");

    for (int i = 0; i < input.row; i++) {
        double tmp = 0;
        for (int j = 0; j < input.col; j++)
            tmp += input.matrix[i][j] * weights[j];
        output[i] = tmp;
    }
}

void Matrix::SumVector(double* input, const double* bias, int sizeof_weights) {
    for (int i = 0; i < sizeof_weights; i++)
        input[i] += bias[i];
}

void Matrix::Multiple_T(const Matrix& input, const double* weights, int sizeof_weights, double* output) {
    if (input.row != sizeof_weights)
        throw std::runtime_error("Error Multiple\n");

    for (int i = 0; i < input.col; i++) {
        double tmp = 0;
        for (int j = 0; j < input.row; j++)
            tmp += input.matrix[i][j] * weights[j];
        output[i] = tmp;
    }
}

double& Matrix::operator ()(int i, int j) {
    return matrix[i][j];
}


std::ostream& operator << (std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; j++) {
            os << m.matrix[i][j] << " ";
        }
    }
    return os;
}
std::istream& operator >> (std::istream& is, Matrix& m) {
    for (int i = 0; i < m.row; ++i) {
        for (int j = 0; j < m.col; j++) {
            is >> m.matrix[i][j];
        }
    }
    return is;
}
