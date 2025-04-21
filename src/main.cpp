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
#include <SFML/Window.hpp>
#include "GameManager.hpp"
#include <iostream>
 
int main() {
    // Create window
    std::cout << "Initializing window..." << std::endl;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Astral Arena");

    if (!window.isOpen()) {
        std::cerr << "Failed to open window!" << std::endl;
        return -1;
    }

    std::cout << "Window created successfully!" << std::endl;

    window.setFramerateLimit(60);

    // Create game manager
    std::cout << "Initializing game manager..." << std::endl;
    GameManager gameManager;

    std::cout << "Game Manager initialized successfully!" << std::endl;

    // Clock for delta time
    sf::Clock clock;

    // Main game loop
    std::cout << "Entering main game loop..." << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) {
                std::cout << "Window closed by user." << std::endl;
                window.close();
            }
        }

        // Calculate delta time
        float dt = clock.restart().asSeconds();
        std::cout << "Delta time: " << dt << " seconds" << std::endl;

        // Update game logic
        gameManager.update(dt);

        // Draw everything
        window.clear();
        gameManager.draw(window);
        window.display();
    }

    std::cout << "Game loop exited." << std::endl;
    return 0;
}

