#include <stdio.h>
#include <stdlib.h>

typedef struct Network
{
	int nb_layers;
	//sizes : list of int representing the nb of neuron per layer
	//biases : matrix of biases
	//weights : list of Matrix containing all weights of the network
}Network;

Network init_all(/*sizes*/);

int main(void)
{
	return 0;
}


Network init_all(/*sizes*/)
{
	//init weights/biases/sizes
	//return Network object
}
