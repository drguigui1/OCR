#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"
#include "Image_Func.h"

// Convert an image into a Matrix
Matrix img_to_matrix(SDL_Surface* img)
{
	int width = img->w;
	int height = img->h;
	Matrix M = {width,height, malloc(width * height * sizeof(double))};
        //init
        for (int i = 0; i < width; i++)
                for(int j = 0; j < height; j++)
                {
			Uint8 r, g, b;
			SDL_GetRGB(get_pixel(img, i, j), img->format, &r, &g, &b);
                        double val = (double) (r+g+b)/3;
                        *(M.pt + i*height + j) = val;
                }
        return M;
}


