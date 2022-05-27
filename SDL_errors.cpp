#include "SDL_common.h"

using namespace std;

void SDL_windowsError() {
	printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
}

void SDL_intializeError() {
	printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
}

void SDL_loadMediaError() {
	printf("Failed to load texture! SDL Error: %s\n", SDL_GetError());
}

void SDL_surfaceError() {
	printf("Unable to load image %s! SDL_image Error: %s\n", IMG_GetError());
}