#include "network.h"

void Network::Init(data_network data) {
    actFunc.set();
    srand(time(NULL));  // инициализируем генератор случайных чисел
    numberof_layers = data.numberof_layers;
    sizeof_layer = new int[numberof_layers];
    for (int i = 0; i < numberof_layers; i++)
        sizeof_layer[i] = data.sizeof_layer[i];

    weights = new Matrix[numberof_layers-1];
    bias = new double* [numberof_layers-1];
    for (int i = 0; i < numberof_layers - 1; i++) {
        weights[i].Init(sizeof_layer[i + 1], sizeof_layer[i]);
        bias[i] = new double[sizeof_layer[i + 1]];
        weights[i].Rand();
        for (int j = 0; j < sizeof_layer[i + 1]; j++)
            bias[i][j] = ((rand() % 50)) * 0.06 / (sizeof_layer[i] + 15);  // формула (зависимость)
    }

    neurons_value = new double* [numberof_layers];
    neurons_error = new double* [numberof_layers];
    for (int i = 0; i < numberof_layers; i++) {
        neurons_value[i] = new double[sizeof_layer[i]];
        neurons_error[i] = new double[sizeof_layer[i]];
    }

    neurons_bias_value = new double[numberof_layers-1];
    for (int i = 0; i < numberof_layers - 1; i++)
        neurons_bias_value[i] = 1;

}

void Network::PrintConfig() {
    std::cout << "*****\n"
              << "Number of layers: " << numberof_layers << "\n"
              << "Size[]: ";
    for (int i = 0; i < numberof_layers; i++)
        std::cout << sizeof_layer[i] << ' ';
    std::cout << "\n*****\n";
}

void Network::SetInput(double* values) {
    for (int i = 0; i < sizeof_layer[0]; i++)
        neurons_value[0][i] = values[i];
}

double Network::ForwardFeed() {
    for (int i = 1; i < numberof_layers; i++) {
        Matrix::Multiple(weights[i-1], neurons_value[i-1], sizeof_layer[i-1], neurons_value[i]);
        Matrix::SumVector(neurons_value[i], bias[i - 1], sizeof_layer[i]);
        actFunc.use(neurons_value[i], sizeof_layer[i]);


    }
    int pred = SearchMaxIndex(neurons_value[numberof_layers-1]);
    return pred;
}

int Network::SearchMaxIndex(double* value) {
    double maximum = value[0];
    int prediction = 0;
    double tmp;
    for (int i = 1; i < sizeof_layer[numberof_layers - 1]; i++) {
        tmp = value[i];
        if (tmp > maximum) {
            prediction = i;
            maximum = tmp;
        }
    }

    return prediction;
}

void Network::PrintValues(int numberof_layers) {
    for (int i = 0; i < sizeof_layer[numberof_layers]; i++)
        std::cout << i << " " << neurons_value[numberof_layers][i] << std::endl;
}

void Network::BackPropagation(double expect) {
    for (int i = 0; i < sizeof_layer[numberof_layers - 1]; i++) {
        if (i != int(expect))
            neurons_error[numberof_layers - 1][i] = -neurons_value[numberof_layers - 1][i] * actFunc.useDer(neurons_value[numberof_layers - 1][i]);
        else
            neurons_error[numberof_layers - 1][i] = (1.0 - neurons_value[numberof_layers - 1][i]) * actFunc.useDer(neurons_value[numberof_layers - 1][i]);
    }
    for (int k = numberof_layers - 2; k > 0; k--) {
        Matrix::Multiple_T(weights[k], neurons_error[k + 1], sizeof_layer[k + 1], neurons_error[k]);
        for (int j = 0; j < sizeof_layer[k]; j++)
            neurons_error[k][j] *= actFunc.useDer(neurons_value[k][j]);
    }
}

void Network::WeightsUpdater(double lr) {
    for (int i = 0; i < numberof_layers - 1; ++i) {
        for (int j = 0; j < sizeof_layer[i + 1]; ++j) {
            for (int k = 0; k < sizeof_layer[i]; ++k) {
                weights[i](j, k) += neurons_value[i][k] * neurons_error[i + 1][j] * lr;
            }
        }
    }
    for (int i = 0; i < numberof_layers - 1; i++) {
        for (int k = 0; k < sizeof_layer[i + 1]; k++) {
            bias[i][k] += neurons_error[i + 1][k] * lr;
        }
    }
}

void Network::SaveWeights() {
    std::ofstream fout;
    fout.open("Weights.txt");
    if (!fout.is_open()) {
        std::cout << "Error reading the file";
        system("pause");
    }
    for (int i = 0; i < numberof_layers - 1; ++i)
        fout << weights[i] << " ";

    for (int i = 0; i < numberof_layers - 1; ++i) {
        for (int j = 0; j < sizeof_layer[i + 1]; ++j) {
            fout << bias[i][j] << " ";
        }
    }
    std::cout << "Weights saved \n";
    fout.close();
}
void Network::ReadWeights() {
    std::ifstream fin;
    fin.open("Weights.txt");
    if (!fin.is_open()) {
        std::cout << "Error reading the file";
        system("pause");
    }
    for (int i = 0; i < numberof_layers - 1; ++i) {
        fin >> weights[i];
    }
    for (int i = 0; i < numberof_layers - 1; ++i) {
        for (int j = 0; j < sizeof_layer[i + 1]; ++j) {
            fin >> bias[i][j];
        }
    }
    std::cout << "Weights readed \n";
    fin.close();
}
