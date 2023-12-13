#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
	return x * x * x - 2 * x - 1;
}

double iterationMethod(double a, double b, double eps) {
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
}

int main() {
	setlocale(LC_ALL, "Russian");
	double a = 0, b = 3, eps = 0.000001;
	//cout << "Введите a: "; cin >> a;
	//cout << "Введите b: "; cin >> b;
	//cout << "Введите eps: "; cin >> eps;
	cout << "Корень, на промежутке [" << a << ", " << b << "]: " << iterationMethod(a, b, eps);
}
 /* 
	Функция должна быть непрерывна.
 */