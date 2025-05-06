#include <SFML/Graphics.hpp>
#include "map.h"
#include "menu.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Astral Arena - Menu");
    window.setFramerateLimit(60);

    Menu menu(800, 600);  // You'll implement this
    bool runningMenu = true;

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
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selected = menu.getSelectedIndex();
                    if (selected == 0) {  // Start Game
                        window.close();  // Close the menu window
                        Map map;         // Launch map
                        map.run();
                        runningMenu = false;
                    }
                    if (selected == 4) {  // Exit
                        window.close();
                    }
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}
