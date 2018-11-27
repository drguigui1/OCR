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
	char img_name[6];
	sprintf(img_name, "%d", img_number);
	strcat(img_name, ".png");
	strcat(path, img_name);
	SDL_Surface* img = load_image(path);
	Matrix M = img_to_matrix(img);
	free(img);
	return M;
}

//good
int GetLabel(char path[], int label_number)
{
	FILE* file;

	char label_name[10];
	sprintf(label_name, "%d", label_number);
	strcat(label_name, ".txt");
	strcat(path, label_name);
	file = fopen(path, "r");
	
	if (file != NULL)
	{
		int target;
		char label = fgetc(file);
		printf("%c\n", label);
		
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
	char pathimage[30] = "../../img_train/";
	char pathlabel[30] = "../../label_train/";

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
		int out = max_M(*(Outputs.matrices + 2));
		unsigned char c_out = convert_to_ascii(out);

		int label = GetLabel(pathlabel, i);
		unsigned char c_lab = convert_to_ascii(label);
		
		printf("RESULT -> %c\n", c_out);
		printf("LABEL  -> %c\n", c_lab);
	}
}

Network CreateNetwork()
{
	Matrix sizes = init_matrix_zero(1, 3);
	*(sizes.pt) = 625;
	*(sizes.pt + 1) = 125;
	*(sizes.pt + 2) = 76;

	Network net = init_all(sizes, 3);

	free(sizes.pt);

	return net; 
}


//good
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

//good
unsigned char convert_to_ascii(int pos)
{
	unsigned char a;

	if (0 <= pos && pos <= 9)                                           
    	a = pos + 48;                                                
    else if (10 <= pos && pos <= 35)                                      
    	a = pos + 55;                                                
    else if (36 <= pos && pos <= 61)                                     
        a = pos + 61;                                                
    else if (pos == 62 || pos == 63)                                    
        a = pos - 29;                                                
    else if (pos == 64 || pos == 65)                                    
        a = pos - 24;                                                
    else if (66 <= pos && pos <= 70)                                      
    	a = pos - 24;                                                
    else if (71 <= pos && pos <= 75)                                      
    	a = pos + 20;
    else
    {
    	errx(1, "ERROR CONVERT TO ASCII");
    }
	return a;
}




