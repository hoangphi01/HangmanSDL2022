#ifndef SDL_button_h
#define SDL_button_h

#include <SDL.h>
#include <SDL_mixer.h>



//Size of start button
const int startButtonWeight = 180;
const int startButtonHeight = 70;

//Level buttons
const int levelButtonWeight = 115;

//Size of easy button
const int easyButtonHeight = 70;

//Size of medium button
const int mediumButtonHeight = 70;

//Size of hard button
const int hardButtonHeight = 70;

//Other buttons
//Size of volume button
const int volumeButtonWeight = 115;
const int volumeButtonHeight = 70;

//Size of pause button
const int pauseButtonWeight = 115;
const int pauseButtonHeight = 70;

//Size of change button
const int changeButtonWeight = 115;
const int changeButtonHeight = 70;

void buttonHandleEvent(SDL_Event*, bool&, bool&, bool&, bool&, bool&, bool&, bool&);


#endif // 