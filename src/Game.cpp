// Game.cpp
// Implementation of the Game class.
// Created on October 4, 2017
// Last modified on October 17, 2017

#include "Game.h"

Game::Game()
{
	_window = NULL, _screenSurface = NULL, _splashScreen = NULL;

	InitializeSDL();
	LoadMedia();
}

Game::~Game()
{
    Cleanup();
}

void Game::Run()
{
	// Game loop.
	while(!_quit)
	{
		Input();
		Update();
		Draw();
	}

	Cleanup();
}

bool Game::InitializeSDL()
{
    bool success = true;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error initializing SDL... Error: %s\n", SDL_GetError());
		success = false;
	}

	_window = SDL_CreateWindow("Game", 
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED, 
								SCREEN_WIDTH, 
								SCREEN_HEIGHT,
								SDL_WINDOW_SHOWN);
	
	if(_window == NULL)
	{
		printf("Error creating SDL window... Error: %s\n", SDL_GetError());
		success = false;
	}
	
	// This statement attaches the main screen surface to the window.
	_screenSurface = SDL_GetWindowSurface(_window);

    return success;
}

bool Game::LoadMedia()
{
	bool success = true;

	_splashScreen = SDL_LoadBMP("../assets/graphics/polygonwhale.bmp");
	if(_splashScreen == NULL)
	{
		printf("Error loading image... Error %s\n", SDL_GetError());
		success = false;
	}

	return success;
}

void Game::Input()
{
	// Variable to hold next event in the queue.
    SDL_Event e;

	// SDL_PollEvent pulls event from the event queue and stores it in e.
	// e will be assigned NULL when the queue is empty.
    while(SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
        case SDL_QUIT: // Close button on window.
            _quit = true;
            break;

        case SDL_KEYDOWN: // Key push.
			_keyDown[e.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP: // Key release.
			_keyDown[e.key.keysym.scancode] = false;
			break;
        }
    }
}

bool Game::IsKeyDown(int key)
{
	// find() will return map.end() if there is no data stored in key location
	// meaning key has yet to be pushed.
	std::map<int, bool>::iterator i = _keyDown.find(key);

	if(i == _keyDown.end())
		return false;

	else
		return _keyDown.at(key);

}

void Game::Update()
{
	if(IsKeyDown(SDL_SCANCODE_UP))
		printf("Up\n");

	if(IsKeyDown(SDL_SCANCODE_DOWN))
		printf("Down\n");

	if(IsKeyDown(SDL_SCANCODE_LEFT))
		printf("Left\n");

	if(IsKeyDown(SDL_SCANCODE_RIGHT))
		printf("Right\n");
}

void Game::Draw()
{
	// Update _screenSurface with the first argument.
	SDL_BlitSurface(_splashScreen, NULL, _screenSurface, NULL);

	// Draw _screenSurface to the window.
	SDL_UpdateWindowSurface(_window);
}

void Game::Cleanup()
{
    SDL_DestroyWindow(_window);
	SDL_FreeSurface(_splashScreen);
	_screenSurface = NULL, _splashScreen = NULL, _window = NULL;
	SDL_Quit();
}