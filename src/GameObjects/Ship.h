// Ship.h
// Created by Tommy Janna
// Class name: Ship
// Description of class: Space ship which contains,
//                       all information about the player's,
//                       crew members and resources. This,
//                       also displays the ship and interacts in space,
//                       combat.
// Created on December 18, 2017
// Last modified on December 18, 2017

#ifndef SHIP_H
#define SHIP_H

#include "Enemy.h"
#include "Line.h"
#include "Button.h"
#include "Blank.h"
#include "../Event.h"
#include "../GameObject.h"
#include <functional>
#include <ctime>
#include <cmath>

class Button;
class ShipInterface;
class Enemy;

class Ship : public GameObject
{
public:
    Ship(int layer, SDL_Renderer* renderer);
    ~Ship();

    void Update() override;
    void Draw() override;
    void Destroy() override;
    
    void Attack(Enemy*);

    int _shieldPenPts;
    int _blasterPts;
    int _shieldPts;

    // This class handles UI elements for the ship.
    class ShipInterface
    {
    public:
        ShipInterface(); // Default constructor cuz this damn compiler wants one. DONT DELETE
        ShipInterface(SDL_Renderer* renderer, Ship* parentShip);

        void Update();
        void Destroy();

        void DisplayPanel(std::string text); // Single text panel.
        int DisplayPanel(std::string text, std::vector<std::string> answers, int panelNum); // A panel with multiple answers.
        void CombatPanel(Enemy* enemy); // Assigning points in combat.
        void BattleLog(std::string message, bool myTurn, Ship* ship, Enemy* enemy); // Displays actions perfromed.
        void CreateMap();
        void Shop();

        void DrawMapLines();
        void DeleteMapLines();
        void DeleteButtons(std::vector<Button*> buttonVector);

        int LocateShip();
        int _location;

    private:

        int Distance(int x1, int y1, int x2, int y2);
        void ModPoints(Button* b);

        Ship* _parentShip;

        SDL_Renderer* _renderer;
        Blank* _panel;
        Blank* _panelText;

        Blank* _combatPanel;
        Blank* _energyText;
        Blank* _blasterPoints;
        Blank* _shieldPenPoints;
        Blank* _shieldPoints;

        Button* _fire;

        Blank* _mapPanel;
        Blank* _locationNode;

        Blank* _healthDisplay;
        Blank* _shieldDisplay;
        Blank* _statusBar;

        Blank* _healthText;
        Blank* _shieldText;
        Blank* _damageText;
        Blank* _membersText;
        Blank* _creditsText;

        Button* _continueButton;
        
        Button* _spaceMap;
        Button* _closeMap;

        bool _shopOwned[4];
        int _shopPrices[4];

        int _mapNodes[13][2];
        int _mapPosX, _mapPosY;

        std::vector<Button*> _mapButtons;
        std::vector<Button*> _answers;
        std::vector<Button*> _combatButtons;
        std::vector<Button*> _shopButtons;
        std::vector<std::string> _loseOptions;
        std::vector<Button*> _continueButtons;
        Line* _lines;
    };

    ShipInterface si;

    int _health, _shield;
    int _credits, _damage, _members, _energy, _shieldRegen;

private:
};

#endif