// Texture.h
// Created by Tommy Janna
// Class name: Texture
// Description of class: Texture wrapper class for SDL_Textures.
//                       This class extends the functionality of SDL_Textures
//                       with methods to easily access properties,
//                       blend/fade in or out, and render.
// Created on October 20, 2017
// Last modified on October 20, 2017

#ifndef TEXTURE_H
#define TEXTURE_H

#include "GameObject.h"
#include "Game.h"
#include <SDL_image.h>
#include <SDL.h>
#include <string>


class Texture
{
public:
    
    Texture();
    Texture(SDL_Renderer*);
    ~Texture();

    void LoadTexture(std::string);

    int GetWidth() { return _width; }
    int GetHeight() { return _height; }
    int GetOpacity() { return _opacity; }

    void Render(int x, int y);

    void FreeTexture();

    void Fade();

private:

    SDL_Texture* _texture;
    SDL_Renderer* _renderer;

    int _width, _height;

    int _opacity;
};

#endif