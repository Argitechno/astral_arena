/**
 * @file main.cpp
 * @author Caleb Blondell (crblondell@students.nic.edu) 
 * @brief 
 * @version 0.1
 * @date 2025-03-25
 * 
 * 
 */

#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Astral Arena");
    window.setFramerateLimit(60);

    // Create game manager
    GameManager gameManager;

    // Clock for delta time
    sf::Clock clock;

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate delta time
        float dt = clock.restart().asSeconds();

        // Update game logic
        gameManager.update(dt);

        // Draw everything
        window.clear();
        gameManager.draw(window);
        window.display();
    }

    return 0;
}
