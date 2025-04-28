/**
 * @file main.cpp
 * @author Caleb Blondell (crblondell@students.nic.edu) 
 * @brief 
 * @version 0.1
 * @date 2025-03-25
 * 
 * 
 */

#include "GameManager.hpp"
#include "Polygon.hpp"
#include "Timer.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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

    Timer* timer = new Timer();  // Create a Timer object

    // Add the timer to the game manager
    gameManager.addObject(timer, true); // Add it as a dynamic object

    // Create a polygon to test
    std::vector<sf::Vector2f> points = {
        {400, 200},
        {300, 250},  
        {350, 350},
        {300, 400},
        {200, 450},  
        {250, 550},
        {350, 500},  
        {400, 450},
        {450, 400},
        {500, 350},
        {460, 300},
        {400, 250},
        {430, 200}   
    };

    Polygon polygon(points);  // Create a polygon with the points
    polygon.setOutlineColor(sf::Color::Magenta);  // Set its outline color
    polygon.setOutlineThickness(2.f);  // Set the thickness
    gameManager.addObject(&polygon, false); // Add it as a dynamic object

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

        // Update game logic
        gameManager.update(dt);
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        if (polygon.contains(worldPos)) {
            polygon.setOutlineColor(sf::Color::White);
        } else {
            polygon.setOutlineColor(sf::Color::Magenta);
        }
        // Draw everything
        window.clear();
        gameManager.draw(window);
        window.display();
    }

    std::cout << "Game loop exited." << std::endl;
    return 0;
}

