#include <stdio.h>
#include <stdlib.h>


typedef struct Matrix
{
	int rows;
	int columns;
	int *pt;
}Matrix;

Matrix init_matrix(int rows, int columns);
Matrix add_matrix(Matrix A, Matrix B);
Matrix hadamar_product(Matrix C, Matrix D);

int main(void)
{
	/*Matrix m = init_matrix(5,5);
	*(m.pt + m.columns + 1) = 5;
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.columns; j++)
			printf("%d ",*(m.pt + i*m.column + j));
	printf("\n");*/
	return 0;
}

/*---------------------------------------*/

//Matrix initialization
Matrix init_matrix(int rows, int columns)
{
	Matrix M = {rows,columns,(int *)malloc(rows * columns * sizeof(int))};	

	//init
	for (int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++)
			*(M.pt + i*columns + j) = 0; //replace with Gaussian distribution

	return M;
}

/*--------------------------------------*/

//matrix addition
Matrix add_matrix(Matrix A, Matrix B)
{
	Matrix M = {A.rows,A.columns,(int *)malloc(A.rows * A.columns * sizeof(int))};
	for (int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++)
			*(M.pt + i*columns + j) = *(A.pt + i*columns + j) + *(B.pt + i*columns + j);
	return M;
}

/*-------------------------------------*/

//Hadamar product
Matrix hadamar_product(Matrix A, Matrix B)
{

	Matrix M = {A.rows,A.columns,(int *)malloc(A.rows * A.columns * sizeof(int))};
	for (int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++)
			*(M.pt + i*columns + j) = *(A.pt + i*columns + j) * *(B.pt + i*columns + j);
	return M;
}


