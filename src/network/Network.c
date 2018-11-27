#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "MathForOcr.h"
#include "Network.h"

/*------------------------*/


//constructeur
StoreMatrix init_StoreMatrix(int nb_matrix)
{
	StoreMatrix l_matrix = {malloc(sizeof(struct Matrix)* nb_matrix),nb_matrix};
	return l_matrix;
}


//constructor
Network init_network(int length)
{
	Network net = {malloc(sizeof(struct StoreMatrix) * 4), length};
	return net;
}

/*-------------------------*/

//functions
/*-------------------------*/


/*----------functions for the network--------------*/

Network init_all(Matrix sizes, int length)
{
	Network net = init_network(length);

	StoreMatrix Weights = init_StoreMatrix(length-1);	
	StoreMatrix Bias = init_StoreMatrix(length-1);
	StoreMatrix Outputs = init_StoreMatrix(length);
	
	//first for Weights
	for (int i = 0; i < (length-1); i++)
		*(Weights.matrices+ i) = init_matrix(*(sizes.pt + i+1),*(sizes.pt + i));
	
	//second for Bias
	for (int j = 0; j < (length-1); j++)
		*(Bias.matrices + j) = init_matrix(*(sizes.pt + j+1),1);

	for (int k = 0; k < length; k++)
        *(Outputs.matrices + k) = init_matrix_zero(*(sizes.pt + k),1);

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

		Matrix T = mult_matrix(W, O);
		Matrix tab = add_matrix(T, B);
		apply_func(tab, sigmoid);

		/* FREE */
		free((Outputs.matrices + i + 1)->pt);

		*(Outputs.matrices + i + 1) = tab;

		/* FREE */
		free(T.pt);
	}
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
	Matrix A = transpose_matrix(Weight);
	A = mult_matrix(A, Error);
	return A;
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
	Matrix B = transpose_matrix(Output_l_1);
	Matrix B2 = mult_matrix(Sgd, B);
	free(B.pt);
	return B2;
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
	Matrix O = copy_matrix(*(Outputs.matrices + length-1));
	Matrix O_l_1 = copy_matrix(*(Outputs.matrices + length-2));
	Matrix W = *(Weights.matrices + length-2);
	Matrix B = *(Bias.matrices + length-2);
	
	Matrix Error = error_last_layer(Target, O); //error

	Matrix Sgd = SGD(O, Error, 0.4);//learning rate error
	Matrix Delt = delta(Sgd, O_l_1);
	//weights update
	W = add_matrix(W, Delt);
	free((Weights.matrices + length-2)->pt);
	*(Weights.matrices + length-2) = W;
	//bias update
	B = add_matrix(B, Sgd);

	free((Bias.matrices + length-2)->pt);
	*(Bias.matrices + length-2) = B;
	free(Sgd.pt);
	free(Delt.pt);

	free(O.pt);
	free(O_l_1.pt);

	return Error;
}

//backprop on the network on all hidden 
void backprop_on_hidden(Network net, Matrix Errorlast, int length)
{
	//store list of matrix
	StoreMatrix Weights = *(net.pt_wbo);
	StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);

	Matrix Error = copy_matrix(Errorlast);
	free(Errorlast.pt);

	for (int i = length - 2; i > 0; i--)
	{
		//store matrix
		Matrix O = copy_matrix(*(Outputs.matrices + i));
    	Matrix O_l_1 = copy_matrix(*(Outputs.matrices + i-1));
		Matrix Wl1 = copy_matrix(*(Weights.matrices + i));
		Matrix W = *(Weights.matrices + i-1);
		Matrix B = *(Bias.matrices + i-1);

		Error = error_hidden(Wl1, Error);
		Matrix Sgd = SGD(O, Error, 0.4);

		Matrix Delt = delta(Sgd, O_l_1);
		//updare weights/bias
		W = add_matrix(W, Delt);
		B = add_matrix(B, Sgd);
		

		/* FREE */
		free((Weights.matrices + i-1)->pt);
		free((Bias.matrices + i-1)->pt);
		
		*(Weights.matrices + i-1) = W;
		*(Bias.matrices + i-1) = B;

		free(Delt.pt);
		free(Sgd.pt);
		free(O.pt);
		free(O_l_1.pt);
		free(Wl1.pt);
	}

	free(Error.pt);
}

void free_storeM(StoreMatrix S, int len)
{
	for (int i = 0; i < len; i++)
	{
		free((S.matrices + i)->pt);
	}
}

void free_network(Network net)
{
	
	StoreMatrix Weights = *(net.pt_wbo);
    StoreMatrix Bias = *(net.pt_wbo + 1);
	StoreMatrix Outputs = *(net.pt_wbo + 2);	

	//Weights
	for (int i = 0; i < (net.length-1); i++)
		free((Weights.matrices + i)->pt);
	
	//biases
	for (int j = 0; j < (net.length-1); j++)
		free((Bias.matrices + j)->pt);

	//Outputs
	for (int k = 0; k < net.length; k++)
		free((Outputs.matrices + k)->pt);
    
    free(Weights.matrices);
    free(Bias.matrices);
    free(Outputs.matrices);
    free(net.pt_wbo);
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
		//int r = (*(Weights.matrices+i)).rows;
        //int c = (*(Weights.matrices+i)).columns;
        //printf("ROWS ->%d, COLS->%d\n", r, c);
		printf("\n");	
	}
	
	//biases
	printf("Biases\n");
	for (int j = 0; j < (length-1); j++)
	{
		print_matrix(*(Bias.matrices + j));
		//int r = (*(Bias.matrices+j)).rows;
        //int c = (*(Bias.matrices+j)).columns;
        //printf("ROWS ->%d, COLS->%d\n", r, c);
		printf("\n");
	}

	//Outputs
	printf("Outputs\n");
	for (int k = 0; k < length; k++)
	{
		print_matrix(*(Outputs.matrices + k));
		//int r = (*(Outputs.matrices+k)).rows;                                   
        //int c = (*(Outputs.matrices+k)).columns;                                
        //printf("ROWS ->%d, COLS->%d\n", r, c);
		printf("\n");
	}
	printf("|----------------------|\n");
}

