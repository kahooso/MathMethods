
#include <iostream>

double f(double x, double y) {
	return (3 / x) - (y / x);
}

void euler(double x, double y, double h, double last_x) {
	std::cout << "Метод Эйлера" << std::endl;
	do {
		y += h * f(x, y);
		x += h;
	} while (x <= last_x);
	std::cout << "y: " << y << std::endl;
	std::cout << "------------------------------------" << std::endl;
}

void exact_euler(double x, double y, double h, double last_x) {
	std::cout << "Уточнённый метод Эйлера: " << std::endl;
	double y2 = y + f(x, y) * h / 2;
	std::cout << "y(1/2) = " << y2 << std::endl;
	y2 = y + f(x + h / 2, y2) * h;
	std::cout << "y1 = " << y2 << std::endl;
	x += h;
	double y3;
	while (x <= last_x) {
		y3 = y + 2 * h * f(x, y2);
		y = y2;
		y2 = y3;
		x += h;
	}
	std::cout << "y: " << y2 << std::endl;
	std::cout << "------------------------------------"  << std::endl;
}

void runge_kutta(double x, double y, double h, double last_x) {
	std::cout << "Метод Рунге-Кутта: " << std::endl;
	double alph = 0.25;
	std::cout << "x = " << x << " y = " << y << std::endl;
	for (double i = x; i < last_x; i += h)
	{
		double k1 = f(x, y);
		double k2 = f(x + h / (2 * alph), y + h / (2 * alph) * k1);
		y += h * ((1 - alph) * k1 + alph * k2);
		x += h;
		std::cout << "x: " << x << " " << " y: " << y << std::endl;
	}
	std::cout << "------------------------------------" << std::endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	double x = 1, y = 0, h = 0.1, last_x = 2;
	euler(x, y, h, last_x);
	exact_euler(x, y, h, last_x);
	runge_kutta(x, y, h, last_x);
}