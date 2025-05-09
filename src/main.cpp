/**
 * @file main.cpp
 * @author Caleb Blondell, Justin Keiner, Will Hall 
 * @brief Entry point for Astral Arena.
 *
 * Handles the main event loop for the game’s front-end. Manages menu input,
 * transitions between menus and subsystems (map, credits), and keeps the
 * ESC-hold logic responsive. Uses SFML for window and event handling.
 * 
 * @date 2025-04-30
 * 
 */
#include <SFML/Graphics.hpp>
#include "GameRun.hpp"
#include "menu.h"
#include "submenu/deadmenu.h"
#include "submenu/creditsmenu.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Astral Arena - Menu");
    window.setFramerateLimit(60);

    Menu menu(800, 600);  // You'll implement this
    bool runningMenu = true;
    sf::Clock startupDelayClock;
    // Wait for 2 seconds before showing the menu

    while (window.isOpen() && runningMenu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    menu.moveUp();
                else if (event.key.code == sf::Keyboard::Down)
                    menu.moveDown();
                else if (event.key.code == sf::Keyboard::Left && menu.getSelectedIndex() == 3) {
                    menu.decrementMatchCount();
                }
                else if (event.key.code == sf::Keyboard::Right && menu.getSelectedIndex() == 3) {
                    menu.incrementMatchCount();
                }
                else if ((event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                    && menu.getSelectedIndex() == 4) {
                    menu.toggleSound();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    menu.playSelectSound();
                    int selected = menu.getSelectedIndex();
                
                    if (selected == 0) {   // Start Game
                        menu.playSelectSound();
                        window.close();
                        GameRun();
                        runningMenu = false;
                    } else if (selected == 1 || selected == 2) { // Select Ship or Select Map
                        DeadMenu dead(800, 600);
                        dead.run(window);
                    }else if (selected == 5) {  // Credits
                        CreditsMenu credits(800, 600);
                        credits.run(window);
                    }
                    else if (selected == 6) {  // Exit
                        window.close();
                    }
                }
            }
        }
        // Protect against false ESC detection right after launch
        if (startupDelayClock.getElapsedTime().asSeconds() > 0.5f) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                menu.startEscHold();
                if (menu.isEscHeldLongEnough(2.0f)) {
                    window.close();
                }
            } else {
                menu.cancelEscHold();
            }
        }

        window.clear(sf::Color(20, 20, 40)); // Dark navy background
        menu.draw(window);
        window.display();
    }

    return 0;
}