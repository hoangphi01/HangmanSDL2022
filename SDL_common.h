#pragma once
#ifndef SDL_common.h

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <sstream>

#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdint.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//The max number of guesses
const int MAX_BAD_GUESSES = 6;

//Position of start button
const int START_X = SCREEN_WIDTH / 2 - 90;
const int START_Y = SCREEN_HEIGHT / 2 + 35;

//Position of easy button
const int LEVEL_BUTTON_X = SCREEN_WIDTH / 2 - 58;
const int EASY_Y = SCREEN_HEIGHT / 2;

//Position of medium button
const int MED_Y = SCREEN_HEIGHT / 2 + 85;

//Position of hard button
const int HARD_Y = SCREEN_HEIGHT / 2 + 170;

//Position of control buttons
const int CTRL_BUTTON_Y = 20;
const int CTRL_BUTTON_PAUSE_X = SCREEN_WIDTH - 90;
const int CTRL_BUTTON_VOLUME_X = SCREEN_WIDTH - 170;
const int CTRL_BUTTON_CHANGE_X = SCREEN_WIDTH - 260;

//Position of gallow
const int GALLOW_X = SCREEN_WIDTH / 2 - 116;
const int GALLOW_Y = SCREEN_HEIGHT / 2 - 48;

//Position of bodies
const int BODY1_X = SCREEN_WIDTH / 2 - 155;
const int BODY1_Y = SCREEN_HEIGHT / 2;

const int BODY2_X = SCREEN_WIDTH / 2 - 108;
const int BODY2_Y = SCREEN_HEIGHT / 2 + 69;

const int BODY3_X = SCREEN_WIDTH / 2 - 155;
const int BODY3_Y = SCREEN_HEIGHT / 2 + 68;

const int BODY4_X = SCREEN_WIDTH / 2 - 52;
const int BODY4_Y = SCREEN_HEIGHT / 2 + 71;

const int BODY5_X = SCREEN_WIDTH / 2 - 132;
const int BODY5_Y = SCREEN_HEIGHT / 2 + 131;

const int BODY6_X = SCREEN_WIDTH / 2 - 84;
const int BODY6_Y = SCREEN_HEIGHT / 2 + 134;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture(std::string path);

//Loads individual image
SDL_Surface* loadSurface(std::string path);

//The window renderer
extern SDL_Renderer* gRenderer;

//Current displayed texture
extern SDL_Texture* gTexture;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//Current displayed PNG image
extern SDL_Surface* gPNGSurface;

//error handling
void SDL_windowsError();

void SDL_intializeError();

void SDL_surfaceError();

void SDL_loadMediaError();

//render elements
void renderMainMenu();
void renderStart();

//render background
void renderBackground1();
void renderBackground2();
void renderBackground3();

void renderButton(bool&);
void renderControlButton();
void renderGallow();
void renderLoseBackground();
void renderWinBackground();

//render bodies
void renderBody1();
void renderBody2();
void renderBody3();
void renderBody4();
void renderBody5();
void renderBody6();

void renderTimeLeft();
void renderWord();


#endif
