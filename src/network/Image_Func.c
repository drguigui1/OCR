#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Image_Func.h"

// -> Loading an image from a file
SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}



