// Ship.cpp
// Implementation of the Ship class.
// Created on December 18, 2017
// Last modified on December 18, 2017

#include "Ship.h"

Ship::Ship(int layer, SDL_Renderer* renderer) : GameObject(-80, 140, 600, 300, layer, renderer, "Ship")
{
    si = ShipInterface(renderer);

    _health = 100;
    _shield = 0;
    
    si.CreateMap();
    si.DisplayPanel("You and your marauder crew are carrying vital information on the Janerian Empire's "
                "mothership. Your payment from the rebel camp will be wired once you return the intel "
                "to Earth-5. The Janerian's tagged your ship with a tracker and have a probe in pursuit!\n\n"
                "Your shields were damaged while escaping the Janerian space station and the enemies are "
                "hot on your trail.");
}

Ship::~Ship()
{
    return;
}

void Ship::Update()
{
    si.Update(_health, _shield);
    return;
}

void Ship::Draw()
{
    _texture->Render();
    return;
}

void Ship::Destroy()
{
    return;
}

Ship::ShipInterface::ShipInterface()
{
    _renderer = NULL;
}

Ship::ShipInterface::ShipInterface(SDL_Renderer* renderer)
{
    _renderer = renderer;

    _panel = new Blank(_renderer, 200, 80, 640, 420, 3);
    _panel->_texture->LoadTexture("../assets/graphics/panel.png");

    _panelText = new Blank(_renderer, 240, 120, 1, 1, 4, 16, " ");
    _healthText = new Blank(_renderer, 51, 25, 1, 1, 4, 40, " ");
    _shieldText = new Blank(_renderer, 51, 500, 1, 1, 4, 40, " ");

    _healthDisplay = new Blank(_renderer, 0, 20, 144, 60, 3);
    _shieldDisplay = new Blank(_renderer, 0, 496, 144, 60, 3);

    _healthDisplay->_texture->LoadTexture("../assets/graphics/hp.png");
    _shieldDisplay->_texture->LoadTexture("../assets/graphics/sh.png");

    _mapPanel = new Blank(_renderer, 200, 80, 640, 420, 3);
    _mapPanel->_texture->LoadTexture("../assets/graphics/spacemap.png");
    _mapPanel->_show = false;
}

void Ship::ShipInterface::DisplayPanel(std::string message)
{
    SDL_Color textColour = { 0xFF, 0xFF, 0xFF };

    _panelText->_texture->LoadRenderedText(message, textColour);
    _continueButton = new Button(_renderer, 
                                450, 400, 
                                88, 37,
                                4,
                                18, "Continue...",
                                [this]() { _panel->_show = false;
                                                        _panelText->_show = false;
                                                        _continueButton->_show = false;
                                                        _continueButton->_toBeDestroyed = true; }, 
                                false);
}

void Ship::ShipInterface::Update(int health, int shield)
{
    _healthText->_texture->LoadRenderedText(std::to_string(health), SDL_Color { 0x00, 0x00, 0x00 });
    _shieldText->_texture->LoadRenderedText(std::to_string(shield), SDL_Color { 0x00, 0x00, 0x00 });

    return;
}

void Ship::ShipInterface::CreateMap()
{
    int mapNodes[15][2] = { {263, 434},
                            {323, 385},
                            {390, 373},
                            {387, 341},
                            {311, 321},
                            {378, 266},
                            {445, 283},
                            {521, 254},
                            {526, 193},
                            {591, 247},
                            {642, 207},
                            {630, 180},
                            {701, 156},
                            {738, 136},
                            {741, 201} };

    std::copy(&mapNodes[0][0], &mapNodes[15][2], &_mapNodes[0][0]);

    _mapPosX = _mapNodes[0][0];
    _mapPosY = _mapNodes[0][1];

    _spaceMap = new Button(_renderer,
                            450, 500,
                            88, 37,
                            2,
                            24, "Space Map",
                            [this]() { _mapPanel->_show = true;
                                        _closeMap->_show = true; 
                                        _locationNode = new Blank(_renderer, 
                                                                    _mapPosX - 10, _mapPosY - 10,
                                                                    40, 40, 4);
                                        _locationNode->_texture->LoadTexture("../assets/graphics/shipicon.png");
                                        DrawMapLines(); }, false);
    
    _closeMap = new Button(_renderer,
                            230, 107,
                            1, 1,
                            4,
                            "../assets/graphics/close.png",
                            [this]() { _mapPanel->_show = false;
                                        _closeMap->_show = false;
                                        _locationNode->_show = false;
                                        _locationNode->_toBeDestroyed = true;
                                        DeleteMapLines(); }, false);
    _closeMap->_show = false;

    return;
}

void Ship::ShipInterface::DrawMapLines()
{
    int location;

    for(int i = 0; i < 15; i++)
    {
        if(_mapPosX == _mapNodes[i][0])
        {
            location = i;
        }
    }

    for(int i = location - 3; i < location + 3; i++)
    {
        if(i >= 0 && i != location)
        {
            if(Distance(_mapNodes[location][0], _mapNodes[location][1],
                        _mapNodes[i][0], _mapNodes[i][1]) < 100)
            {
                new Line(_renderer, _mapNodes[location][0], _mapNodes[location][1], _mapNodes[i][0], _mapNodes[i][1]);

                Button* b = new Button(_renderer,
                            _mapNodes[i][0], _mapNodes[i][1],
                            25, 25,
                            4,
                            "../assets/graphics/mapnode.png",
                            [this, i](){ 
                                _mapPosX = _mapNodes[i][0];
                                _mapPosY = _mapNodes[i][1];
                                _mapPanel->_show = false;
                                _closeMap->_show = false;
                                _locationNode->_show = false;
                                _locationNode->_toBeDestroyed = true;
                                DeleteMapLines();
                                DeleteMapButtons();
                            }, false);
                _mapButtons.push_back(b);
            }
        }
    }
}

int Ship::ShipInterface::Distance(int x1, int y1, int x2, int y2)
{
    return sqrt((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
}

void Ship::ShipInterface::DeleteMapLines()
{
    for(int i = 0; i < Line::_lines.size(); i++)
    {
        Line::_lines[i]->_toBeDestroyed = true;
    }
}

void Ship::ShipInterface::DeleteMapButtons()
{
    for(int i = 0; i < _mapButtons.size(); i++)
    {
        if(_mapButtons[i] != NULL)
            _mapButtons[i]->_toBeDestroyed = true;
    }
}