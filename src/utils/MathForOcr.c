#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "MathForOcr.h"

//sigmoid
double sigmoid(double a)
{
	return 1/(1+exp(-a));
}

//sigmoid prime
double sigmoidprime(double a)
{
	return a*(1-a);
}

//random value
double generate_random(double min, double max)
{
	//srand (time (NULL));
	return min + (rand() / ((RAND_MAX)/(max - min)));
}
