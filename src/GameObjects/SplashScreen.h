// SplashScreen.h
// Created by Tommy Janna
// Class name: SplashScreen
// Description of class: A type of GameObject. This class is solely
//                       used to display the splash screen at the
//                       beginning of the game.
// Created on November 8, 2017
// Last modified on November 8, 2017

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "../GameObject.h"

class SplashScreen : public GameObject
{
public:
    SplashScreen(SDL_Renderer*);
    ~SplashScreen();

    void Update() override;
};

#endif
