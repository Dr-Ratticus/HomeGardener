#pragma once
#include<iostream>
#include"main.h"
#include <SDL.h>
#include <stdio.h>
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

//screen declarations
Screen gameScreen(NULL, NULL); //placeholder for current Screen object
Screen titleScreen(titleScreenSurface, titleScreenPath);
//end screen decs

//SDL pointers
SDL_Window* gameWindow = NULL; //main window we render to
SDL_Surface* gameWindowSurface = NULL; //surface of window we render to
SDL_Surface* currentScreenSurface = NULL; //hold current screen Surface
SDL_Surface* titleScreenSurface = NULL; //image to be displayed
//end SDL pointers

//functions
const char* assetPath(string Spath) { //convert "/asset/blah.bmp" to usable path
	const char* realPath = Spath.c_str();
	return realPath;
};

bool initSDL() { //initiate SDL
	bool success = true; //declare output variable
	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //check for fail
		cout << "SDL failed to initialize. SDL_Error: \n" << SDL_GetError();
		success = false;
	}
	else { //create window
		gameWindow = SDL_CreateWindow("Home Gardener v.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN); //redefine gameWindow
		if (gameWindow == NULL) { //check for fail
			cout << "Window could not be created. SDL_Error: \n" << SDL_GetError();
			success = false;
		}
		else {
			gameWindowSurface = SDL_GetWindowSurface(gameWindow); //get window surface
		}
	}
	return success;
};

bool loadScreen(Screen newScreen) {
	bool success = true; //output variable
	newScreen = SDL_LoadBMP(path);
	if (newScreen.getSurface() == NULL) { //print debug for fail
		cout << "failed to load screen. SDL error: \n"
			<< SDL_GetError();
		success = false;
	}
	currentScreenSurface = newScreen.getSurface(); //keep track of current screen surface
	gameScreen = newScreen; //keep track of current screen obj
	return success;
};


int startGame() {
	if (!initSDL()) { cout << "failed to initialize.\n"; }
	else {
		if (!loadScreen(titleScreen)) {
			cout << "failed to load title screen. SDL error: \n" << SDL_GetError();
		}
		else {
			SDL_BlitSurface(titleScreen, NULL, gameWindowSurface, NULL); //load title screen
			//Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	//clear screen
	gameScreen.clearScreen();
	return 0;
}
//end functions