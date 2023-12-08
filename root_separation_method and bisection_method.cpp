#include <iostream>
#include <cmath>
#include <limits>

using std::cout;
using std::endl;

double accuracy = 0.001;

/* Функция */
double f(double x);

/* Метод отделения корня */
void rootSeparationMethod(double a, double b, double step);

/* Метод половинного деления */
double bisectionMethod(double a, double b, double accuracy);

int main() {
    double a = -8, b = 2, step = 0.1;
    rootSeparationMethod(a, b, step);
}

/* Функция */
double f(double x) {
    return 2 * sin(x) - atan(x);
}

/* Метод отделения корня */
void rootSeparationMethod(double a, double b, double step) {
    double x1 = a;
    double x2 = a + step;
    double y1 = f(x1);
    while (x2 <= b) {
        double y2 = f(x2);
        if (y1 * y2 <= 0) {
            cout << "There is a root between [" << x1 << " and " << x2 << "]\t ";
            double root = bisectionMethod(x1, x2, accuracy);
            cout << "x = " << root << endl;
        }
        x1 = x2;
        x2 += step;
        y1 = y2;
    }
}

/* Метод половинного деления */
double bisectionMethod(double a, double b, double accuracy) {
    double middle = (a + b) / 2;
    if (f(a) * f(b) > 0) {
        return NAN;
    }
    while ((b - a) > accuracy) {
        middle = (a + b) / 2;
        if (f(a) * f(middle) < 0) {
            b = middle; /* влево */
        }
        else {
            a = middle; /* вправо */
        }
    }
    return middle;
}