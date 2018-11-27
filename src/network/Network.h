#include "Matrix.h"

#ifndef NETWORK_H
#define NETWORK_H

//type list Matrix
typedef struct StoreMatrix
{
	struct Matrix* matrices;
	int nb;
}StoreMatrix;

StoreMatrix init_StoreMatrix(int nb_matrix);

//type liste liste matrix
typedef struct Network
{
	struct StoreMatrix* pt_wbo; 
	int length;
}Network;

Network init_network(int length);

Network init_all(Matrix sizes, int length);
void feedforward(Network net, int length);
void print_network(Network net, int length);
Matrix backprop_on_last(Network net, Matrix Target, int length);
void backprop_on_hidden(Network net, Matrix ErrorLast, int length);
void free_network(Network net);

//void print_result(Network net, int length);

#endif
