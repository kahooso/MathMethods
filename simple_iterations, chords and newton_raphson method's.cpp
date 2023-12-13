#include <iostream>

double f(double x);
double g(double x);
double simple_iterations(double a, double b, double accuracy);
double newton_raphson(double a, double b, double accuracy);
double chord(double a, double b, double accuracy);

int main() {
	setlocale(LC_ALL, "Russian");
    double a = 2.5, b = 2.6;
    double accuracy = 0.001;
	std::cout << "Метод простых итераций: " << simple_iterations(a, b, accuracy) << std::endl;
	std::cout << "Метод касательных: " << newton_raphson(a, b, accuracy) << std::endl;
	std::cout << "Метод хорд: " << chord(a, b, accuracy) << std::endl;
	return 0;
}

double f(double x) {
    return 2 * sin(x) - atan(x);
}
double g(double x) {
	return 2 * cos(x) - (1 / (x * x + 1));
}
double simple_iterations(double a, double b, double accuracy) {
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
	return x;
}
double chord(double a, double b, double accuracy) {
	double h = (b - a) / 100;
	double y = f(a);
	double d = f(a + 2 * h) - 2 * f(a + h) + f(a);
	double x0, x1;
	double c;
	double x;
	if (y * d < 0) {
		x0 = a;
		c = b;
	}
	else {
		x0 = b;
		c = a;
	}
	x1 = ((x0 * f(c)) - (c * f(x0))) / (f(c) - f(x0));
	do {
		x0 = x1;
		x1 = ((x0 * f(c)) - (c * f(x0))) / (f(c) - f(x0));
	} while (fabs(x1 - x0) > accuracy);
	x = x1;
	return x;
}
double newton_raphson(double a, double b, double accuracy) {
	double h = (b - a) / 100;
	double x = f(a);
	double y = f(a + 2 * h) - 2 * f(a + h) + f(a);
	double x0, x1;
	if (x * y > 0) {
		x0 = a;
	}
	else {
		x0 = b;
	}
	x1 = x0 - f(x0) / g(x0);
	do {
		x0 = x1;
		x1 = x0 - f(x0) / g(x0);
	} while (fabs(x1 - x0) > accuracy);
	x = x1;
	return x;
}

