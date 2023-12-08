#include <iostream>

double f(double x) {
	return 2 * sin(x) - atan(x);
}

double g(double x) {
	return 2 * cos(x) - ((1) / (x * x + 1));
}

void метод_касетльных(double a, double b, double accuracy) {
	std::cout << "Метод касательных: " << std::endl;
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
	std::cout << "Корень: " << x << std::endl;
}

void horde(double a, double b, double accuracy) {
	std::cout << "Метод Хорд: " << std::endl;
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
	std::cout << "Корень: " << x << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	double a = 2.5, b = 2.6;
	double accuracy = 0.001;
	horde(a, b, accuracy);
	метод_касетльных(a, b, accuracy);
	return 0;
}