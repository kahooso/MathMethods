#include <iostream>
#include <cmath>

void methodOfSimpleIteration(double matrix[3][4], double e) {
    double x[3] = { 0 }, y[3] = { 0 };
    int max_iterations = 1000;
    int iteration = 0;

    for (int i = 0; i < 3; ++i) {
        x[i] = matrix[i][3];
        std::cout << "Начальное X" << i << ": " << x[i] << std::endl;
    }

    double d = 0;
    while (true) {
        for (int i = 0; i < 3; ++i) {
            y[i] = matrix[i][3];
            for (int j = 0; j < 3; ++j) {
                y[i] += matrix[i][j] * x[j];
            }
            d += pow(y[i] - x[i], 2);
        }
        d = sqrt(d);
        if (d > e && iteration < max_iterations) {
            for (int i = 0; i < 3; ++i) {
                x[i] = y[i]; // Обновляем значения переменной x
            }
        }
        else {
            for (int i = 0; i < 3; ++i) {
                std::cout << "x" << i << ": " << x[i] << std::endl;
            }
            break;
        }
        ++iteration;
    }
}
int main() {
    setlocale(LC_ALL, "Russian");
    const int rows = 3, cols = 4;
    double e = 0.001;
    double matrix[rows][cols] = {
        {2, 3, -1, 5},
        {3, -1, 4, 13},
        {5, -2, 2, 7}
    };
    methodOfSimpleIteration(matrix, e);
}
