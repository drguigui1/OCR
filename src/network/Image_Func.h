#ifndef IMAGE_FUNC_H
#define IMAGE_FUNC_H

#include <SDL/SDL.h>

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
SDL_Surface* load_image(char *path);

#endif
