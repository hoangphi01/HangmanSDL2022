#include "SDL_common.h"
#include "SDL_texture.h"

using namespace std;

Texture::Texture() {
	mTexture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture() {
	free();
}

bool Texture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, string content, SDL_Color textColor) {
	free();
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, content.c_str(), textColor);
	if (textSurface == NULL) {
		cout << "Unable to render text surface. " << TTF_GetError() << endl;
	}
	else {
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL) {
			cout << "Unable to create texture from rendered text. " << SDL_GetError() << endl;
		}
		else {
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}

bool Texture::loadFromFile(SDL_Renderer* renderer, string path) {
	// deallocate
	free();

	SDL_Texture* newTexture{ NULL };

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		cout << "Unable to load image " << path.c_str() << endl
			<< "SDL_image err: " << IMG_GetError() << endl;
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTexture == NULL) {
			cout << "Unable to create texture from " << path.c_str() << endl
				<< "SDL err: " << SDL_GetError() << endl;
		}
		else {
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != NULL;
}

void Texture::free() {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad{ x, y, width, height };


	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}