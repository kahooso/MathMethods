#include <iostream>

void iteration(double matrix[][4], const int rows, const int cols, double accuracy) {
	std::cout << "---------------------------" << std::endl;
	std::cout << "Метод итераций" << std::endl;
	double  d = 0, x[3], y[3];
	std::cout << std::endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {//без столбца свободных членов
			d = d + pow(matrix[i][j], 2);
		}
	}

	/*
		последовательность итераций сходится к решению системы, если
		квадратный корень из суммы квадратов коэффициентов при неизвестных меньше 1 
	*/

	if (sqrt(d) < 1) { //условие сходимости
		for (int i = 0; i < rows; i++) {
			x[i] = matrix[i][cols - 1];
		}
		d = 0;
		for (int i = 0; i < rows; i++) {
			y[i] = matrix[i][cols - 1];
			for (int j = 0; j < cols - 1; j++) {
				y[i] = y[i] + matrix[i][j] * x[j];
			}
			d = d + pow((y[i] - x[i]), 2);
		}
		while (sqrt(d) > accuracy) {
			for (int i = 0; i < rows; i++) {
				x[i] = y[i];
			}
			d = 0;
			for (int i = 0; i < rows; i++) {
				y[i] = matrix[i][cols - 1];
				for (int j = 0; j < cols - 1; j++) {
					y[i] = y[i] + matrix[i][j] * x[j];
				}
				d = d + pow((y[i] - x[i]), 2);//разница между старыми и новыми значениями
			}
		}
		for (int i = 0; i < rows; i++) { 
			for (int j = 0; j < cols; j++) {
				std::cout << matrix[i][j] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << "Решение: ";
		for (int i = 0; i < rows; i++) {
			std::cout << "x" << i << " = " << y[i] << std::endl;
		}
	}
	else {
		std::cout << "Условие сходимости не выполняется" << std::endl;
	}
	std::cout << "---------------------------" << std::endl;
}

void seidel(double matrix[][4], const int rows, const int cols, double accuracy) {
	std::cout << "---------------------------" << std::endl;
	std::cout << "Метод Зейделя" << std::endl;
	double d = 0, x[4], y[3];

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols - 1; j++) {
			if (j != i) {
				matrix[i][j] = -(matrix[i][j]) / matrix[i][i];//получаем итерац формулу(меняем те, которые не 0(где не а[i][i]))
				d = d + (pow(matrix[i][j], 2));
			}
		}
		matrix[i][cols - 1] = matrix[i][cols - 1] / matrix[i][i];
		matrix[i][i] = 0;
		x[i] = matrix[i][cols - 1];
	}
	std::cout << std::endl;
	for (int i = 0; i < rows; i++) {//массив
		for (int j = 0; j < cols; j++) {
			std::cout << matrix[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	if (sqrt(d) < 1) {
		d = 2 * accuracy; //задаем расстояние
		while (sqrt(d) > accuracy) {
			d = 0;
			for (int i = 0; i < rows; i++) {
				y[i] = matrix[i][cols - 1];//приравниваем к ст св членов
				for (int j = 0; j < cols - 1; j++) {
					y[i] = y[i] + matrix[i][j] * x[j];//считаем
				}
				d = d + (pow(y[i] - x[i], 2));
				x[i] = y[i];
			}
		}
		std::cout << std::endl << "Решение: " << std::endl;
		for (int i = 0; i < rows; i++) { 
			std::cout << "x" << i << " = " << x[i] << std::endl;
		}
	}
	else {
		std::cout << "Условие сходимости не выполняется" << std::endl;
	}
	std::cout << "---------------------------" << std::endl;
}

/*
	Блок-схема алгоритма метода Зейделя приведена на рис. 2.2.4. В отличие
	от алгоритма метода итераций здесь не нужно приводить вручную систему
	уравнений к виду 2.2.10. Это выполняется в самом алгоритме в первой паре
	вложенных циклов с параметрами i и j . Правда, предварительно исходную
	систему уравнений необходимо вручную привести к виду с максимальными по
	модулю коэффициентами на главной диагонали. Одновременно с приведением
	системы к виду 2.2.10 в этой части алгоритма подсчитывается сумма квадратов
	коэффициентов преобразованной системы. Эта сумма обозначена d .
	После проверки условия сходимости ( sqrt(d) < 1) переменной d обозначено
	расстояние между векторами двух последовательных итераций. Цикл
	получения итераций продолжается до тех пор, пока это расстояние не станет
	меньшим или равным требуемой точности accuracy.
	Для входа в этот цикл первоначально нужно сделать так, чтобы d было больше accuracy .
	Это сделано командой присвоения значения d = 2 * accuracy ,
	хотя можно сделать и любым другим способом.
	В отличие от метода итераций здесь каждая вновь полученная
	компонента очередной итерации используется для подсчета расстояния между
	итерациями и сразу заменяет соответствующую компоненту предыдущей итерации.
*/

int main()
{
	setlocale(LC_ALL, "Russian");
	const int rows = 3, cols = 4;
	double accuracy = 0.0001, matrix_for_seidel[rows][cols] = {
		{46.9, -2.64, 2.21, -34.56},
		{4.78, -12.2, 2.33, 36.48},
		{3.19, 1.58, -33.8, -75.53}
	};
	double matrix_for_iterations[rows][cols] = {
		{0,0.0563, -0.0471, -0.7369},
		{0.3918, 0, 0.1910, -2.9902},
		{0.0944, 0.0467, 0, 2.2346}
	};
	iteration(matrix_for_iterations, rows, cols, accuracy);
	seidel(matrix_for_seidel, rows, cols, accuracy);
}
