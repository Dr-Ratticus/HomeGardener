#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include"main.cpp"
#include"externs.h"
using namespace std;


//classes
class Screen {
private:
	//variable declarations
	SDL_Surface* surfaceSDL;
	const char* path;
public: 
	//function prototypes
	Screen(SDL_Surface* = NULL, const char* = NULL); //constructor
	const char* getPath() { return path; } //in line accessor
	SDL_Surface* getSurface() { return surfaceSDL; } //in line accessor
	void modifyPath(string newPath);
	void modifySurface(SDL_Surface* newSurface); //modifiers
	void clearScreen();
};

Screen::Screen(SDL_Surface* windowSurface, const char* userPath) {
	surfaceSDL = windowSurface;
	path = userPath;
};
void Screen::modifyPath(string newPath) {
	path = assetPath(newPath);
};
void Screen::modifySurface(SDL_Surface* newSurface) {
	surfaceSDL = newSurface;
};

void Screen::clearScreen() { //close game window and clear surface
	SDL_FreeSurface(currentScreenSurface); //empty screen contents
	currentScreenSurface = NULL; //set screen to null
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
	SDL_Quit(); //turn off SDL
};
//end classes

//function declarations
const char* assetPath(string Spath);
bool initSDL();
bool loadScreen(Screen newScreen);
int startGame();
//end func declarations

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




//end functions
