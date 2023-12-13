#include <iostream>
#include <cmath>

double determinant(double matrix[][3], int size, double accuracy);
void gauss(double matrix[][4], const int rows, const int cols);
bool check_out_method(double matrix[][4], const int rows, const int cols, const double accuracy);
//void matrix_inverse(double matrix[][4], const int rows, const int cols, double determinant);

int main() {
    setlocale(LC_ALL, "Russian");
    const double accuracy = 0.0001;
    const int rows = 3, cols = 4;
    double matrix[rows][cols]{
        {5, 6, -7, 24},
        {-6, 2, 2, -4},
        {5, -6, -6, -1}
    };
    double matrix_determinant[rows][cols - 1]{
        {5, 6, -7},
        {-6, 2, 2},
        {5, -6, -6}
        //{1, 2, 3},
        //{2, 4, 6},
        //{3, 6, 9}
    };
    double inverse_matrix[rows][cols]{
        {5, 6, -7, 24},
        {-6, 2, 2, -4},
        {5, -6, -6, -1}
    };

    if (!check_out_method(matrix, rows, cols, accuracy)) {
        if (determinant(matrix_determinant, 3, accuracy) != 0) {
            gauss(matrix, rows, cols);
            //matrix_inverse(inverse_matrix, rows, cols, determinant(matrix_determinant, 3, accuracy));
        }
    }
    return 0;
}

bool check_out_method(double matrix[][4], const int rows, const int cols, const double accuracy) {
    for (int i = 0; i < rows; i++)
    {
        double max_fabs = fabs(matrix[i][i]);
        int max_fabs_index = i; // Номер строки с максимальным элементом

        for (int k = i; k < rows; k++)
        {
            if (fabs(matrix[k][i]) > max_fabs) {
                max_fabs = fabs(matrix[k][i]);
                max_fabs_index = k;
            }
        }

        if (max_fabs < accuracy) {
            std::cout << "Матрица вырожденная!" << std::endl;
            return true;
        }
        else {
            if (max_fabs_index != i) {
                for (int j = 0; j < cols; j++)
                {
                    std::swap(matrix[i][j], matrix[max_fabs_index][j]);
                }
            }
        }
    }
    return false; // Матрица не вырожденная
}
double determinant(double matrix[][3], int size, const double accuracy)
{
    int pivot_index = 0;
    double pivot_value = 0;
    double determinant = 1;
    for (int i = 0; i < size; i++)
    {
        pivot_index = i;
        pivot_value = fabs(matrix[i][i]);
        for (int j = i + 1; j < size; j++)
        {
            if (fabs(matrix[j][i]) > pivot_value)
            {
                pivot_index = j;
                pivot_value = fabs(matrix[j][i]);
            }
        }
        if (pivot_value < accuracy) { std::cout << "Вырожденная матрица!" << std::endl; return 0; }
        if (pivot_index != i)
        {
            std::swap(matrix[pivot_index], matrix[i]);
            determinant *= -1;
        }
        for (int j = i + 1; j < size; j++)
        {
            double multiplier = matrix[j][i] / matrix[i][i];
            for (int k = i; k < size; k++)
            {
                matrix[j][k] -= matrix[i][k] * multiplier;
            }
        }
        determinant *= matrix[i][i];
    }
    std::cout << "Определить матрицы: " << determinant << std::endl;
    std::cout << std::endl;
    return determinant;
}
void gauss(double matrix[][4], const int rows, const int cols) {
    std::cout << "Метод Гаусса: " << std::endl;
    std::cout << "Дана матрица: " << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

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
    std::cout << "Преобразованная матрица: " << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    double roots[3];
    std::cout << "\nКорни: " << std::endl;
    for (int i = 0; i < rows; i++) {
        roots[i] = matrix[i][cols - 1];
        std::cout << "x" << i << " = " << roots[i] << std::endl;
    }
    std::cout << std::endl;
}
//void matrix_inverse(double matrix[][4], const int rows, const int cols, double determinant) {
//    double inverse_determinant = 1 / determinant;
//    std::cout << "Обратный определить матрицы: " << inverse_determinant << std::endl << std::endl;
//    std::cout << "Обратная матрица: " << std::endl;
//    for (int i = 0; i < rows; i++)
//    {
//        for (int j = 0; j < cols; j++)
//        {
//            matrix[i][j] *= inverse_determinant;
//            std::cout << matrix[i][j] << "\t";
//        }
//        std::cout << std::endl;
//    }
//}
