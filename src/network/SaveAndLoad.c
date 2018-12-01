#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>

#include "SaveAndLoad.h"
#include "MathForOcr.h"
#include "Matrix.h"
#include "Network.h"

void SaveData(DataType type, StoreMatrix data)
{
	FILE *file;
	if (type == Weights)
	{
		file = fopen("weights.save", "w+");
	}
	else
	{
		file = fopen("bias.save", "w+");
	}
	if (file != NULL)
	{

		for (int i = 0; i < data.nb; i++)
		{
			Matrix matrix_to_save = *(data.matrices + i);
			int rows = matrix_to_save.rows;	
			int columns = matrix_to_save.columns;

			for (int j = 0; j < rows; j++)
			{
				for (int k = 0; k < columns; k++)
				{
					fprintf(file, "%f\n", *(matrix_to_save.pt + j*columns + k));
				}
			}
		}
		fclose(file);
	}
	else 
		errx(1, "ERROR while opening file in SaveData\n");
}

void SaveNetwork(Network net)
{
	StoreMatrix weights = *(net.pt_wbo);
	StoreMatrix bias = *(net.pt_wbo + 1);
	SaveData(Weights, weights);
	SaveData(Bias, bias);
}

StoreMatrix LoadData(DataType type)
{
	FILE *file;

	if (type == Weights)
	{
		file = fopen("weights.save", "r");
		int nb_matrix = 2;
		StoreMatrix M = init_StoreMatrix(nb_matrix);

		for (int i = 0; i < nb_matrix; ++i)
		{
			int rows;
			int columns;
			if (i == 0)
			{
				rows = 30;
				columns = 625; 
			}
			else
			{
				rows = 10;
				columns = 30;
			}

			Matrix m = init_matrix(rows, columns);

			for (int j = 0; j < rows; ++j)
			{
				for (int k = 0; k < columns; ++k)
				{
					char* s = malloc(15 * sizeof(char));
					s = fgets(s, 15, file);
					strtok(s, "\n");
					*(m.pt + j*columns + k) = atof(s);
					free(s);
				}
			}
			*(M.matrices + i) = m;
            
		}
		fclose(file);
		return M;

	}
	else
	{
		file = fopen("bias.save", "r");
		int nb_matrix = 2;
		StoreMatrix M = init_StoreMatrix(nb_matrix);

		for (int i = 0; i < nb_matrix; ++i)
		{
			int rows;
			if (i == 0)
				rows = 30;
			else
				rows = 10;
			int columns = 1;

			Matrix m = init_matrix(rows, columns);

			for (int j = 0; j < rows; ++j)
			{
				for (int k = 0; k < columns; ++k)
				{
					char* s = malloc(15 * sizeof(char));
					s = fgets(s, 15, file);
					strtok(s, "\n");
					*(m.pt + j*columns + k) = atof(s);
					free(s);
				}
			}
			*(M.matrices + i) = m;			
        }
		fclose(file);
		return M;
	}
}

Network LoadNetwork(Matrix sizes)
{
    StoreMatrix weights = LoadData(Weights);
    StoreMatrix bias = LoadData(Bias);
	Network net = init_all(sizes, 3);
    StoreMatrix Weights = *(net.pt_wbo);
    StoreMatrix Bias = *(net.pt_wbo+1);
    free_storeM(Weights, Weights.nb);
    free_storeM(Bias, Bias.nb);
    *(net.pt_wbo) = weights;
	*(net.pt_wbo+1) = bias; 
	return net;
}
