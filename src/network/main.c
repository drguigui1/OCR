#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "xor.h"
#include "Matrix.h"
#include "MathForOcr.h"
#include "Network.h"
#include "SaveAndLoad.h"
#include "ImageTraining.h"



int main()
{
	srand(time(NULL));
	//XOR
	//init sizes = [2,3,1]
	/*Matrix sizes = init_matrix(1, 3);
	*(sizes.pt) = 2;
	*(sizes.pt + 1) = 10;
    *(sizes.pt + 2) = 1;

	//Network net = LoadNetwork(sizes);
    //free_network(net);

	xor(sizes);
	free(sizes.pt);
	*/
	// OCR

	//Network net = CreateNetwork();
	//TrainNetwork(net, 50000);
	//TestNetwork(net);
	//SaveNetwork(net);
	
	//Network net = LoadNetwork();
	//print_network(net, 3);
	//TestNetwork(net);

	//free_network(net);
    
	// TEST

	/*Network net = CreateNetwork();
	feedforward(net, net.length);
	print_network(net, net.length);
	printf("|--------------------|\n");
	Matrix Target = init_matrix_zero(7, 1);
	Matrix Error = backprop_on_last(net, Target, net.length);
	print_matrix(Error);
	printf("|-------------------|\n");
	backprop_on_hidden(net, Error, net.length);

	free(Error.pt);
	free(Target.pt);
	free_network(net);
*/

	char* st = xor_f(1, 0);
	printf("X1:1, X2:1\n");
	st = st;

	return 0;

}




