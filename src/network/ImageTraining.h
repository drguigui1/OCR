#include "Network.h"

#ifndef IMAGETRAINING_H
#define IMAGETRAINING_H

Matrix GetImage(char path[], int img_number);
int GetLabel(char path[], int label_number);
void TrainNetwork(Network net, int nb_it);
void TestNetwork(Network net);
Network CreateNetwork ();
int max_M(Matrix M);
unsigned char convert_to_ascii(int pos);
void ApplyOCR(Matrix images, int length, char str[]);
Matrix SimulateSeg();

#endif
