#pragma once
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include"main.cpp"
using namespace std;

//default settings
extern int screenWidth = 640;
extern int screenHeight = 480;
//end settings

//path directory
extern const char* path = NULL; //makes the paths work
extern string titleScreenString = "/assets/TitleBackground.bmp";
extern const char* titleScreenPath = assetPath(titleScreenString);

//end paths

//SDL pointers
extern SDL_Window* gameWindow = NULL; //main window we render to
extern SDL_Surface* gameWindowSurface = NULL; //surface of window we render to
extern SDL_Surface* currentScreenSurface = NULL; //hold current screen Surface
extern SDL_Surface* titleScreenSurface = NULL; //image to be displayed
//end SDL pointers

//screen declarations
extern Screen gameScreen(NULL, NULL); //placeholder for current Screen object
extern Screen titleScreen(titleScreenSurface, titleScreenPath);
//end screen decs