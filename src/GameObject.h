// GameObject.h
// Created by Tommy Janna
// Class name: GameObject
// Description of class: GameObject class which implements all necessary members for
//                       objects in the game such as position, texture 
//                       and an abstract update function.
// Created on October 24, 2017
// Last modified on October 24, 2017

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Texture.h"
#include <vector>

class GameObject
{
public:

    GameObject();
    GameObject(SDL_Renderer*, std::string);
    virtual ~GameObject();

    virtual void Update() = 0; // (= 0) makes this a pure virtual method, so Update() must be implemented.
    virtual void Draw() = 0;
    virtual void Destroy() = 0;
    void LoadTexture(std::string);

    static std::vector<GameObject*> _objects;

    bool _toBeDestroyed;

    Texture* _texture;

    std::string _name;

private:

};

#endif