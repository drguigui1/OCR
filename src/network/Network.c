#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "MathForOcr.h"


/*------------------------*/

//type list Matrix
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


//type liste liste matrix
typedef struct Network
{
	struct StoreMatrix* pt_wbo; 
	//pt + 0 -> weights
	//pt + 1 -> bias
	//pt + 2 -> outputs
}Network;

//constructor
Network init_network()
{
	Network net = {malloc(sizeof(struct StoreMatrix) * 3)};
	return net;
}

/*-------------------------*/

//functions
/*-------------------------*/

Network init_all(Matrix sizes, int length);
void feedforward(Network net, int length);
void print_network(Network net, int length);
Matrix backprop_on_last(Network net, Matrix Target, int length);
void backprop_on_hidden(Network net, Matrix ErrorLast, int length);

/*-------------------------*/

int main(void)
{
	
	//init sizes = [2,3,2]
	Matrix sizes = init_matrix(1, 3);
	*(sizes.pt) = 2;
	*(sizes.pt + 1) = 3;
        *(sizes.pt + 2) = 2;

	/////////////////////////
	
	int length = sizeof(sizes)/sizeof(int);

	Network net = init_all(sizes, length);

	StoreMatrix Outputs = *(net.pt_wbo + 2);	

	//declare Input
	Matrix I = init_matrix(2,1);
	*(I.pt) = 1;
	*(I.pt + 1) = 1;
	*(Outputs.matrices) = I;
	*(net.pt_wbo + 2) = Outputs;

	//target
	Matrix T = init_matrix(1,1);
	*(I.pt) = 1;
	*(I.pt + 1) = 0.5;

	feedforward(net, length);	

	print_network(net, length);

	Matrix Error = backprop_on_last(net, T, length);
	backprop_on_hidden(net, Error, length);
	
	print_network(net, length);	

	return 0;
}


/*----------------------------*/


/*----------functions for the network--------------*/

Network init_all(Matrix sizes, int length)
{
	Network net = init_network();

	StoreMatrix Weights = init_ListMatrix(length-1);	
	StoreMatrix Bias = init_ListMatrix(length-1);
	StoreMatrix Outputs = init_ListMatrix(length);

	
	//first for Weights
	for (int i = 0; i < (length-1); i++)
		*(Weights.matrices + i) = init_matrix(*(sizes.pt + i+1),*(sizes.pt + i));
	
	//second for Bias
	for (int j = 0; j < (length-1); j++)
		*(Bias.matrices + j) = init_matrix(*(sizes.pt + j+1),1);

	*(net.pt_wbo) = Weights;
	*(net.pt_wbo + 1) = Bias;
	*(net.pt_wbo + 2) = Outputs;
	return net;
}

/*----------------------------*/

void feedforward(Network net, int length)
{
	//first Matrix of Outputs : the input of the network
	StoreMatrix Weights = *(net.pt_wbo);
	StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);

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
	*(net.pt_wbo + 2) = Outputs;

}

/*------------------------------*/

//call this function with a copy of Output
Matrix error_last_layer(Matrix Target, Matrix Output)
{
	mult_by_doubl(Output, -1);
	return add_matrix(Target, Output);
}

//Error : error of the l+1 layer
Matrix error_hidden(Matrix Weight, Matrix Error)
{
	Matrix A = init_matrix(Weight.columns, Error.columns);
	A = transpose_matrix(Weight);
	return mult_matrix(A, Error);
}

/*------------------------------*/

//on one layer 
//lr : learning rate
//call this function with copy of Output
Matrix SGD(Matrix Output, Matrix Error, double lr)
{
	Matrix A = init_matrix(Output.rows, 1);
	apply_func(Output, sigmoidprime);
	mult_by_doubl(Error, lr);
	A = hadamar_product(Output, Error);
	return A;
} //apply it on bias

/*--------------------------------*/

//on one layer
//call this function with copy of Output_l_1
Matrix delta(Matrix Sgd, Matrix Output_l_1)
{
	Matrix B = init_matrix(Sgd.rows, Output_l_1.rows);
	Output_l_1 = transpose_matrix(Output_l_1);
	B = mult_matrix(Sgd, Output_l_1);
	return B;
} //apply it on weights*/

/*--------------------------------*/
//backprop on the last layer
Matrix backprop_on_last(Network net, Matrix Target, int length)
{

	//store list of matrix
	StoreMatrix Weights = *(net.pt_wbo);
	StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);

	//store useful matrix
	Matrix O = *(Outputs.matrices + length-1);
	Matrix O_l_1 = *(Outputs.matrices + length-2);
	Matrix W = *(Weights.matrices + length-2);
	Matrix B = *(Bias.matrices + length-2);

	Matrix Error = error_last_layer(Target, O); //error
	printf("\n");
	Matrix Sgd = SGD(O, Error, 0.2);//learning rate 
	Matrix Delt = delta(Sgd, O_l_1);
	//weights update
	W = add_matrix(W, Delt);
	*(Weights.matrices + length-2) = W;
	//bias update
	B = add_matrix(B, Sgd);
	*(Bias.matrices + length-2) = B;

	*(net.pt_wbo) = Weights;
	*(net.pt_wbo +1) = Bias;
	
	return Error;
}

//backprop on the network on all hidden 
void backprop_on_hidden(Network net, Matrix Errorlast, int length)
{
	//store list of matrix
	StoreMatrix Weights = *(net.pt_wbo);
	StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);

	Matrix Error = Errorlast;

	for (int i = length - 2; i > 0; i--)
	{
		//store matrix
		Matrix O = *(Outputs.matrices + i);
	        Matrix O_l_1 = *(Outputs.matrices + i-1);
		Matrix Wl1 = *(Weights.matrices + i);
		Matrix W = *(Weights.matrices + i-1);
		Matrix B = *(Bias.matrices + i-1);

		Error = error_hidden(Wl1, Error);
		Matrix Sgd = SGD(O, Error, 0.2);
		Matrix Delt = delta(Sgd, O_l_1);
		//updare weights/bias
		W = add_matrix(W, Delt);
		B = add_matrix(B, Sgd);
		
		*(Weights.matrices + i-1) = W;
		*(Bias.matrices + i-1) = B;
	}
	*(net.pt_wbo) = Weights;
	*(net.pt_wbo + 1) = Bias;
}

/*-------------------------------------------*/
/*---------------HELPERS---------------------*/
void print_network(Network net, int length)
{
	
	StoreMatrix Weights = *(net.pt_wbo);
        StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);	

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
	

}