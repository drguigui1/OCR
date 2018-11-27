#include <stdio.h>
#include <stdlib.h>
#include <time.h>




#include "xor.h"
#include "Matrix.h"
#include "MathForOcr.h"
#include "Network.h"
#include "SaveAndLoad.h"
#include "ImageTraining.h"


void test()
{
	for (int i = 2300; i<2310; i++)
	{
		char path[100] = "../../img_train/";
		Matrix M = GetImage(path, i);
		//int tmp = M.columns;
		//M.columns = 1;
		//M.rows *= tmp;
		//print_matrix(M);
		//printf("\n%d %d\n", M.rows, M.columns);
		free(M.pt);
	}
}

int main()
{
	srand(time(NULL));
	//XOR
	//init sizes = [2,3,1]
	/*Matrix sizes = init_matrix(1, 3);
	*(sizes.pt) = 2;
	*(sizes.pt + 1) = 3;
    *(sizes.pt + 2) = 1;

	

	srand(time(NULL));
	xor(sizes);
	free(sizes.pt);*/
	
	// OCR

	/*Network net = CreateNetwork();
	TrainNetwork(net, 1);
	TestNetwork(net);

	free_network(net);
*/
	// TEST

	/*Network net = CreateNetwork();
	feedforward(net, net.length);
	print_network(net, net.length);
	free_network(net);
*/
	//test();
	return 0;

}




