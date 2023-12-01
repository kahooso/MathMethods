#include <iostream>

double f(double x);
double left_rectangles(const double a, const double b, const double eps);
double right_rectangles(const double a, const double b, const double eps);
double middle_rectangles(const double a, const double b, const double eps);
double trapezoid(const double a, const double b, const double eps);
double simpson(const double a, const double b);

int main() {
	const double eps = 0.001; //точность
	double a = 0.0, b = 0.5; /* пределы интегрирования */
	std::cout << "Integral solutions with diffrent methods." << std::endl;
	std::cout << "left rectangles method: \t" << left_rectangles(a, b, eps) << std::endl;
	std::cout << "right rectangles method: \t" << right_rectangles(a, b, eps) << std::endl;
	std::cout << "middle rectangles method: \t" << middle_rectangles(a, b, eps) << std::endl;
	std::cout << "trapez method: \t\t\t" << trapezoid(a, b, eps) << std::endl;
	std::cout << "Simpson method: \t\t" << simpson(a, b) << std::endl;
}

double f(const double x) {
	return (1 / sqrt(1 - pow(x, 2)));
}

double left_rectangles(const double a, const double b, const double eps) {
	double l0 = 0, l1 = INFINITY; // текущее и предыдущее значение интеграла
	unsigned int n = 5; // число отрезков
	double h = 0; // длина одного отрезка
	double x = 0;
	while (fabs(l1 - l0) > eps) {
		n = 2 * n;
		l0 = l1;
		h = (b - a) / n;
		l1 = 0;
		for (int i = 0; i < n - 1; i++) {
			x = a + i * h;
			l1 = l1 + f(x);
		}
		l1 = l1 * h;
	}
	return l1;
}

double right_rectangles(const double a, const double b, const double eps) {
	double l0 = 0, l1 = INFINITY; // текущее и предыдущее значение интеграла
	unsigned int n = 5; // число отрезков
	double h = 0; // длина одного отрезка
	double x = 0;
	while (fabs(l1 - l0) > eps) {
		n = 100 * n;
		l0 = l1;
		h = (b - a) / n;
		l1 = 0;
		for (int i = 1; i <= n; i++) {
			x = a + (i + 1) * h;
			l1 = l1 + f(x);
		}
		l1 = l1 * h;
	}
	return l1;
}

double middle_rectangles(const double a, const double b, const double eps) {
	double l0 = 0, l1 = INFINITY; // текущее и предыдущее значение интеграла
	unsigned int n = 5; // число отрезков
	double h = 0; // длина одного отрезка
	double x = 0;
	while (fabs(l1 - l0) > eps) {
		n = 2 * n;
		l0 = l1;
		h = (b - a) / n;
		l1 = 0;
		for (int i = 0; i < n; i++) {
			x = a + (h / 2) + i * h;
			l1 = l1 + f(x);
		}
		l1 = l1 * h;
	}
	return l1;
}

double trapezoid(const double a, const double b, const double eps)
{
	double l0 = 0, l1 = INFINITY;
	unsigned int n = 5;
	while (abs(l1 - l0) > eps) {
		n = n * 2;
		l0 = l1;
		double h = (b - a) / n;
		double s = (f(a) + f(b)) / 2;
		for (int i = 0; i < n; ++i) {
			s = s + f(a + i * h);
		}
		l1 = s * h;
	}
	return l1;
}

double simpson(const double a, const double b) {
	int n = 10;
	double s = 0;
	double h = (b - a) / n;
	int odd;
	for (unsigned int i = 1; i <= n; i++)
	{
		odd = 2 + 2 * (i % 2);
		s += odd * f(a + i * h);
	}
	s = s * (h / 3);
	return s;
}
