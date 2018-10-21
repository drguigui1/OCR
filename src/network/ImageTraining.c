#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "ImageTraining.h"
#include "Network.h"


StoreMatrix ImageParsing(ImageType type)
{
	FILE* images;
	FILE* labels;

	if (type == Train)
	{
		images = fopen("../../test_img/train-images-idx3-ubyte", "r");
		labels = fopen("../../test_img/train-labels-idx1-ubyte", "r");
	}
	else
	{
		images = fopen("../../test_img/t10k-images-idx3-ubyte", "r");
		labels = fopen("../../test_img/t10k-labels-idx1-ubyte", "r");
	}
	if (images != NULL && labels != NULL)
	{
		fseek(images, 2, SEEK_CUR);
		fseek(labels, 4, SEEK_CUR);
		char* s = malloc(sizeof(int));
		s = fgets(s, sizeof(int), images);
		int nb_images = atoi(s);
		printf("%d\n", nb_images);

		StoreMatrix a = init_StoreMatrix(1);
		return a;
	}
	else
		errx(1, "ERROR while opening file in ImageParsing");
}
