#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Matrix.h"
#include "Image_Func.h"
#include "convert.h"

static inline
Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}


// -> Get the value of a pixel with his coordinates x and y
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}


// Convert an image into a Matrix
Matrix img_to_matrix(SDL_Surface* img)
{
		int width = img->w;
		int height = img->h;
		Matrix M = {width,height, malloc(width * height * sizeof(double))};
        //init
        for (int i = 0; i < width; i++)
        {
         	for(int j = 0; j < height; j++)
            {
				Uint8 r, g, b;
				SDL_GetRGB(get_pixel(img, i, j), img->format, &r, &g, &b);
           		double val = (double) (r+g+b)/3;
                *(M.pt + i*height + j) = val;
            }
         }
        return M;
}


