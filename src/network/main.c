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
	char path[22] = "../../img_test/";
	Matrix M = GetImage(path, 2);
	//int tmp = M.columns;
	//M.columns = 1;
	//M.rows *= tmp;
	print_matrix(M);
	printf("\n%d %d\n", M.rows, M.columns);
	free(M.pt);
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
	free(size.pt);
	*/

	/*Network net = CreateNetwork();
	TrainNetwork();
	TestNetwork(net);*/

	Network net = CreateNetwork();
	print_network(net, net.length);
	free(net.pt_wbo);


	retur 0;

}




