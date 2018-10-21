#ifndef IMAGE_FUNC_H
#define IMAGE_FUNC_H

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
SDL_Surface* gray_to_surface (char *path);
#endif
