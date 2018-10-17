#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "MathForOcr.h"
#include "Network.h"
#include "save_and_load.h"

int main()
{
	
	//init sizes = [2,3,2]
	Matrix sizes = init_matrix(1, 4);
	*(sizes.pt) = 2;
	*(sizes.pt + 1) = 3;
    *(sizes.pt + 2) = 3;
    *(sizes.pt + 3) = 2;


	/////////////////////////

	int length = sizes.columns + 1;

	Network net = init_all(sizes, length);

	StoreMatrix Outputs = *(net.pt_wbo + 2);	

	//declare Input
	Matrix I = init_matrix(2,1);
	*(I.pt) = 1;
	*(I.pt + 1) = 1;
	*(Outputs.matrices) = I;
	*(net.pt_wbo + 2) = Outputs;

	//target
	Matrix T = init_matrix(2,1);
	*(T.pt) = 1;
	*(T.pt + 1) = 0.5;

	//feedforward
	feedforward(net, length);	
	//print
	print_network(net, length);
	//backpropagation
	Matrix Error = backprop_on_last(net, T, length);
	backprop_on_hidden(net, Error, length);
	//print
	print_network(net, length);	
	
	SaveData(Weights, Outputs);

	return 0;
}
