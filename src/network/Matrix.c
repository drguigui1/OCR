#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

/*
int main()
{
	Matrix m1 = init_matrix(2,3);
	Matrix m2 = init_matrix(3,2);
	
	Matrix m3;

	*(m1.pt) = 1;
	*(m1.pt + 1) = 2;
	*(m1.pt + 2) = 0;
	*(m1.pt + m1.columns) = 4;
	*(m1.pt + m1.columns + 1) = 3;
	*(m1.pt + m1.columns + 2) = -1;

	*(m2.pt) = 5;
	*(m2.pt + 1) = 1;
	*(m2.pt + m2.columns) = 2;
	*(m2.pt + m2.columns + 1) = 3;
	*(m2.pt + 2*m2.columns) = 3;
	*(m2.pt + 2*m2.columns + 1) = 4;

		m3 = mult_matrix(m1, m2);

	for (int i = 0; i < m3.rows; i++)
	{
		for (int j = 0; j < m3.columns; j++)
			printf("%d ",*(m3.pt + i*m3.columns + j));
		printf("\n");
	}
	return 0;
}*/

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

/*-------------------------------------*/

//Matrix multiplication
Matrix mult_matrix(Matrix A, Matrix B)
{
	Matrix M = {A.rows, B.columns, (int *)malloc(A.rows * B.columns * sizeof(int))};
	if (A.columns != B.rows)
	{
		printf("ERROR MATRIX SIZE !\n");
	}
	else
	{
		for (int i = 0; i < A.rows; i++)
			for (int j = 0; j < B.columns; j++)
				for (int k = 0; k < A.columns; k++)
					*(M.pt + i*M.columns + j) += (*(A.pt + i*A.columns + k)) * (*(B.pt + k*B.columns + j)); 
	}
	return M;
}

