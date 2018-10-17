#include <stdio.h>
#include <stdlib.h>

#include "save_and_load.h"
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
		fputc((char) data.nb, file);
	}
	else 
		printf("ERROR while opening file in SaveData\n");
}


