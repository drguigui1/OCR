#include <stdio.h>
#include <stdlib.h>

#include "../../Headers/Matrix.h"

struct Matrix
{
	int rows;
	int columns;
	int *pt;
};

int main()
{
	/*Matrix m = init_matrix(5,5);
	*(m.pt + m.columns - 1) = 5;
	//m = transpose_matrix(m);
	
	for (int i = 0; i < m.rows; i++)
	{
		for (int j = 0; j < m.columns; j++)
			printf("%d ",*(m.pt + i*m.columns + j));
		printf("\n");
	}*/
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
	for (int i = 0; i < M.rows; i++)
		for(int j = 0; j < M.columns; j++)
			*(M.pt + i*M.columns + j) = *(A.pt + i*M.columns + j) + *(B.pt + i*M.columns + j);
	return M;
}

/*-------------------------------------*/

//Hadamar product
Matrix hadamar_product(Matrix A, Matrix B)
{

	Matrix M = {A.rows,A.columns,(int *)malloc(A.rows * A.columns * sizeof(int))};
	for (int i = 0; i < M.rows; i++)
		for(int j = 0; j < M.columns; j++)
			*(M.pt + i*M.columns + j) = *(A.pt + i*M.columns + j) * *(B.pt + i*M.columns + j);
	return M;
}

/*-------------------------------------*/

//Matrix transpose
Matrix transpose_matrix(Matrix A)
{
	Matrix B = {A.columns, A.rows, (int *)malloc(A.rows * A.columns * sizeof(int))};
	for (int i = 0; i < B.rows; i++)
		for(int j = 0; j < B.columns; j++)
			*(B.pt + i*B.columns + j) = *(A.pt + i + j*B.columns);
	return B;
}

