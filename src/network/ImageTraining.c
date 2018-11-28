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


//good
Matrix GetImage(char path[], int img_number)
{
	char img_name[100] = "";
	sprintf(img_name, "%d", img_number);
	strcat(img_name, ".png");
	strcat(path, img_name);
	SDL_Surface* img = load_image(path);
	Matrix M = img_to_matrix(img);
	SDL_FreeSurface(img);
	printf("%s\n", img_name);
	return M;
}

//good
int GetLabel(char path[], int label_number)
{
	FILE* file;

	char label_name[100] = "";
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
	
	int length = net.length;
	StoreMatrix Outputs = *(net.pt_wbo + 2);
    free((Outputs.matrices)->pt);

	for (int i = 0; i < nb_it; i++)
	{
		char pathimage[100] = "../../img_train/";
		char pathlabel[100] = "../../label_train/";

		int r = rand() % 1000;

		Matrix image = GetImage(pathimage, r);
		image.rows *= image.columns;
		image.columns = 1;
        
        *(Outputs.matrices) = image;
		
		int label = GetLabel(pathlabel, r);
		
		Matrix Target = init_matrix_zero(76, 1);
		*(Target.pt + label) = 1;

		feedforward(net, length);
		printf("ROWS->%d and COLS->%d\n", Target.rows, Target.columns);
		Matrix Error = backprop_on_last(net, Target, length); //ERROR SIZE (SUB AND HADAMAR)
		printf("ROWS->%d and COLS->%d\n", Error.rows, Error.columns);
		backprop_on_hidden(net, Error, length); //ERROR SIZE (mult)
		free(image.pt);
        free(Error.pt);
		free(Target.pt);
	}
}

void TestNetwork(Network net)
{
	int length = net.length;
	StoreMatrix Outputs = *(net.pt_wbo + 2);
    *(Outputs.matrices) = init_matrix_zero(12 , 1);

	for (int i = 0; i < 500; i++)
	{
	    char pathimage[100] = "../../img_test/";
	    char pathlabel[100] = "../../label_test/";

		Matrix image = GetImage(pathimage, i);
		image.rows *= image.columns;
		image.columns = 1;
        free((Outputs.matrices)->pt);
		*(Outputs.matrices) = image;
		
		feedforward(net, length);
		int out = max_M(*(Outputs.matrices + 2));
		unsigned char c_out = convert_to_ascii(out);

		int label = GetLabel(pathlabel, i);
		unsigned char c_lab = convert_to_ascii(label);
		
		printf("RESULT -> %c\n", c_out);
		printf("LABEL  -> %c\n", c_lab);

        //free(image.pt);
	}
}

//good
Network CreateNetwork()
{
	Matrix sizes = init_matrix_zero(1, 3);
	*(sizes.pt) = /*625*/12;
	*(sizes.pt + 1) = /*125*/5;
	*(sizes.pt + 2) = /*76*/7;

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




