#ifndef SDL_texture_h
#define SDL_texture_h

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

typedef uint8_t Uint8;

extern class Texture {
public:
	Texture();
	~Texture();

	bool loadFromRenderedText(SDL_Renderer*, TTF_Font*, std::string, SDL_Color);
	bool loadFromFile(SDL_Renderer*, std::string);
	void free();
	void setBlendMode(SDL_BlendMode);
	void setAlpha(Uint8);
	void render(SDL_Renderer*, int a, int b, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* mTexture;
	int width;
	int height;
};

// Button textures
extern Texture gStartButton;
extern Texture gEasyButton;
extern Texture gMedButton;
extern Texture gHardButton;
extern Texture gPauseButton;
extern Texture gVolumeButton;
extern Texture gChangeButton;

// Body textures
extern Texture gBody1;
extern Texture gBody2;
extern Texture gBody3;
extern Texture gBody4;
extern Texture gBody5;
extern Texture gBody6;

// Screen textures
extern Texture gLoseScreen;
extern Texture gWinScreen;
extern Texture gMainMenu;

// Background textures
extern Texture gBackground1;
extern Texture gBackground2;
extern Texture gBackground3;

// Font
extern TTF_Font* gFont;
extern Texture gFontPlayer;

// Gallow
extern Texture gGallow;

extern Texture gTimePlayer;
extern Texture gGuessedWord;
//const int NUMBER{ 10 };
//extern SDL_Rect gFontClips[NUMBER];

// Sound
extern Mix_Chunk* gBackgroundSound;

#endif // texture