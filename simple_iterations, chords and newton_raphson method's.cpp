#include <iostream>

double f(double x);
double g(double x);
double simple_iterations(double a, double b, double eps);
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

double simple_iterations(double a, double b, double eps) {
	double h = (b - a / 100); /* шаг для разбиения интервала[a, b] */
	double x0 = (b + a) / 2;  /* Начальное приблежение к корю, среднее значение между a и b */
	double x = a;
	double y = a + h;
	double M = (fabs(f(y) - f(x)) / h); /* Оценка максимальной производной f(x) на интервале a и b */
	double C;

	while (y < b) {
		x = y;
		y = x + h;
		/* Берем две точки */
		C = (fabs(f(y) - f(x)) / h); /* Смотрим насколько f(y) - f(x) различаются */
		if (C > M) {
			M = C;
			/* Если разница велика, это становится оценочным значение
				быстроты изменения функции на интервале.
			*/
		}
	}

	M++; /* Увеличиваем на 1. Нужно для того, чтобы учесть длинну интервала */

	C = f(a) < f(b) ? 1 : -1;

	/*
		В зависимости какое значение больше выбераем направление, в котором двигаться к корню.
		Если f(a) ближе к 0, идем в положительном направлении.
		Если наоборот, идем в отрицательном направлении.
	*/

	double x1 = x0 - C * (f(x0) / M);

	/*
		Теперь начиная с точки x0 используем формулу x1 = ..., для поиска следующей точки.
		Повторяем этот шаг, пока разница между x1 и x0 не станет меньше, чем наша точность.

	*/

	while (fabs(x1 - x0) > eps) {
		x0 = x1;
		x1 = x0 - C * (f(x0) / M);
	}

	/*
		Как только разница стала достаточно маленькой, (меньше eps), x1 считается приблеженным корнем уравнения.
	*/
	x = x1;
	return x;
	/*
		Функция должна быть непрерывна.
	*/
}


