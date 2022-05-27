#include "SDL_common.h"
#include "SDL_texture.h"

using namespace std;

SDL_Color textColor{ 255, 255, 255 };

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_intializeError();
		success = false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	if (TTF_Init() == -1) {
		cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}

	else
	{
		//Create window
		gWindow = SDL_CreateWindow("HANGMAN 2022 by hoangphi01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			SDL_windowsError();
			success = false;
		}
		else
		{
			//Initialize PNG loading
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				SDL_windowsError();
				success = false;
			}
			else
			{
				//Get window surface
				gScreenSurface = SDL_GetWindowSurface(gWindow);
			}

			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Prevent overloading CPU & GPU. DS:04.29.20
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}

			else
			{

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	//Load success flag
	bool success = true;

	//load gallow
	if (!gGallow.loadFromFile(gRenderer, "Image/gallow.png")) {
		SDL_loadMediaError();
		success = false;
	}

	//load PNG button textures
	if (!gStartButton.loadFromFile(gRenderer, "Image/startButton.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gPauseButton.loadFromFile(gRenderer, "Image/pauseButton.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gEasyButton.loadFromFile(gRenderer, "Image/easyButton.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gMedButton.loadFromFile(gRenderer, "Image/medButton.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gHardButton.loadFromFile(gRenderer, "Image/hardButton.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gVolumeButton.loadFromFile(gRenderer, "Image/volumeButton.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gChangeButton.loadFromFile(gRenderer, "Image/changeButton.png")) {
		SDL_loadMediaError();
		success = false;
	}

	//load main menu textures
	if (!gMainMenu.loadFromFile(gRenderer, "Image/mainMenu.png")) {
		SDL_loadMediaError();
		success = false;
	}

	//load background textures
	if (!gBackground1.loadFromFile(gRenderer, "Image/Background1.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gBackground2.loadFromFile(gRenderer, "Image/Background2.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gBackground3.loadFromFile(gRenderer, "Image/Background3.png")) {
		SDL_loadMediaError();
		success = false;
	}

	//load win-lose
	if (!gWinScreen.loadFromFile(gRenderer, "Image/winScreen.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gLoseScreen.loadFromFile(gRenderer, "Image/loseScreen.png")) {
		SDL_loadMediaError();
		success = false;
	}

	//load bodies
	if (!gBody1.loadFromFile(gRenderer, "Image/body1.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gBody2.loadFromFile(gRenderer, "Image/body2.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gBody3.loadFromFile(gRenderer, "Image/body3.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gBody4.loadFromFile(gRenderer, "Image/body4.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gBody5.loadFromFile(gRenderer, "Image/body5.png")) {
		SDL_loadMediaError();
		success = false;
	}

	if (!gBody6.loadFromFile(gRenderer, "Image/body6.png")) {
		SDL_loadMediaError();
		success = false;
	}

	// Load font
	gFont = TTF_OpenFont("Font/HangmanFont.ttf", 70);
	if (gFont == NULL) {
		cout << "Font failed" << TTF_GetError() << " " << SDL_GetError() << endl;
		success = false;
	}

	// Load music
	gBackgroundSound = Mix_LoadWAV("Music/HangmanSfx.wav");
	if (gBackgroundSound == NULL) {
		cout << "Failed to load sound. " << Mix_GetError() << " " << SDL_GetError() << endl;
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	gBackground1.free();
	gBackground2.free();
	gBackground3.free();

	gBody1.free();
	gBody2.free();
	gBody3.free();
	gBody4.free();
	gBody5.free();
	gBody6.free();


	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		SDL_surfaceError();
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
		if (optimizedSurface == NULL)
		{
			SDL_surfaceError();
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

//void render elements

//render bodies (1-6)
void renderBody1() {
	gBody1.render(gRenderer, BODY1_X, BODY1_Y);
}

void renderBody2() {
	gBody2.render(gRenderer, BODY2_X, BODY2_Y);
}

void renderBody3() {
	gBody3.render(gRenderer, BODY3_X, BODY3_Y);
}

void renderBody4() {
	gBody4.render(gRenderer, BODY4_X, BODY4_Y);
}

void renderBody5() {
	gBody5.render(gRenderer, BODY5_X, BODY5_Y);
}

void renderBody6() {
	gBody6.render(gRenderer, BODY6_X, BODY6_Y);
}

//render mainmenu
void renderMainMenu() {
	gMainMenu.render(gRenderer, 0, 0);
}

void renderStart() {
	gStartButton.render(gRenderer, START_X, START_Y);
}

void renderButton(bool& insideLevelMenu) {
	gEasyButton.render(gRenderer, LEVEL_BUTTON_X, EASY_Y);
	gMedButton.render(gRenderer, LEVEL_BUTTON_X, MED_Y);
	gHardButton.render(gRenderer, LEVEL_BUTTON_X, HARD_Y);
}

void renderBackground1() {
	gBackground1.render(gRenderer, 0, 0);
	//cout << "test2" << endl;

}

void renderBackground2() {
	gBackground2.render(gRenderer, 0, 0);
	//cout << "test2" << endl;

}

void renderBackground3() {
	gBackground3.render(gRenderer, 0, 0);
	//cout << "test2" << endl;

}

void renderLoseBackground() {
	gLoseScreen.render(gRenderer, 0, 0);
}

void renderWinBackground() {
	gWinScreen.render(gRenderer, 0, 0);
}

void renderControlButton() {
	gChangeButton.render(gRenderer, CTRL_BUTTON_CHANGE_X, CTRL_BUTTON_Y);
	gVolumeButton.render(gRenderer, CTRL_BUTTON_VOLUME_X, CTRL_BUTTON_Y);
	gPauseButton.render(gRenderer, CTRL_BUTTON_PAUSE_X, CTRL_BUTTON_Y);
}

void renderGallow() {
	gGallow.render(gRenderer, GALLOW_X, GALLOW_Y);
}



