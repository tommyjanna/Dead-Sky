// Enemy.cpp
// Implementation of the Enemy class.
// Created on January 11, 2018
// Last modified on January 11, 2018

#include "Enemy.h"

Enemy::Enemy(int layer, SDL_Renderer* renderer, int health, int shield, int damage, int credits, int location) : GameObject(492, 140, 600, 300, layer, renderer, "Enemy")
{
    _health = health;
    _shield = shield;
    _damage = damage;
    _credits = credits;
    _location = location;

    _healthText = new Blank(renderer, 885, 25, 1, 1, 4, 40, " ");
    _shieldText = new Blank(renderer, 885, 500, 1, 1, 4, 40, " ");

    // Background image that houses stats text.
    _healthDisplay = new Blank(renderer, 880, 20, 144, 60, 3);
    _shieldDisplay = new Blank(renderer, 880, 496, 144, 60, 3);

    _healthDisplay->_texture->LoadTexture("../assets/graphics/hpenemy.png");
    _shieldDisplay->_texture->LoadTexture("../assets/graphics/shenemy.png");
    
    return;
}

Enemy::~Enemy()
{
    _healthDisplay->_toBeDestroyed = true;
    _shieldDisplay->_toBeDestroyed = true;
    _healthText->_toBeDestroyed = true;
    _shieldText->_toBeDestroyed = true;
    return;
}

void Enemy::Update()
{
    _healthText->_texture->LoadRenderedText(std::to_string(_health), SDL_Color { 0x00, 0x00, 0x00 });
    _shieldText->_texture->LoadRenderedText(std::to_string(_shield), SDL_Color { 0x00, 0x00, 0x00 });

    return;
}

void Enemy::Draw()
{
    _texture->Render();
    return;
}

void Enemy::Destroy()
{
    return;
}

void Enemy::Attack(Ship* ship)
{
    // Default battle log.
    std::string battleLog = "Enemy turn:\n";
    int spilloverDamage;

    // Generate random number between 0 and 3 to determine if the enemy will fire,
    // their missiles.
    int useMissiles = rand() % 4;

    if(_health <= 0) // Skip battle sequence if health is 0.
    {
        _health = 0; // Set to 0 just in case number is in the negatives.
        ship->si.DisplayPanel("You defeated the enemy!\n\nYou plunder their ship and discover " + std::to_string(_credits) +
                                " trade credits!");

        // Plunder enemy's credits.
        ship->_credits += _credits;
    }

    else
    {
        // Only use shield penetration missiles 2 in every 3.
        if(useMissiles != 3)
        {
            // Shield penetration missiles.
            if(ship->_shield > 0) // Double damage, because missiles hit shield.
            {
                battleLog.append("The enemy dealt " + std::to_string(_damage) + " damage, but it was DOUBLED to " +
                    std::to_string(_damage * 2) + " because they hit the shield with your shield penetration missiles!\n\n");

                if(ship->_shield < _damage * 2)
                {
                    ship->_shield = 0;
                }

                else
                {
                    ship->_shield -= _damage * 2;
                }
            }

            else // Half the damage, because missiles hit hull.
            {
                if(ship->_health < _damage / 2)
                {
                    ship->_health = 0;
                }

                else
                {
                    ship->_health -= _damage / 2;
                }

                battleLog.append("The enemy dealt " + std::to_string(_damage) + " damage, but it was HALVED to " +
                    std::to_string(_damage / 2) + " because they didn't hit any shield with their shield penetration missiles!\n\n");
            }
        }

        // Regular blasters.
        if(ship->_shield > 0) // Half the damage because blasters hit the shield.
        {
            battleLog.append("The enemy dealt " + std::to_string(_damage) + " damage, but it was HALVED to " +
                        std::to_string(_damage / 2) + " because they hit the shield with their regular blasters!\n\n");

            if(ship->_shield < _damage / 2) // If damage should do more damage than the enemy's shield.
            {
                spilloverDamage = (_damage / 2) - ship->_shield;

                ship->_shield = 0;
                ship->_health -= spilloverDamage;
            }

            else
            {
                ship->_shield -= _damage / 2;
            }
        }

        else // Regular damage, because blasters hit the hull
        {
            if(ship->_health < _damage)
            {
                ship->_health = 0;
            }

            else
            {
                ship->_health -= _damage;
            }

            battleLog.append("The enemy dealt " + std::to_string(_damage) + " damage with their regular blasters!\n\n");
        }

        // Display all enemy actions.
        ship->si.BattleLog(battleLog, true, ship, this);
    }
    return;
}