#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "Matrix.h"


//Matrix initialization
Matrix init_matrix(int rows, int columns)
{
	Matrix M = {rows,columns, malloc(rows * columns * sizeof(int))};	

	//init random generator
	srand(time(NULL));
	//
	//init
	for (int i = 0; i < rows; i++)
		for(int j = 0; j < columns; j++)
		{
			int r = rand() % 3;
			*(M.pt + i*columns + j) = r; //replace with Gaussian distribution
		}
	return M;
}

/*--------------------------------------*/

//matrix addition
Matrix add_matrix(Matrix A, Matrix B)
{
	Matrix M = {A.rows,A.columns, malloc(A.rows * A.columns * sizeof(int))};
	for (int i = 0; i < M.rows; i++)
		for(int j = 0; j < M.columns; j++)
			*(M.pt + i*M.columns + j) = *(A.pt + i*M.columns + j) + *(B.pt + i*M.columns + j);
	return M;
}

/*-------------------------------------*/

//Hadamar product
Matrix hadamar_product(Matrix A, Matrix B)
{

	Matrix M = {A.rows,A.columns, malloc(A.rows * A.columns * sizeof(int))};
	for (int i = 0; i < M.rows; i++)
		for(int j = 0; j < M.columns; j++)
			*(M.pt + i*M.columns + j) = *(A.pt + i*M.columns + j) * *(B.pt + i*M.columns + j);
	return M;
}

/*-------------------------------------*/

//Matrix transpose
Matrix transpose_matrix(Matrix A)
{
	Matrix B = {A.columns, A.rows, malloc(A.rows * A.columns * sizeof(int))};
	for (int i = 0; i < B.rows; i++)
		for(int j = 0; j < B.columns; j++)
			*(B.pt + i*B.columns + j) = *(A.pt + i + j*B.columns);
	return B;
}

/*-------------------------------------*/

//Matrix multiplication
Matrix mult_matrix(Matrix A, Matrix B)
{
	Matrix M = {A.rows, B.columns, malloc(A.rows * B.columns * sizeof(int))};
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

/*-------------------------------------*/

//print Matrix
void print_matrix(Matrix A)
{
	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.columns; j++)
			printf("%d ", *(A.pt + i*A.columns + j));
		printf("\n");
	}
}


