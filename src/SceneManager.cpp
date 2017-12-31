// SceneManager.cpp
// Implementation of SceneManager.
// Created on November 30, 2017
// Last modified on December 17, 2017

#include "SceneManager.h"

void SceneManager::ChangeScene(int scene)
{
    switch(scene)
    {
    case SceneManager::SPLASHSCREEN:
    {
        SplashScreen* s = new SplashScreen(0, 0, 1024, 576, 4, Game::_renderer);
        s->_texture->LoadTexture("../assets/graphics/polygonwhale.png");
        break;
    }

    case SceneManager::MENU:
    {   
        SDL_SetRenderDrawColor(Game::_renderer, 0xFF, 0xFF, 0x00, 0xFF);
        Menu m = Menu();
        break;
    }

    case SceneManager::SETUP:
    {
        break;
    }

    case SceneManager::GAME:
    {
        Ship* ship = new Ship(2, Game::_renderer);
        ship->_texture->LoadTexture("../assets/graphics/spaceship.png");

        break;
    }

    case SceneManager::EXIT:
    {
        Game::_quit = true;
        break;
    }
    }
    

    return;
}