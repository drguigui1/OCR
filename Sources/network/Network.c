#include <stdio.h>
#include <stdlib.h>

#include "./../../Headers/Matrix.h"

#include <math.h>

typedef struct Network
{
	int nb_layers;
	//sizes : list of int representing the nb of neuron per layer
	//biases : matrix of biases
	//weights : list of Matrix containing all weights of the network
}Network;


//functions
//Network init_all(/*sizes*/);
double sigmoid(double a);
double sigmoidprime(double b);
//

int main(void)
{
	Matrix M;
	M = init_matrix(3,3);
	printf("%d\n", *(M.pt + 1));
	return 0;
}


/*----------------------------*/


//Network init_all(Matrix M)
//{
	//init weights/biases/sizes
	//return Network object
//}


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

