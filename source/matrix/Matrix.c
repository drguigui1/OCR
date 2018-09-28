#include <stdio.h>
#include <stdlib.h>


typedef struct Matrix
{
	int rows;
	int column;
	int *pt;
}Matrix;

Matrix init_matrix(int rows, int column);
Matrix add_matrix(Matrix A, Matrix B);
Matrix hadamar_product(Matrix C, Matrix D);

int main(void)
{
	/*Matrix m = init_matrix(5,5);
	*(m.pt + m.column + 1) = 5;
	for (int i = 0; i < m.rows; i++)
		for (int j = 0; j < m.column; j++)
			printf("%d ",*(m.pt + i*m.column + j));
	printf("\n");*/
	return 0;
}

/*---------------------------------------*/

//Matrix initialization
Matrix init_matrix(int rows, int column)
{
	Matrix M = {rows,column,(int *)malloc(rows * column * sizeof(int))};	

	//init
	for (int i = 0; i < rows; i++)
		for(int j = 0; j < column; j++)
			*(M.pt + i*column + j) = 0; //replace with Gaussian distribution

	return M;
}

/*--------------------------------------*/

//matrix addition
Matrix add_matrix(Matrix A, Matrix B)
{
	Matrix M = {A.rows,A.column,(int *)malloc(A.rows * A.column * sizeof(int))};
	//
	return M;
}

/*-------------------------------------*/

//Hadamar product
Matrix hadamar_product(Matrix A, Matrix B)
{

	Matrix M = {A.rows,A.column,(int *)malloc(A.rows * A.column * sizeof(int))};
	//
	return M;
}


