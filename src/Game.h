// Game.h
// Created by Tommy Janna
// Class name: Game
// Description of class: Game class which creates a new instance of the game.
//                       This class contains methods which initialize the SDL framework,
//                       create a new window, handle the game loop,
//                       handle input, load graphics, and draw to the screen.
// Created on October 4, 2017
// Last modified on October 20, 2017

#ifndef GAME_H
#define GAME_H

#include "GameObjects/SplashScreen.h"
#include "Texture.h"
#include "GameObject.h"
#include <SDL_image.h>
#include <SDL.h>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

class GameObject;
class SplashScreen;

class Game
{
public:
    
    Game();
    ~Game();

    void Run();

    // Leave public because it needs to be accessible by basically everything duuhhh.
    static SDL_Renderer* _renderer;
    static std::vector<GameObject*> _objects;

private:

    bool InitializeSDL();
    void LoadMedia();

    void Input();
    bool IsKeyDown(int);

    void Update();
    void Draw();
    void Cleanup();

    // Game loop exit flag.
    bool _quit;

    // Map for storing keyboard input
    std::map<int, bool> _keyDown;

    SDL_Window* _window;

    SplashScreen* _splashScreen;
};

#endif