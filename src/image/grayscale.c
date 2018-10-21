#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "Image_Func.h"
#include "Pixel_Func.h"


SDL_Surface* grayscale (char *path)
{
	init_sdl();

	SDL_Surface* image_surface = load_image(path);
	
	int width = image_surface->w;
	int height = image_surface->h;
        Uint8 r, g, b;
	Uint8 average;
	for (int i = 0; i < height; i++)
	{    
		for (int j = 0; j < width; j++)
		{
			Uint32 pixel = get_pixel(image_surface, j, i);
                    	SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
                    	average = 0.3*r + 0.59*g + 0.11*b;
                    	r = average;
                	g = average;
                    	b = average;
                   	pixel = SDL_MapRGB(image_surface->format, r, g, b);
                    	put_pixel(image_surface, j, i, pixel);
            	}
    	}

	return image_surface;

}
