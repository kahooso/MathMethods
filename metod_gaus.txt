#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void methodGauss(double matrix[][4], const int rows, const int cols) {
	// Вывод исходной матрицы
	cout << "Дана матрица: " << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < rows; i++) {
		for (int j = cols - 1; j >= i; j--) {
			matrix[i][j] = matrix[i][j] / matrix[i][i];
		}
		for (int k = 0; k < rows; k++) {
			if (k != i) {
				for (int j = cols - 1; j >= i; j--) {
					matrix[k][j] = matrix[k][j] - (matrix[k][i] * matrix[i][j]);
				}
			}
		}
	}
	cout << "Преобразованная матрица: " << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	double roots[3];
	cout << "\nКорни: " << endl;
	for (int i = 0; i < rows; i++) {
		roots[i] = matrix[i][cols - 1]; 
		cout << "x" << i << " = " << roots[i] << endl;
	}
}

bool checkOutMethod(double matrix[][4], const int rows, const int cols) {
	for (int i = 0; i < rows; i++)
	{
		int maxFabs = fabs(matrix[i][i]);
		int l = i; //номер максимума
		for (int k = i; k < cols; k++)
		{
			if (maxFabs < matrix[k][i]) {
				maxFabs = fabs(matrix[k][i]);
				l = k;
			}
			for (int k = i; k < cols; k++)
			{
				if (matrix[j][i] > maxFabs) {
					maxFabs = fabs(matrix[j][i]);
					l = j;
				}
			}
		}
		if (maxFabs < 0.001) {
			cout << "Матрица вырожденная!" << endl;
			return true;
		}
		else {
			for (int j = 0; j < cols; j++)
			{
				matrix[i][j] = matrix[l][i];
			}
		}
	}
	return false;
}

int main() {
	setlocale(LC_ALL, "Russian");
	const int rows = 3;
	const int cols = 4;
	double matrix[rows][cols]{
		{8.39, -8.99, -1.29, 8.86},
		{-1.05, 1.89, 4.91, 4.20},
		{-6.38, 8.36, 0.48, -5.06}
	};
	bool check = checkOutMethod(matrix, rows, cols);
	if (check) {
		return 0;
	}
	else {
		methodGauss(matrix, rows, cols);
	}
}
