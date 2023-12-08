#include <iostream>
#include <cmath>

double f(double x) {
    return 2 * sin(x) - atan(x);
}

void simpleIterations(double a, double b, double accuracy) {
    double h = (b - a) / 100, /* Шаг */
        x0 = (a + b) / 2, /* x0 - начальное приближение */
        C; /* Знак производной */
    double x = a, y = a + h, M = (f(y) - f(x)) / h;
    do {
        x = y; //преобразуем к виду x = f(x)
        y = x + h;
        C = fabs(f(y) - f(x)) / h;

        if (C > M) {
            M = C;
        }
    } while (C > M);
    ++M;
    C = f(a) < f(b) ? 1 : -1;
    double x1 = x0 - C * (f(x0) / M);
    do {
        x0 = x1;
        x1 = x0 - C * f(x0) / M;
    } while (fabs(x1 - x0) > accuracy);
    x = x1;
    std::cout << "The root is " << x << std::endl;
}

int main() {
    double a = 2.5, b = 2.6;
    double accuracy = 0.001;
    simpleIterations(a, b, accuracy);
    return 0;
}