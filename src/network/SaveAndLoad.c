#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "SaveAndLoad.h"
#include "MathForOcr.h"
#include "Matrix.h"
#include "Network.h"

void SaveData(DataType type, StoreMatrix data)
{
	FILE *file;

	if (type == Weights)
		file = fopen("weights.save", "w+");
	else
		file = fopen("bias.save", "w+");

	if (file != NULL)
	{
		fputc(data.nb, file);

		for (int i = 0; i < data.nb; i++)
		{
			Matrix matrix_to_save = *(data.matrices + i);
			int rows = matrix_to_save.rows;	
			int columns = matrix_to_save.columns;

			fputc(rows, file);
			fputc(columns, file);

			for (int j = 0; j < rows; j++)
			{
				for (int k = 0; k < columns; k++)
				{
					fprintf(file, "%lf", *(matrix_to_save.pt + j*columns + k));
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
		file = fopen("weights.save", "r");
	else
		file = fopen("bias.save", "r");

	if (file != NULL)
	{
		int nb_matrix = fgetc(file);
		StoreMatrix M = init_StoreMatrix(nb_matrix);

		for (int i = 0; i < nb_matrix; ++i)
		{
			int rows = fgetc(file);
			int columns = fgetc(file);
			
			Matrix m = init_matrix(rows, columns);

			for (int j = 0; j < rows; ++j)
			{
				for (int k = 0; k < columns; ++k)
				{
					char* s = malloc(9);
					s = fgets(s, 9, file);
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
		errx(1, "ERROR while opening file in LoadData\n");
}

Network LoadNetwork()
{
	StoreMatrix weights = LoadData(Weights);
	StoreMatrix bias = LoadData(Bias);
	Network net = init_network();
	*(net.pt_wbo) = weights;
	*(net.pt_wbo) = bias;
	return net;
}
