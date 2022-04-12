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
#include "frogSimulator.h"
#define NUMMENU 3




int start_sdl(void)
{
	bool quit = false;
	SDL_Event event;
	int objectFrameWidth = 0, objectFrameHeight = 0, backgroundFrameWidth = 0, backgroundFrameHeight = 0;
	int frameTime = 0, countTime = 0;
	int objectTextureWidth = 0, objectTextureHeight = 0, backgroundTextureWidth = 0, backgroundTextureHeight = 0;
	
	
	// initialize graphics system 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		printf("error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("CrappyCraps!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (!window)
	{
		printf("error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	//create renderer to set up graphics hardware
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, render_flags);
	if (!renderer)
	{
		printf("error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Load image into memory using SDL_image_library function
	SDL_Surface* objectSurface = IMG_Load("../resources/frog_sprites.png");
	if (!objectSurface)
	{
		printf("error creating surface\n: %s", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	//
	SDL_Surface* backgroundSurface = IMG_Load("../resources/img-itch-zone_flat_mountains.png");
	if (!backgroundSurface)
	{
		printf("error creating surface\n: %s", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_FreeSurface(backgroundSurface);
	if (!backgroundTexture)
	{
		printf("error creating texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundTextureWidth, &backgroundTextureHeight);
	//backgroundFrameWidth = backgroundTextureWidth / 12;
	//backgroundFrameHeight = backgroundTextureHeight / 8;

	SDL_Texture* objectTexture = SDL_CreateTextureFromSurface(renderer, objectSurface);
	SDL_FreeSurface(objectSurface);
	if (!objectTexture)
	{
		printf("error creating texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	SDL_QueryTexture(objectTexture, NULL, NULL, &objectTextureWidth, &objectTextureHeight);
	objectFrameWidth = objectTextureWidth / 12;
	objectFrameHeight = objectTextureHeight / 8;



	SDL_Rect srcRect = { objectFrameWidth, objectFrameHeight, 48, 44 };
	SDL_Rect dstRect = { 0, 330, 32, 64 };

	srcRect.x = 0;
	srcRect.y = 0;

	while (!quit)
	{
		

		while (SDL_PollEvent(&event) != NULL)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					dstRect.y += 41;
					srcRect.y = (3 * objectFrameHeight);
					srcRect.x = (2 * objectFrameWidth);
				
				}
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					srcRect.x = (2 * objectFrameWidth);
					srcRect.y = (5 * objectFrameHeight);
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					srcRect.x = (2 * objectFrameWidth);
					srcRect.y = (6 * objectFrameHeight);
				}
				break;
			case SDL_KEYDOWN:
				//Move frog Left
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					if ((dstRect.x / 12 ) <= 0)
						srcRect.y = (5 * objectFrameHeight);
					else
					{
						//Check if Left facing image is selected, set if not
						if (srcRect.y != (1 * objectFrameHeight))
							srcRect.y = (1 * objectFrameHeight);

						dstRect.x -= 20.50;
						//change sprites
						srcRect.x += objectFrameWidth;
						if (srcRect.x >= (3 * objectFrameWidth))
						{
							srcRect.x = 0;

						}
					}
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					//Check if at Boundary
					if ((dstRect.x / 12) >= objectFrameWidth)
						srcRect.y = (6 * objectFrameHeight);

					else
					{
						
						dstRect.x += 20.50;
						srcRect.x += objectFrameWidth;
						if (srcRect.x >= (3 * objectFrameWidth))
						{
							srcRect.x = 3;

						}
					}
					if (srcRect.y != (2 * objectFrameHeight))
						srcRect.y = (2 * objectFrameHeight);
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{

					//Check if at Boundary
					if ((dstRect.y / 8) <= objectFrameHeight * 0.9)
						srcRect.y = (7 * objectFrameHeight);
					else
					{
						//Move image up
						dstRect.y -= 20.50;

						if (srcRect.y != (3 * objectFrameHeight))
							srcRect.y = (3 * objectFrameHeight);

						srcRect.x += objectFrameHeight;
						if (srcRect.x >= (3 * objectFrameHeight))
						{
							srcRect.x = 0;

						}
					}
				}

				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					//Check if at Boundary
					if ((dstRect.y / 8) >= objectFrameHeight * 0.8)
						srcRect.y = (4 * objectFrameHeight);
					else
					{

						//Move image down
						dstRect.y += 20.50;
						if (srcRect.y != (0 * objectFrameHeight))
							srcRect.y = (0 * objectFrameHeight);
						srcRect.x += objectFrameHeight;
						if (srcRect.x >= (3 * objectFrameWidth))
						{
							srcRect.x = 3;

						}
					}

					
				}
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					//Check if at Boundary
					if ((dstRect.y / 8) <= objectFrameHeight * 0.8)
						srcRect.y = (7 * objectFrameHeight);
					else
					{
						srcRect.y = (3 * objectFrameHeight);
						srcRect.x = (2 * objectFrameWidth);
						dstRect.y -= 40.50;
					}
				}
				break;
			}
			
		}
		
		
	
		SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
		SDL_RenderCopy(renderer, objectTexture, &srcRect, &dstRect);


		SDL_RenderPresent(renderer);

		SDL_RenderClear(renderer);
	
	}
	
	//animation loop going left using 3 frames from spritesheet 
	frameTime++;
	if (FPS / frameTime == 12)
	{
		countTime++;
		frameTime = 0;
		srcRect.x += objectFrameWidth;
		if (countTime > 2)
		{
			srcRect.x = 0;
			countTime = 0;
			dstRect.x -= 5.25;
		}
	}
	
	//wait 5 seconds


	//Cleanup resources 
	SDL_DestroyTexture(objectTexture);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
