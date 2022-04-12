/*

Created By: Andrew Lefors
Created On: 2/24/2020
Project: Frog Simulator
File Version: 0.2.30.20

Description: This is the Frog life Simulator, written in C using the library SDL_C. Boundaries are set, animations respond to movement direction appropriatly. 


			NOTE: Frog Sprites acquired from rpgtileset.com
			NOTE: Animation background acquired from img-itchzone.com
			NOTE: Watched tutorials on SDL2 from numerous locations for animations.



*/

#pragma once
//SDL STuff
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
//Constant macros
#define penaltyValue 100
#define FPS 60
#define SCREEN_WIDTH (640)
#define SCREEN_HEIGHT (480)
#define SCROLL_SPEED (300)
//function prototypes
//Start SDL animated game
int start_sdl(void);
