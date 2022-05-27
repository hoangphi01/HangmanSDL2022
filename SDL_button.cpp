#include "SDL_common.h"
#include "SDL_button.h"

using namespace std;
bool isMuted = false;

void buttonHandleEvent(SDL_Event* e, bool& intro, bool& insideLevelMenu, bool& insideLevel1, bool& insideLevel2, bool& insideLevel3, bool& playAgain, bool& quit) {
	if (e->type == SDL_MOUSEBUTTONUP) {
		int x, y;
		SDL_GetMouseState(&x, &y);

		//level
		int level;

		//control Sfx
		if (x >= CTRL_BUTTON_VOLUME_X && x <= CTRL_BUTTON_VOLUME_X + volumeButtonHeight) {
			if (y >= CTRL_BUTTON_Y && y <= CTRL_BUTTON_Y + volumeButtonWeight) {
				if (isMuted == false) {
					isMuted = true;
					Mix_Pause(-1);
				}
				else if (isMuted == true) {
					isMuted = false;
					Mix_Resume(-1);
				}
			}
		}

		//RESTART GAME
		if (x >= CTRL_BUTTON_CHANGE_X && x <= CTRL_BUTTON_CHANGE_X + volumeButtonHeight) {
			if (y >= CTRL_BUTTON_Y && y <= CTRL_BUTTON_Y + changeButtonWeight) {
				quit = true;
				playAgain = true;
			}
		}

		//INCREASE TIME
		if (x >= CTRL_BUTTON_PAUSE_X && x <= CTRL_BUTTON_PAUSE_X + pauseButtonHeight) {
			if (y >= CTRL_BUTTON_Y && y <= CTRL_BUTTON_Y + pauseButtonWeight) {
				
			}
		}

		//select level
		if (insideLevelMenu && !intro) {
			if (x >= LEVEL_BUTTON_X && x <= LEVEL_BUTTON_X + levelButtonWeight) {
				if (y >= EASY_Y && y <= EASY_Y + easyButtonHeight) {
					level = 1;
					cout << "Level1!!!\n";
					insideLevel1 = true;
					insideLevel2 = false;
					insideLevel3 = false;
					insideLevelMenu = false;
				}
				else if (y >= MED_Y && y <= MED_Y + mediumButtonHeight) {
					level = 2;
					cout << "Level2!!!\n";
					insideLevel2 = true;
					insideLevel1 = false;
					insideLevel3 = false;
					insideLevelMenu = false;
				}
				else if (y >= HARD_Y && y <= HARD_Y + hardButtonHeight) {
					level = 3;
					cout << "Level3!!!\n";
					insideLevel3 = true;
					insideLevel2 = false;
					insideLevel1 = false;
					insideLevelMenu = false;
				}
			}
		}


		//intro screen
		if (intro) {
			if (y >= START_Y && y <= START_Y + startButtonHeight) {
				if (x >= START_X && x <= START_X + startButtonWeight) {
					cout << "Inside!!!\n";
					insideLevelMenu = true;
					intro = false;
				}
			}
		}

	}

}