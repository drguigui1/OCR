#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

#include <math.h>

/*------------------------*/

/*typedef struct Network
{
	struct StoreMatrix*** pt_weights;
	struct StoreMatrix*** pt_bias;
	struct StoreMatrix*** pt_outputs;
}Network;*/


typedef struct StoreMatrix
{
	struct Matrix* matrices;
}StoreMatrix;


//constructeur

StoreMatrix init_ListMatrix(int nb_matrix)
{
	StoreMatrix l_matrix = {malloc(sizeof(struct Matrix) * nb_matrix)};
	return l_matrix;
}

/*-------------------------*/

//functions
/*-------------------------*/

void init_all(StoreMatrix Weights, StoreMatrix Bias, Matrix sizes, int length);
void feedforward(StoreMatrix Weights, StoreMatrix Bias, StoreMatrix Outputs, Matrix sizes, int length);
double sigmoid(double a);
double sigmoidprime(double b);

/*-------------------------*/

int main(void)
{
	//init sizes = [2,3,2]
	Matrix sizes = init_matrix(1, 3);
	*(sizes.pt) = 2;
	*(sizes.pt + 1) = 3;
        *(sizes.pt + 2) = 2;

	int length = sizeof(sizes)/sizeof(int);

	StoreMatrix Weights = init_ListMatrix(length-1);	
	StoreMatrix Bias = init_ListMatrix(length-1);
	StoreMatrix Outputs = init_ListMatrix(length);

	//declare Input
	*(Outputs.matrices) = init_matrix(2,1);

	init_all(Weights, Bias, sizes, length);
	feedforward(Weights, Bias, Outputs, sizes, length);	
	//Weights
	printf("Weights\n");
	for (int i = 0; i < (length-1); i++)
	{
		print_matrix(*(Weights.matrices + i));
		printf("\n");	
	}
	
	//biases
	printf("Biases\n");
	for (int j = 0; j < (length-1); j++)
	{
		print_matrix(*(Bias.matrices + j));
		printf("\n");
	}

	//Outputs
	printf("Outputs\n");
	for (int k = 0; k < length; k++)
	{
		print_matrix(*(Outputs.matrices + k));
		printf("\n");
	}
	printf("|----------------------|\n");

	//double b = 0.22;
	//mult_by_doubl(sizes, b);
	//apply_func(sizes, sigmoid);
	//print_matrix(sizes);
	

	return 0;
}


/*----------------------------*/


/*----------functions for the network--------------*/

void init_all(StoreMatrix Weights, StoreMatrix Bias, Matrix sizes, int length)
{
	
	//creat three struct of matrix 
	//first for Weights
	for (int i = 0; i < (length-1); i++)
		*(Weights.matrices + i) = init_matrix(*(sizes.pt + i+1),*(sizes.pt + i));

	//second for Bias
	for (int j = 0; j < (length-1); j++)
		*(Bias.matrices + j) = init_matrix(*(sizes.pt + j+1),1);

}

/*------------------------*/

void feedforward(StoreMatrix Weights, StoreMatrix Bias, StoreMatrix Outputs, Matrix sizes, int length)
{
	//first Matrix of Outputs : the input of the network
	
	for (int i = 0; i < length-1; i++) //parcours du reseau
	{
		Matrix W = *(Weights.matrices + i);
		Matrix O = *(Outputs.matrices + i);
		Matrix B = *(Bias.matrices + i);
		Matrix tab = init_matrix(W.rows, 1);

		tab = add_matrix(mult_matrix(W, O), B);
		apply_func(tab, sigmoid);
		*(Outputs.matrices + i + 1) = tab;
	}

}

//int g (int (*f)(char))

/*----------Math functions--------------*/

//sigmoid
double sigmoid(double a)
{
	return 1/(1+exp(-a));
}

//sigmoid prime
double sigmoidprime(double a)
{
	return a*(1-a);
}

