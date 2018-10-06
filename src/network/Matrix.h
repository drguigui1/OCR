typedef struct Matrix
{
	int rows;
	int columns;
	int *pt;
}Matrix;

Matrix init_matrix(int rows, int columns);
Matrix add_matrix(Matrix A, Matrix B);
Matrix hadamar_product(Matrix A, Matrix B);
Matrix transpose_matrix(Matrix A);
Matrix mult_matrix(Matrix A, Matrix B);
void print_matrix(Matrix A);
