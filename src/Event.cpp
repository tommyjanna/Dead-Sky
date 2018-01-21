// Event.cpp
// Implementation of the Event file.
// Created on January 2, 2018
// Last modified on January 2, 2018

#include "Event.h"

namespace Event
{
    void UpdateEvent(Ship* ship, int panelNumber, int choice)
    {
        std::vector<std::string> answers; // Vector for passing possible answers.

        // Destroy existing enemy ships.
        if(currentEnemy != NULL)
        {
            if(currentEnemy->_location != ship->si._location)
            {
                currentEnemy->_toBeDestroyed = true;
                currentEnemy = NULL;
            }
        }

        // If location hasn't been visited or new panel or shop location, run event.
        if(!visited[ship->si._location] || panelNumber > 1 || ship->si._location == 5)
        {
            switch(ship->si._location)
            {
            case 0:
                if(panelNumber == 1)
                {
                    ship->si.DisplayPanel("You are the captain of an infamous raider mob. You and your marauder crew "
                                "were hired by the newly formed rebel alliance to thieve vital information "
                                "on the Janerian Empire's mothership. The Janerian Empire led under their Lord, "
                                "Emperor Tommy Janna the Great, have been tyranizing the star citizens of this "
                                "galaxy for decades!\n\nYour crew successfully obtained the intel "
                                "and your payment from the rebel camp will be wired once you return it to the rebel "
                                "base on Earth-5. The empire tagged your ship with a tracker as you were escaping "
                                "and they have a probe in pursuit!\n\nYour shields were damaged while escaping the "
                                "Janerian's and the enemies are hot on your trail. You should open your space map "
                                "and head to the next space sector.");
                }
                break;
            case 1:
                if(panelNumber == 1)
                {
                    answers.push_back(">: Fly towards the origin of the distress beacon.");
                    answers.push_back(">: Ignore the signal, I have enough on my plate right now.");

                    ship->si.DisplayPanel("Your ship is picking up an incoming signal from a nearby planet in the sector.\n\n"
                                    "The radio is picking up a lot of static, but you're able to make out a few words:\n"
                                    "       ...help us...stuck...circumstances...\n"
                                    "       ...bZ..bloop...dyingggg...wzzzzZZ....", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    if(choice == 0)
                    {
                        answers.push_back(">: Continue");

                        ship->si.DisplayPanel("You fly cautiously toward the planet where the signal originates.\n\n"
                                        "As the captain, you and another crew member, Cornelius, go down to the planet. "
                                        "On the planet you encounter a small village with humanoid dolphins living "
                                        "in huts built with metal debris.\n\nTheir leader informs you of the destruction "
                                        "of their city while Cornelius wanders off into "
                                        "the desolate planet.\n\nDuring your conversation with the leader, you hear "
                                        "a terrified yelp from outside the hut.", answers, 3);
                    }
                }

                else if(panelNumber == 3)
                {
                    answers.push_back(">: I'll leave, we'll return to save you Cornelius, I promise.");
                    answers.push_back(">: Grab your concealed weapon and fight the natives!!");

                    ship->si.DisplayPanel("You rush out of the hut to see the natives mercilessly beating Cornelius "
                                        "on the ground! You try to intervene, but the leader emerges from the tent pointing "
                                        "a gun at you.\n\n\"TAKE ANOTHER STEP AND YOU BOTH DIE!\"\n\n The leader escorts you "
                                        "back to your ship, and allows you and the rest of your crew to leave in peace, in "
                                        "exchange for Cornelius to work as a slave.", answers, 4);
                }

                else if(panelNumber == 4)
                {
                    if(choice == 0)
                    {
                        ship->si.DisplayPanel("You quickly leave the planet.\n\nYou lost a crew member. (-1 energy in combat)");
                    }

                    if(choice == 1)
                    {
                        ship->si.DisplayPanel("You pull out your gun from your leather jacket!\n\n"
                                "Unfortunately, the leader was intently prepared for such an event and shoots "
                                "you in the arm. You quickly hop aboard your ship and escape while all the natives"
                                "fire at your ship with their blasters.\n\n"
                                "You lost a crew member (-1 energy in combat) and your ship took 20 HP in damage.");
                        
                        ship->_health -= 20;
                    }

                    ship->_members--;
                }
                break;

            case 2:
                ship->si.DisplayPanel("You find a floating sack sitting in the distance. You fetch it with your "
                                    "ship's arm and open it.\n\nAww sweet, you found 50 trade credits!"
                                    "(Redeemable at any participating Galacic Trade Market)");
                
                ship->_credits += 50;
                break;
            
            case 3:
                if(panelNumber == 1)
                {
                    currentEnemy = new Enemy(2, Game::_renderer, 40, 20, 10, 30, ship->si._location);
                    currentEnemy->_texture->LoadTexture("../assets/graphics/enemyship.png");

                    answers.push_back(">: Loyalty tax my ass! Bite me.");
                    answers.push_back(">: Of course, we don't want to cause any trouble. Please take our " 
                                        + std::to_string(ship->_credits) + " credits.");

                    ship->si.DisplayPanel("An incoming ship slows to a halt, and a video transmission "
                                        "of a group of Klingons sitting around their ship's dashboard is "
                                        "patched through to your main systems monitor. The "
                                        "one in the front speaks first:\n\n"
                                        "\"We are on a diplomatic mission on behalf of the Empire "
                                        "and we ask that you forfeit all your trade credits as a loyalty tax "
                                        "to the Emporor.\"", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    if(choice == 0)
                    {
                        answers.push_back("Battle!");

                        ship->si.DisplayPanel("\"Then you shall feel the full wrath of the EMPIRE!!!\"", answers, 3);
                    }

                    else if(choice == 1)
                    {
                        ship->si.DisplayPanel("\"Thanks for your compliance.\"\n\nYou lost "
                                + std::to_string(ship->_credits) + " credits.");

                        ship->_credits = 0;
                    }
                }

                else if(panelNumber == 3)
                {
                    ship->si.CombatPanel(currentEnemy);
                }
                break;
            
            case 4:
                ship->si.DisplayPanel("This area seems to be empty... Best move onto the next sector.");
                break;
            
            case 5:
                ship->si.Shop();
                break;

            case 6:
                if(panelNumber == 1)
                {
                    answers.push_back(">: Proceed stealthly through the stardust.");
                    answers.push_back(">: Suck all the dust using your space vacuum, but revealing your location.");

                    ship->si.DisplayPanel("You enter a sector filled with stardust from a recent death "
                                    "of a star. On your radio, you pick up broken sentances from hostile Empire "
                                    "ships!\n\nYou must proceed through the sector but if the Empire spots you "
                                    "the intel will be confiscated and your crew will be tried under the full extent of space law!", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    if(choice == 0)
                    {
                        ship->si.DisplayPanel("You succesfully navigated the stardust without getting "
                                            "spotted by the Empire. You can now warp to the next sector.");
                    }

                    else if(choice == 1)
                    {
                        answers.push_back("Battle!");

                        ship->si.DisplayPanel("As you're sucking up the dust, you were spotted by one of the Empire "
                                            "ships and they recognized your ship as fugitives from the Empire.\n\n"
                                            "\"SURRENDER NOW REBEL SCUM!\"", answers, 3);
                    }
                }

                else if(panelNumber == 3)
                {
                    currentEnemy = new Enemy(2, Game::_renderer, 80, 40, 15, 45, ship->si._location);
                    currentEnemy->_texture->LoadTexture("../assets/graphics/enemyship.png");

                    ship->si.CombatPanel(currentEnemy);
                }
                break;

            case 7:
                ship->si.DisplayPanel("An eerie silence deepens on the ship as you pull into the sector. "
                                "It's a little too calm for comfort. The radar shows no ships in the area. "
                                "\n\nNo answers present themselves so you must move onto the next sector.");
                break;

            case 8:
                if(panelNumber == 1)
                {
                    answers.push_back(">: Engage back thrusters to full blast and try to pull away.");
                    answers.push_back(">: Engage side thrusters and try to burn the creature.");
                    answers.push_back(">: Target all weapons on the creature's eyes.");

                    ship->si.DisplayPanel("The same silence presents itself as you warp into the sector. " 
                                "Suddenly, a giant tentacle reaches out from the depths of space and grabs "
                                "a hold of your ship. The suction cups latch to your hull and begins "
                                "to pull you toward a desolate planet far below. Your crew beings to panic.", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    if(choice == 0)
                    {
                        ship->si.DisplayPanel("You manage to pull free from the grip of death itself. " 
                                        "In the process a piece of hull is ripped off.\n\n"
                                        "Your ship took 20 HP in damage.");

                        ship->_health -= 20;
                    }

                    else if(choice == 1)
                    {
                        ship->si.DisplayPanel("The burn of the thrusters causes the tentacle to lash back. "
                                            "You instantly engage back thursters now to escape while the creature "
                                            "is dazed, but as you are accelerating, the tentacle knocks your ship "
                                            "with a hard blow! Fortunately the suction cups weren't able to latch "
                                            "on and you escaped with hefty damage to you hull.\n\n"
                                            "Your ship took 45 HP in damage.");

                        ship->_health -= 45;
                    }

                    else if(choice == 2)
                    {
                        ship->si.DisplayPanel("You launch all defenses against the creature's eyes!\n\n"
                                            "Direct shots! The arm unlatches from your ship and your ship is "
                                            "freed from the clutches of death itself.\n\nQuickly, you engage your "
                                            "back thrusters and speed off into the space ahead.");
                    }
                }
                break;

            case 9:
                if(panelNumber == 1)
                {
                    answers.push_back(">: Enter the field, we must search that escape pod!");
                    answers.push_back(">: Leave it, I don't have time for this.");
                    ship->si.DisplayPanel("You enter the sector and stop on the border of an asteroid field. "
                                        "You look deeply at the floating rocks. Suddenly you notice a small "
                                        "escape pod floating on its own out in the field.\n\nYour ship is relatively "
                                        "large and entering the field may cause damages to your ship.", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    if(choice == 0)
                    {
                        ship->si.DisplayPanel("You enter the asteroid field and your hull takes a few nasty dents. "
                                            "Once you reach the pod, you pull it onto your ship using ship's arm. "
                                            "On board, you find an unconcious young rebel pilot, as read a crest "
                                            "on his jacket. His heart is still beating, so you leave him to rest up "
                                            "on your ship.\n\nOnce the young human wakes up he explains how he got "
                                            "seperated from the rebels after their ship was invaded, so he escaped on "
                                            "this pod. He agrees to help you carry the inteligence to the rebel base!"
                                            "\n\nYou gained a crew member (+1 energy in combat) and your ship took 5 HP "
                                            " in damage from the asteroids.");
                        
                        ship->_health -= 5;
                        ship->_members++;
                    }
                }
                break;

            case 10:

                if(panelNumber == 1)
                {
                    answers.push_back(">: Pfft, I can handle anything.");
                    answers.push_back(">: Thank you for the warning, but we must proceed to save the Galaxy.");
                    ship->si.DisplayPanel("You encounter a large cargo ship, and a video transmission is "
                                        "patched through to your monitor. The crew of Romulan traders say:\n\n"
                                        "\"We are out here seeking conducting business and we noticed a large "
                                        "Empire ship ahead in the next sector. We implore you to tread lightly, those "
                                        "ship's are not deployed on your average day. Be careful out there traveler.\"");
                }

                else if(panelNumber == 2)
                {
                    if(choice == 0)
                    {
                        ship->si.DisplayPanel("\"For your sake, I hope this is true.\"");
                    }

                    else if(choice == 1)
                    {
                        ship->si.DisplayPanel("\"Good luck with your adventures, wherever they may take you.\"");
                    }
                }
                break;

            case 11:
                if(panelNumber == 1)
                {
                    currentEnemy = new Enemy(2, Game::_renderer, 150, 100, 30, 1000, ship->si._location);
                    currentEnemy->_texture->LoadTexture("../assets/graphics/dreadnought.png");

                    answers.push_back(">: I'd like to see you try.");
                    ship->si.DisplayPanel("An Empire dreadnought awaits your ship.\n\n\"HALT REBEL SCUM, SURRENDER "
                                        "YOURSELVES, OR YOU SHALL BE DESTROYED\"", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    ship->si.CombatPanel(currentEnemy);
                }
                break;

            case 12:
                if(panelNumber == 1)
                {
                    answers.push_back("Exit Game.");

                    ship->si.DisplayPanel("You arrived at the rebel base on Earth-5 and succesfully delivered the intel "
                                        "to the commander! Now the rebels can conduct a succesful attack on the Empire "
                                        "mothership and peace will be restored to the galaxy.\n\nCongratulations!", answers, 2);
                }

                else if(panelNumber == 2)
                {
                    SceneManager::ChangeScene(SceneManager::EXIT);
                }
                break;
            }
        }

        if(panelNumber == 69) // Lost game by losing all health.
        {
            SceneManager::ChangeScene(SceneManager::EXIT);
        }

        // Flag visited current location so when the ship returns, the same event won't run.
        visited[ship->si._location] = true;
    }

    void ResetLocations()
    {
        // Set all locations visited to false.
        for(int i = 0; i < 13; i++)
        {
            visited[i] = false;
        }
    }
}