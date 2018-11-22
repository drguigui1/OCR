#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "ImageTraining.h"
#include "Network.h"
#include "Matrix.h"
#include "convert.h"
#include "Image_Func.h"


Matrix GetImage(char path[], int img_number)
{
	char img_name[5];
	sprintf(img_number, "%d", img_name);
	strcat(img_name, ".png");
	strcat(path, img_name);
	Matrix M = img_to_matrix(load_image(path));
	return M;
}

int GetLabel(char path[], int label_number)
{
	FILE* file;

	char label_name[5];
	sprintf(label_number, "%d", &label_name);
	strcat(label_name, ".txt");
	strcat(path, label_name);
	file = fopen(path, "r");
	
	if (file != NULL)
	{
		int target;
		char label = fgetc(file);
		
		if (47 < label && label < 58)
			target = label - 48;
		else if (64 < label && label < 91)
			target = label - 55;
		else if (96 < label && label < 123)
			target = label - 61;
		else if (label == 33 || label == 34)
			target = label + 29;
		else if (label == 40 || label == 41)
			target = label + 24;
		else if (42 < label && label < 48)
			target = label + 24;
		else if (90 < label && label < 96)
			target = label - 20;

		fclose(file);
		return target; 
	}
	else 
		errx(1, "ERROR while opening file in SaveData\n");
}

void TrainNetwork(Network net, int nb_it)
{
	char pathimage[] = "../../img_train/";
	char pathlabel[] = "../../label_train/";

	int length = net.length;
	StoreMatrix Outputs = *(net.pt_wbo + 2);

	for (int i = 0; i < nb_it; i++)
	{
		int r = rand() % 10000;

		Matrix image = GetImage(pathimage, r);
		image.rows *= image.columns;
		image.columns = 1;

		*(Outputs.matrices) = image;
		
		int label = GetLabel(pathlabel, r);
		
		Matrix Target = init_matrix_zero(1, 76);
		*(Target.pt + label) = 1;

		feedforward(net, length);
		Matrix Error = backprop_on_last(net, Target, length);
		backprop_on_hidden(net, Error, length);
	}
}

void TestNetwork(Network net)
{
	char pathimage[] = "../../img_test/";
	char pathlabel[] = "../../label_test/";

	int length = net.length;
	StoreMatrix Outputs = *(net.pt_wbo + 2);

	for (int i = 0; i < 1000; i++)
	{

		Matrix image = GetImage(pathimage, i);
		image.rows *= image.columns;
		image.columns = 1;

		*(Outputs.matrices) = image;
		
		feedforward(net, length);

		
	}
}

Network CreateNetwork()
{
	Matrix sizes = init_matrix_zero(1, 3);
	*(sizes.pt) = 625;
	*(sizes.pt + 1) = 125;
	*(sizes.pt + 2) = 76;

	Network net = init_all(sizes, 3);

	return net; 
}


int max_M(Matrix M)
{
    int tmp = 0;
    for (int i = 1; i < M.rows*M.columns; i++)
    {
        if (*(M.pt + tmp) < *(M.pt + i))
        {
			tmp = i;
        }

    }
    return tmp;
}




