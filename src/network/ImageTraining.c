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
	//printf("%s\n", img_name);
	for (int i = 0; i < M.rows; i++)
	{
		for (int j = 0; j < M.columns; j++)
		{	
			*(M.pt + i*M.columns + j) /= 255;
		}
	}
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
		//printf("%c\n", label);
		

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
		//int r = rand() % 10;
		//int r = 0;
		char pathimage[100] = "../../img_train/";
		char pathlabel[100] = "../../label_train/";

		int r = rand() % 10000;
		//printf("\n R -> %d\n", r);

		Matrix image = GetImage(pathimage, r);
		image.rows *= image.columns;
		image.columns = 1;

		//Matrix image = test(r);
		
        *(Outputs.matrices) = image;
		
		int label = GetLabel(pathlabel, r);
		//printf("\n%d\n", label);

		Matrix Target = init_matrix_zero(10, 1);
		*(Target.pt + label/*r*/) = 1;
		//print_matrix(Target);
		//printf("\n");

		feedforward(net, length);
		Matrix Error = backprop_on_last(net, Target, length);
		//print_matrix(Error);
		backprop_on_hidden(net, Error, length); 
		//printf("\n");
		//print_matrix(Error);
		if (i == 0 || i == nb_it-1 || i == nb_it-2)
		{
			printf("\n----NETWORK----%d\n", i);
			printf("\n---%d---\n", label);
			print_network(net, net.length);
		}
		free(image.pt);
        free(Error.pt);
		free(Target.pt);
		//printf("%d\n", i);
	}
	*(Outputs.matrices) = init_matrix_zero(625 , 1);
}

void TestNetwork(Network net)
{
	int length = net.length;
	StoreMatrix Outputs = *(net.pt_wbo + 2);
    int c = 0; 
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
		
		if (c_out == c_lab)
			c++;

		printf("RESULT -> %c\n", c_out);
		printf("LABEL  -> %c\n", c_lab);

        //free(image.pt);
	}
	printf("%d", c);
}

//good
Network CreateNetwork()
{
	Matrix sizes = init_matrix_zero(1, 3);
	*(sizes.pt) = 625/*17*/;
	*(sizes.pt + 1) = 30;
	*(sizes.pt + 2) = /*76*/10;

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

/*char* ApplyOCR(Matrix images, int length)
{
    size_t i = 0;
    size_t j = 0;
    Network net = LoadNetwork();
    char str[length / 350];
    size_t cpt_matrix = 0;
    Matrix M = init_matrix_zero(625, 1);

    while (i < length)
    {
        if (*(images.pt + i) == -2)
        {
            str[j] = " ";
            j++;
        }
        else if (*(images.pt + i) == -3)
        {
            str[j] = "\n"; 
            j++;
        }
        else if (*(images.pt + i) <= 1 && *(images.pt + i) >= 0)
        {
            if (cpt_matrix == 625)
            {
                //lancer OCR
                feedforward(net, net.length);
                StoreMatrix Outputs = *(net.pt_wbo+2);
                Matrix O = *(Outputs.matrices + 2);
                double b = max_M(O);

                char fl[8];
                sprintf(fl, "%lf", b);
                strcat(str, fl);
                j += 8;

                //add le char retourne dans la string
                cpt_matrix = 0;
            }
            else
            {
                *(M.pt + cpt_matrix) = *(images.pt + i);
                cpt_matrix++;
            }
        }
        i += 1;

    }
    return str;
}*/





