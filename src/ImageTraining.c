#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <fcntl.h>

#include "ImageTraining.h"
#include "Network.h"
#include "mnist.h"


StoreMatrix ImageParsing(ImageType type)
{
	int images;
	FILE* labels;

	if (type == Train)
	{
		images = open("../../test_img/train-images-idx3-ubyte", O_RDONLY);
		labels = fopen("../../test_img/train-labels-idx1-ubyte", "r");
	}
	else
	{
		images = open("../../test_img/t10k-images-idx3-ubyte", O_RDONLY);
		labels = fopen("../../test_img/t10k-labels-idx1-ubyte", "r");
	}
	if (labels != NULL)
	{

		int info_image[1];
		size_t b = read(images, info_image, 1 * sizeof(int));
		printf("%ld\n", b);
		for (int i = 0; i < 1; i++)
		{
			printf("%d\n", info_image[i]);
		}

		/*fseek(images, 0, SEEK_CUR);
		fseek(labels, 4, SEEK_CUR);
		char* s = malloc(8);
		s = fgets(s, 8, images);
		printf("%s\n", s);
		int nb_images = strtol(s, NULL, 16);
		printf("%d\n", nb_images);*/
		
		StoreMatrix a = init_StoreMatrix(1);
		return a;
	}
	else
		errx(1, "ERROR while opening file in ImageParsing");
}
