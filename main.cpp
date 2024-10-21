#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include"main.h"
using namespace std;

//default settings
int screenWidth = 640;
int screenHeight = 480;
//end settings

//path directory
const char* path = NULL; //makes the paths work
string titleScreenString = "/assets/TitleBackground.bmp";
const char* titleScreenPath = assetPath(titleScreenString);

//end paths

//SDL pointers
SDL_Window* gameWindow = NULL; //main window we render to
SDL_Surface* gameWindowSurface = NULL; //surface of window we render to
SDL_Surface* currentScreenSurface = NULL; //hold current screen Surface
SDL_Surface* titleScreenSurface = NULL; //image to be displayed
//end SDL pointers

//screen declarations
Screen gameScreen(NULL, NULL); //placeholder for current Screen object
Screen titleScreen(titleScreenSurface, titleScreenPath);
//end screen decs



int main(int argc, char* args[]) {
	startGame();

	return 0;
}

int startGame() {
	if (!initSDL()) { cout << "failed to initialize.\n"; }
	else {
		if (!loadScreen(titleScreen)) {
			cout << "failed to load title screen. SDL error: \n" << SDL_GetError();
		}
		else {
			SDL_BlitSurface(titleScreenSurface, NULL, gameWindowSurface, NULL); //load title screen
			//Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	//clear screen
	gameScreen.clearScreen();
	return 0;
}

