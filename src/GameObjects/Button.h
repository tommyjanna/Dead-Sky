// Button.h
// Created by Tommy Janna
// Class name: Button
// Description of class: It's a button.
// Created on November 30, 2017
// Last modified on November 30, 2017

#ifndef BUTTON_H
#define BUTTON_H

#include "../GameObject.h"
#include "../Game.h"
#include <functional>

class Button : public GameObject
{
public:
    Button(SDL_Renderer* renderer, int x, int y, int width, int height, std::function<void()> const& event);
    Button(SDL_Renderer*, int x, int y, int width, int height, int fontSize, std::string, std::function<void()> const& event);
    ~Button();

    void Update() override;
    void Draw() override;
    void Destroy() override;

private:

    int _buttonWidth, _buttonHeight;
    int _x, _y;

    bool _down;

    std::function<void()> _event;
};

#endif