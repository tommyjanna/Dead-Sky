// Enemy.h
// Created by Tommy Janna
// Class name: Enemy
// Description of class: Enemy ship which contains,
//                       all information about the enemy's,
//                       ship. Conducts battles with the 
//                       player.
// Created on January 11, 2018
// Last modified on January 11, 2018

#ifndef ENEMY_H
#define ENEMY_H

#include "Ship.h"
#include "Blank.h"
#include "../GameObject.h"

class Ship;

class Enemy : public GameObject
{
public:
    Enemy(int layer, SDL_Renderer* renderer, int health, int shield);
    ~Enemy();

    void Update() override;
    void Draw() override;
    void Destroy() override;

    void Attack(Ship*);

    int _health, _shield;

private:

    Blank* _healthDisplay;
    Blank* _shieldDisplay;

    Blank* _healthText;
    Blank* _shieldText;
};

#endif