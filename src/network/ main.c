#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"
#include "MathForOcr.h"
#include "Network.h"
#include "save_and_load.h"

int main()
{
	Matrix xor1 = init_matrix(2,1); 
	Matrix xor2 = init_matrix(2,1); 
	Matrix xor3 = init_matrix(2,1); 
	Matrix xor4 = init_matrix(2,1); 

	*(xor1.pt) = 0;
	*(xor1.pt+1) = 0;
	*(xor2.pt) = 0;
	*(xor2.pt+1) = 1;
	*(xor3.pt) = 1;
	*(xor3.pt+1) = 0;
	*(xor4.pt) = 1;
	*(xor4.pt+1) = 1;

	StoreMatrix XOR = init_StoreMatrix(4);
	*(XOR.matrices) = xor1;
	*(XOR.matrices+1) = xor2;
	*(XOR.matrices+2) = xor3;
	*(XOR.matrices+3) = xor4;

	Matrix label1 = init_matrix(1,1); 
	Matrix label2 = init_matrix(1,1); 
	Matrix label3 = init_matrix(1,1); 
	Matrix label4 = init_matrix(1,1);

	*(label1.pt) = 0;
	*(label2.pt) = 1;
	*(label3.pt) = 1;
	*(label4.pt) = 0;

	StoreMatrix LABEL = init_StoreMatrix(4); 
	*(LABEL.matrices) = label1;
	*(LABEL.matrices+1) = label2;
	*(LABEL.matrices+2) = label3;
	*(LABEL.matrices+3) = label4;

	
	//init sizes = [2,3,2]
	Matrix sizes = init_matrix(1, 3);
	*(sizes.pt) = 2;
	*(sizes.pt + 1) = 3;
    *(sizes.pt + 3) = 1;


	/////////////////////////

	int length = sizes.columns + 1;

	Network net = init_all(sizes, length);

	StoreMatrix Outputs = *(net.pt_wbo + 2);	
	Matrix Input = init_matrix(2,1);

	srand(time(NULL));
	for (int i = 0; i < 5000; ++i)
	{
		printf("%d\n", i);
		int n = rand() % 4;
		Matrix xor = init_matrix(2,1); 
		xor = *(XOR.matrices+n);
		*(Input.pt) = *(xor.pt);
		*(Input.pt+1) = *(xor.pt+1);		
		*(Outputs.matrices) = Input;
		//feedforward
		feedforward(net, length);	
		//print
		//print_network(net, length);

		//backpropagation
		Matrix Error = backprop_on_last(net, *(LABEL.matrices + n), length);
		backprop_on_hidden(net, Error, length);
		//print
		//print_network(net, length);	
	}
	
	//SaveData(Weights, Outputs);
	
	return 0;
}
