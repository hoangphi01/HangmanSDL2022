#include "SDL_common.h"
#include "SDL_texture.h"
#include "SDL_button.h"

using namespace std;

SDL_Color textColorInMain{ 255, 255, 255 };

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Current displayed texture
SDL_Texture* gTexture = NULL;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//Current displayed PNG image
SDL_Surface* gPNGSurface = NULL;

//Color of text
//SDL_Color textColor{ 0, 0, 0 };

//Gallow texture
Texture gGallow;

// Button textures
Texture gStartButton;
Texture gEasyButton;
Texture gMedButton;
Texture gHardButton;
Texture gPauseButton;
Texture gVolumeButton;
Texture gChangeButton;

// Body textures
Texture gBody1;
Texture gBody2;
Texture gBody3;
Texture gBody4;
Texture gBody5;
Texture gBody6;

// Screen textures
Texture gLoseScreen;
Texture gWinScreen;
Texture gMainMenu;

// Background textures
Texture gBackground1;
Texture gBackground2;
Texture gBackground3;

// Font
TTF_Font* gFont = NULL;
Texture gFontPlayer;
Texture gGuessedWord;

Texture gInputText;

// Sfx
Mix_Chunk* gBackgroundSound = NULL;

Texture gTimePlayer;
const int NUMBER{ 10 };
SDL_Rect gFontClips[NUMBER];

//Get random word
vector<string> GetWords() {
	ifstream readLine;
	string currentWord;
	vector<string> wordList;

	readLine.open("Dictionary/data.txt");

	if (readLine.is_open()) {
		while (getline(readLine, currentWord)) {
			wordList.push_back(currentWord);
		}
		readLine.close();
	}
	else {
		cerr << "Unable to open text file";
		exit(1);
	}

	return wordList;
}

Uint32 play(bool& playAgain, bool& introScreen, Uint32 totalTime) {
	Uint32 score{ 0 };

	Uint32 startTimeLevel1 = 60;
	Uint32 startTimeLevel2 = 30;
	Uint32 startTimeLevel3 = 20;
	Uint32 timeVal = 0;

	Uint32 gameStartTime;
	string usedTime;
	/// Variables for rendering

	// render in game score
	Uint8 scoreAlpha{ 3 };

	//level of game
	int level = 0;

	// number of guesses
	int guessCount = 0;

	// boolean for rendering
	bool intro = true;
	bool insideLevelMenu = false;

	bool quit{ false };
	bool startGame{ false };
	bool gameStarted{ false };
	bool die{ false };
	bool reachedGround{ false };
	bool gameOver{ false };
	bool scoreBoard{ false };
	bool insideAdvance{ false };
	bool insideBack{ false };
	bool right{ true };
	bool switchSide{ false };
	bool scored{ false };

	//boolean for level
	bool insideLevel1{ false };
	bool insideLevel2{ false };
	bool insideLevel3{ false };

	//Event handler
	SDL_Event e;

	//Get random word
	vector<string> resultWord = GetWords();

	int k = (rand() % resultWord.size());
	string testWord = resultWord[k];
	string finalWord = testWord;
	transform(finalWord.begin(), finalWord.end(), finalWord.begin(), ::toupper);
	transform(testWord.begin(), testWord.end(), testWord.begin(), ::toupper);
	cout << testWord << endl;
	string inputText = string(testWord.length(), '-');

	//While application is running
	while (!quit) {


		//Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			//User requests quit
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				if (!insideLevelMenu) {
					if (e.key.keysym.sym == SDLK_SPACE) {
						insideLevelMenu = true;
					}
				}

				else {
					if (e.key.keysym.sym == SDLK_1) {
						insideLevel1 = true;
					}

					else if (e.key.keysym.sym == SDLK_2) {
						insideLevel2 = true;
					}

					else if (e.key.keysym.sym == SDLK_3) {
						insideLevel3 = true;
					}

				}

			}
			//read from keyboard
			if (e.type == SDL_TEXTINPUT) {
				size_t diTimKhoBau = testWord.find(e.text.text);

				if (diTimKhoBau != std::string::npos) {
					for (int i = 0; i < testWord.length(); i++) {
						cout << testWord << endl;
						if (testWord[i] == *e.text.text) {
							inputText[i] = *e.text.text;
						}
					}
				}

				else {
					guessCount++;
					if (insideLevel2) {
						startTimeLevel2 -= 3;
					}
					else if (insideLevel3) {
						startTimeLevel2 -= 5;
					}
				}
			}

			if (e.type == SDL_MOUSEBUTTONUP) {
				buttonHandleEvent(&e, intro, insideLevelMenu, insideLevel1, insideLevel2, insideLevel3, playAgain, quit);
			}
			//buttonHandleEvent(&e, intro, insideLevelMenu, insideLevel1, insideLevel2, insideLevel3);

		}

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		//Render texture to screen
		Mix_PlayChannel(-1, gBackgroundSound, -1);
		renderMainMenu();
		if (intro) {
			renderStart();
			gameStartTime = SDL_GetTicks() / 1000;
		}

		else if (insideLevelMenu) {
			renderButton(insideLevelMenu);
			gameStartTime = SDL_GetTicks() / 1000;
		}

		else if (insideLevel1) {
			renderBackground1();
			renderGallow();

			timeVal = SDL_GetTicks() / 1000 - totalTime;
			int remainTime = startTimeLevel1 - timeVal + gameStartTime;
			string nowTime = std::to_string(remainTime);

			if (!gameOver) {
				usedTime = std::to_string(startTimeLevel1 - remainTime);
			}


			gTimePlayer.loadFromRenderedText(gRenderer, gFont, nowTime, textColorInMain);
			gTimePlayer.render(gRenderer, 370, 10);

			gInputText.loadFromRenderedText(gRenderer, gFont, inputText.c_str(), textColorInMain);
			gInputText.render(gRenderer, 225, 500);

			if (guessCount == 1) {
				renderBody1();
			}
			if (guessCount == 2) {
				renderBody1();
				renderBody2();
			}
			if (guessCount == 3) {
				renderBody1();
				renderBody2();
				renderBody3();
			}
			if (guessCount == 4) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
			}
			if (guessCount == 5) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
				renderBody5();
			}
			if (guessCount == 6) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
				renderBody5();
				renderBody6();
			}

			if (guessCount > 6 || remainTime <= 0) {
				gameOver = true;

				renderLoseBackground();
				gInputText.loadFromRenderedText(gRenderer, gFont, finalWord.c_str(), textColorInMain);
				gInputText.render(gRenderer, 225, 400);

				gTimePlayer.loadFromRenderedText(gRenderer, gFont, "You spend: " + usedTime + " seconds", textColorInMain);
				gTimePlayer.render(gRenderer, 225, 500);
			}

			if (testWord.compare(inputText) == 0) {
				gameOver = true;

				renderWinBackground();
				gInputText.loadFromRenderedText(gRenderer, gFont, finalWord.c_str(), textColorInMain);
				gInputText.render(gRenderer, 225, 400);

				gTimePlayer.loadFromRenderedText(gRenderer, gFont, "You spend: " + usedTime + " seconds", textColorInMain);
				gTimePlayer.render(gRenderer, 225, 500);
			}
		}

		else if (insideLevel2) {
			renderBackground2();
			renderGallow();

			timeVal = SDL_GetTicks() / 1000 - totalTime;
			int remainTime = startTimeLevel2 - timeVal + gameStartTime;
			string nowTime = std::to_string(remainTime);

			if (!gameOver) {
				usedTime = std::to_string(startTimeLevel2 - remainTime);
			}

			gTimePlayer.loadFromRenderedText(gRenderer, gFont, nowTime, textColorInMain);
			gTimePlayer.render(gRenderer, 370, 10);

			gInputText.loadFromRenderedText(gRenderer, gFont, inputText.c_str(), textColorInMain);
			gInputText.render(gRenderer, 225, 500);

			if (guessCount == 1) {
				renderBody1();
			}
			if (guessCount == 2) {
				renderBody1();
				renderBody2();
			}
			if (guessCount == 3) {
				renderBody1();
				renderBody2();
				renderBody3();
			}
			if (guessCount == 4) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
			}
			if (guessCount == 5) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
				renderBody5();
			}
			if (guessCount == 6) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
				renderBody5();
				renderBody6();
			}

			if (guessCount > 6 || remainTime <= 0) {
				gameOver = true;

				renderLoseBackground();
				gInputText.loadFromRenderedText(gRenderer, gFont, finalWord.c_str(), textColorInMain);
				gInputText.render(gRenderer, 225, 400);

				gTimePlayer.loadFromRenderedText(gRenderer, gFont, "You spend: " + usedTime + " seconds", textColorInMain);
				gTimePlayer.render(gRenderer, 225, 500);
			}

			if (testWord.compare(inputText) == 0) {
				gameOver = true;

				renderWinBackground();
				gInputText.loadFromRenderedText(gRenderer, gFont, finalWord.c_str(), textColorInMain);
				gInputText.render(gRenderer, 225, 400);

				gTimePlayer.loadFromRenderedText(gRenderer, gFont, "You spend: " + usedTime + " seconds", textColorInMain);
				gTimePlayer.render(gRenderer, 225, 500);
			}
		}

		else if (insideLevel3) {
			renderBackground3();
			renderGallow();

			timeVal = SDL_GetTicks() / 1000 - totalTime;
			int remainTime = startTimeLevel3 - timeVal + gameStartTime;
			string nowTime = std::to_string(remainTime);

			if (!gameOver) {
				usedTime = std::to_string(startTimeLevel3 - remainTime);
			}

			gTimePlayer.loadFromRenderedText(gRenderer, gFont, nowTime, textColorInMain);
			gTimePlayer.render(gRenderer, 370, 10);

			gInputText.loadFromRenderedText(gRenderer, gFont, inputText.c_str(), textColorInMain);
			gInputText.render(gRenderer, 225, 500);

			if (guessCount == 1) {
				renderBody1();
			}
			if (guessCount == 2) {
				renderBody1();
				renderBody2();
			}
			if (guessCount == 3) {
				renderBody1();
				renderBody2();
				renderBody3();
			}
			if (guessCount == 4) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
			}
			if (guessCount == 5) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
				renderBody5();
			}
			if (guessCount == 6) {
				renderBody1();
				renderBody2();
				renderBody3();
				renderBody4();
				renderBody5();
				renderBody6();
			}

			if (guessCount > 6 || remainTime <= 0) {
				gameOver = true;

				renderLoseBackground();
				gInputText.loadFromRenderedText(gRenderer, gFont, finalWord.c_str(), textColorInMain);
				gInputText.render(gRenderer, 225, 400);

				gTimePlayer.loadFromRenderedText(gRenderer, gFont, "You spend: " + usedTime + " seconds", textColorInMain);
				gTimePlayer.render(gRenderer, 225, 500);
			}

			if (testWord.compare(inputText) == 0) {
				gameOver = true;

				renderWinBackground();
				gInputText.loadFromRenderedText(gRenderer, gFont, finalWord.c_str(), textColorInMain);
				gInputText.render(gRenderer, 225, 400);

				gTimePlayer.loadFromRenderedText(gRenderer, gFont, "You spend: " + usedTime + " seconds", textColorInMain);
				gTimePlayer.render(gRenderer, 225, 500);
			}
		}


		renderControlButton();
		//renderTimeLeft();

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
	return score;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	Uint32 highscore;
	Uint32 score{ 0 };
	Uint32 totalTime = 0;

	if (!init())
	{
		cout << "Failed to initialize" << endl;
	}
	else
	{
		//Load media
		if (!loadMedia()) {
			cout << "Failed to load media" << endl;
		}
		else {
			srand(time(NULL)); // initialize random seed for random length
			bool intro{ true };
			bool playAgain{ true };
			while (playAgain) {
				playAgain = false;
				score = play(playAgain, intro, totalTime);
				totalTime++;
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}