#include "GameManager.hpp"
#include "Polygon.hpp"
#include "PolygonOutline.hpp"
#include "Timer.hpp"
#include "Spaceship.hpp"
#include "DebugDrawer.hpp"
#include "VectorUtils.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cmath>



int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Spaceship Test");

    Polygon shape;
    shape.addPoint({30.f, 10.f});
    shape.addPoint({15.f, 45.f});
    shape.addPoint({45.f, 45.f});

    Spaceship ship1(shape, 0.f, 90.f);
    ship1.setColor(sf::Color::Cyan);
    ship1.setPosition({200.f, 300.f});

    Spaceship ship2(shape, -90.f, 90.f, {600.f, 300.f});
    ship2.setColor(sf::Color::Red);

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Ship 1 (WASD)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            ship1.applyThrust();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            ship1.applyTorque(false); // Left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            ship1.applyTorque(true); // Right

        // --- Ship 2 (Arrow Keys)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            ship2.applyThrust();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            ship2.applyTorque(false); // Left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            ship2.applyTorque(true); // Right

        std::cout << "Ship1 Current Speed = " << Vec2::length(ship1.getVelocity()) << '\n';

        // Update logic
        ship1.update(dt);
        ship2.update(dt);

        // Draw
        window.clear();
        window.draw(ship1);
        window.draw(ship2);
        window.display();
    }

    return 0;
}
