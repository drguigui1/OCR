#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

#include <math.h>

typedef struct Network
{
	int nb_layers;
	//Matrix *pt_b; // matrix of biases
	//Matrix *pt_w; // pt of matrix type
}Network;


//functions
Network init_all(int *pt); //pt on the list of number layers
double sigmoid(double a);
double sigmoidprime(double b);
//

int main(void)
{
	Matrix M;
	M = init_matrix(3,3);
	for (int i = 0; i < M.rows; i++)
	{
		for (int j = 0; j < M.columns; j++)
                	printf("%d", *(M.pt + i*M.columns + j));
		printf("\n");
	}
	return 0;
}


/*----------------------------*/

/*
//don't forget to declare the list sizes
Network init_all(int *p, int size) //pt of th list of number layer
{
	Network net = {size, init_matrix()};
	

	//init weights/biases/sizes
	//return Network object
}*/


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

