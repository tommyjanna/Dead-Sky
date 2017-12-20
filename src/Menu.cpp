// Menu.cpp
// Implementation of the Menu class.
// Created on November 30, 2017
// Last modified on November 30, 2017

#include "Menu.h"

Menu::Menu()
{
    _bg = new Blank(Game::_renderer,
                    0, 0,
                    SCREEN_WIDTH, SCREEN_HEIGHT,
                    1);
    
    _bg->_texture->LoadTexture("../assets/graphics/background.png");

    _title = new Blank(Game::_renderer,
                        SCREEN_WIDTH / 2 - 185, 50,
                        0, 0, 4,
                        60, "DEAD SKY");

    _play = new Button(Game::_renderer, 
                        SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2,
                        88, 37, 4,
                        30, "PLAY", []() { SceneManager::ChangeScene(SceneManager::GAME); });
    
    _exit = new Button(Game::_renderer, 
                        SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 60,
                        88, 37, 4,
                        30, "EXIT", []() { SceneManager::ChangeScene(SceneManager::EXIT); });
}