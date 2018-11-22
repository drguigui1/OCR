#include "Network.h"

#ifndef IMAGETRAINING_H
#define IMAGETRAINING_H

Matrix GetImage(char path[], int img_number);
int GetLabel(char path[], int label_number);
void TrainNetwork(Network net, int nb_it);
void TestNetwork(Network net);
Network CreateNetwork ();
int max_M(Matrix M);

#endif
