#include <SDL.h>
#include <stdio.h>
#include <iostream>
using namespace std;

//Screen Dimensions
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480; 
/*add ability to change later*/

bool init(); //starts SDL and create window
bool loadMedia(); //loads media
void close(); //frees media and shuts down SDL

/* SDL_ are data types. these are pointers.*/

SDL_Window* gWindow = NULL; //window we render to
SDL_Surface* gScreenSurface = NULL; //surface contained by window
SDL_Surface* gTitleScreen = NULL; //image to be displayed


bool init() { //init SDL
	bool success = true; //initialization flag

	if (SDL_Init(SDL_INIT_VIDEO) < 0) { //check for fail
		cout << "SDL failed to initialize. SDL_Error: \n" << SDL_GetError();
		success = false;
	}
	else { //create window
		gWindow = SDL_CreateWindow("Home Gardener v.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //redefine gWindow. parameters name xpos ypos x y
		if (gWindow == NULL) { //check for fail
			cout << "Window could not be created. SDL_Error: \n" << SDL_GetError();
			success = false;
		}
		else {
			gScreenSurface = SDL_GetWindowSurface(gWindow); //get window surface
		}
	}
	return success;
}

bool loadMedia() {
	bool success = true; //get success flag
	gTitleScreen = SDL_LoadBMP("assets/TitleBackground.bmp");
	if (gTitleScreen == NULL) {
		cout << "Failed to load title. SDL_ERROR: \n", SDL_GetError();
		success = false;
	}

	return success;
}

void close() {
	//deallocate surface
	SDL_FreeSurface(gTitleScreen);
	gTitleScreen = NULL;

	//destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

int main(int argc, char* args[]) {
	//initialize
	if (!init()) { //check for failed init
		cout << "failed to initialize.\n";
	}
	else { //load screen
		if (!loadMedia()) { //check for fail
			cout << "failed to load title.\n";
		}
		else { //change screen
			SDL_BlitSurface(gTitleScreen, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
			//Hack to get window to stay up
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	close();
	return 0;
}