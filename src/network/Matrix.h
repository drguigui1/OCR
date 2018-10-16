#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix
{
	int rows;
	int columns;
	double *pt;
}Matrix;

Matrix init_matrix(int rows, int columns);
Matrix add_matrix(Matrix A, Matrix B);
Matrix hadamar_product(Matrix A, Matrix B);
Matrix transpose_matrix(Matrix A);
Matrix mult_matrix(Matrix A, Matrix B);
void apply_func(Matrix A, double (*sig) (double));
void mult_by_doubl(Matrix A, double b);
void print_matrix(Matrix A);
Matrix copy_matrix(Matrix A);

#endif
