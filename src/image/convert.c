#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utils/Matrix.h"
#include "../utils/MathForOcr.h"
#include "grayscale.h"
#include "Pixel_Func.h"
#include "Image_Func.h"

// Convert an image into a Matrix
Matrix img_to_matrix(SDL_Surface* img)
{
	int width = img->w;
	int height = img->h;
	Matrix M = {width,height, malloc(width * height * sizeof(double))};
        srand (time (NULL));
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

// Convert a matrix with 0 and 1 values to a binarized img
// Then display the image
void matrix_to_img (Matrix M)
{
	int x = M.rows;
	int y = M.columns;
	double val;
	Uint32 pixel;
	SDL_Surface* img = SDL_CreateRGBSurface(0, x, y, 32, 0, 0, 0, 0);
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			val = (uint8_t) *(M.pt + i*y +j) * 255;
			pixel = SDL_MapRGB(img->format, val, val, val);
			put_pixel (img, i, j, pixel);
		}
	}
	display_image(img);
	wait_for_keypressed();
}
