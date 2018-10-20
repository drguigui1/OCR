#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "MathForOcr.h"
#include "Network.h"

/*------------------------*/


//constructeur
StoreMatrix init_StoreMatrix(int nb_matrix)
{
	StoreMatrix l_matrix = {malloc(sizeof(struct Matrix) * nb_matrix), nb_matrix};
	return l_matrix;
}


//constructor
Network init_network()
{
	Network net = {malloc(sizeof(struct StoreMatrix) * 4)};
	return net;
}

/*-------------------------*/

//functions
/*-------------------------*/


/*----------functions for the network--------------*/

Network init_all(Matrix sizes, int length)
{
	Network net = init_network();

	StoreMatrix Weights = init_StoreMatrix(length-1);	
	StoreMatrix Bias = init_StoreMatrix(length-1);
	StoreMatrix Outputs = init_StoreMatrix(length);
	StoreMatrix Zs = init_StoreMatrix(length-1);
	
	//first for Weights
	for (int i = 0; i < (length-1); i++)
		*(Weights.matrices + i) = init_matrix(*(sizes.pt + i+1),*(sizes.pt + i));
	
	//second for Bias
	for (int j = 0; j < (length-1); j++)
		*(Bias.matrices + j) = init_matrix(*(sizes.pt + j+1),1);

	//for (int k = 0; k < (length-1), k++)
		//*(Zs.matrices + k) = init_matrix(*());

	*(net.pt_wbo) = Weights;
	*(net.pt_wbo + 1) = Bias;
	*(net.pt_wbo + 2) = Outputs;
	*(net.pt_wbo + 3) = Zs;
	return net;
}

/*----------------------------*/

void feedforward(Network net, int length)
{
	//first Matrix of Outputs : the input of the network
	StoreMatrix Weights = *(net.pt_wbo);
	StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);
	//StoreMatrix Zs = *(net.pt_wbo + 3);

	for (int i = 0; i < length-1; i++) //parcours du reseau
	{
		Matrix W = *(Weights.matrices + i);
		Matrix O = *(Outputs.matrices + i);
		Matrix B = *(Bias.matrices + i);
		Matrix tab = init_matrix(W.rows, 1);

		tab = add_matrix(mult_matrix(W, O), B);
		//*(Zs.matrices + i) = copy_matrix(tab);
		apply_func(tab, sigmoid);
		*(Outputs.matrices + i + 1) = tab;
	}
	*(net.pt_wbo + 2) = Outputs;
	//*(net.pt_wbo + 3) = Zs; 

}

/*------------------------------*/

//call this function with a copy of Output
Matrix error_last_layer(Matrix Target, Matrix Output)
{
	return sub_matrix(Target, Output);
}

//Error : error of the l+1 layer
Matrix error_hidden(Matrix Weight, Matrix Error)
{
	Matrix A = init_matrix(Weight.columns, Weight.rows);
	A = transpose_matrix(Weight);
	return mult_matrix(A, Error);
}

/*------------------------------*/

//on one layer 
//lr : learning rate
//call this function with copy of Output
Matrix SGD(Matrix Output, Matrix Error, double lr)
{
	apply_func(Output, sigmoidprime);
	mult_by_doubl(Error, lr);
	return hadamar_product(Output, Error);
} //apply it on bias

/*--------------------------------*/

//on one layer
//call this function with copy of Output_l_1
Matrix delta(Matrix Sgd, Matrix Output_l_1)
{
	Matrix B = init_matrix(Output_l_1.columns, Output_l_1.rows);
	B = transpose_matrix(Output_l_1);
	return mult_matrix(Sgd, B);
} //apply it on weights*/

/*--------------------------------*/
//backprop on the last layer
Matrix backprop_on_last(Network net, Matrix Target, int length)
{

	//store list of matrix
	StoreMatrix Weights = *(net.pt_wbo);
	StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);
	//StoreMatrix Zs = *(net.pt_wbo + 3);

	//store useful matrix
	Matrix O = copy_matrix(*(Outputs.matrices + length-1));
	Matrix O_l_1 = copy_matrix(*(Outputs.matrices + length-2));
	Matrix W = *(Weights.matrices + length-2);
	Matrix B = *(Bias.matrices + length-2);
	//Matrix Z = copy_matrix(*(Zs.matrices + length-2));
	
	Matrix Error = error_last_layer(Target, O); //error
	printf("\n-----ERROR----\n");
	print_matrix(Error);
	printf("--------------\n");

	Matrix Sgd = SGD(O, Error, 0.2);//learning rate error
	Matrix Delt = delta(Sgd, O_l_1);
	//weights update
	W = add_matrix(W, Delt);
	*(Weights.matrices + length-2) = W;
	//bias update
	B = add_matrix(B, Sgd);

	*(Bias.matrices + length-2) = B;

	*(net.pt_wbo) = Weights;
	*(net.pt_wbo +1) = Bias;
	*(net.pt_wbo +2) = Outputs;
	//*(net.pt_wbo +3) = Zs;

	return Error;
}

//backprop on the network on all hidden 
void backprop_on_hidden(Network net, Matrix Errorlast, int length)
{
	//store list of matrix
	StoreMatrix Weights = *(net.pt_wbo);
	StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);
	//StoreMatrix Zs = *(net.pt_wbo + 3);

	Matrix Error = copy_matrix(Errorlast);

	for (int i = length - 2; i > 0; i--)
	{
		//store matrix
		Matrix O = copy_matrix(*(Outputs.matrices + i));
	    	Matrix O_l_1 = copy_matrix(*(Outputs.matrices + i-1));
		Matrix Wl1 = copy_matrix(*(Weights.matrices + i));
		Matrix W = *(Weights.matrices + i-1);
		Matrix B = *(Bias.matrices + i-1);
		//Matrix Z = copy_matrix(*(Zs.matrices + i-1));

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
	*(net.pt_wbo + 2) = Outputs;
	//*(net.pt_wbo + 3) = Zs;
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

