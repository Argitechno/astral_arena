#include "GameManager.hpp"
#include "Polygon.hpp"
#include "PolygonOutline.hpp"
#include "Timer.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cmath>
 
int main() {
    std::cout << "Initializing window..." << std::endl;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Astral Arena");

    if (!window.isOpen()) {
        std::cerr << "Failed to open window!" << std::endl;
        return -1;
    }

    std::cout << "Window created successfully!" << std::endl;
    window.setFramerateLimit(60);

    std::vector<sf::Vector2f> points = {
        {  0.f,   0.f },
        { 15.f,  40.f },
        { 10.f,  50.f },
        { -10.f, 50.f },
        { -15.f, 40.f }
    };

    Polygon polygon1(points, {300.f, 200.f});
    Polygon polygon2(points, {600.f, 300.f});
    Polygon polygon3(points, {500.f, 500.f});

    PolygonOutline outline1(polygon1);
    PolygonOutline outline2(polygon2);
    PolygonOutline outline3(polygon3);

    outline1.setColor(sf::Color::Green);
    outline2.setColor(sf::Color::Green);
    outline3.setColor(sf::Color::Green);

    sf::RectangleShape bounds1, bounds2, bounds3;
    sf::CircleShape centroid1(3.f), centroid2(3.f), centroid3(3.f);
    centroid1.setOrigin(3.f, 3.f);
    centroid2.setOrigin(3.f, 3.f);
    centroid3.setOrigin(3.f, 3.f);
    centroid1.setFillColor(sf::Color::Blue);
    centroid2.setFillColor(sf::Color::Blue);
    centroid3.setFillColor(sf::Color::Blue);

    sf::Clock clock;

    std::cout << "Entering main game loop..." << std::endl;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                std::cout << "Window closed by user." << std::endl;
                window.close();
            }
        }

        // Update bounds and centroids
        auto updateBounds = [](Polygon& p, sf::RectangleShape& r) {
            sf::FloatRect b = p.getBounds();
            r.setPosition(b.left, b.top);
            r.setSize({b.width, b.height});
            r.setFillColor(sf::Color::Transparent);
            r.setOutlineColor(sf::Color::Red);
            r.setOutlineThickness(1.f);
        };

        updateBounds(polygon1, bounds1);
        updateBounds(polygon2, bounds2);
        updateBounds(polygon3, bounds3);

        centroid1.setPosition(polygon1.getCentroid());
        centroid2.setPosition(polygon2.getCentroid());
        centroid3.setPosition(polygon3.getCentroid());

        // Controls for polygon1
        sf::Vector2f positionDelta(0.f, 0.f);
        float rotationDelta = 0.f;
        float scaleDelta = 1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) positionDelta.y -= 2.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) positionDelta.y += 2.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) positionDelta.x -= 2.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) positionDelta.x += 2.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) rotationDelta -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) rotationDelta += 1.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) scaleDelta = 0.99f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) scaleDelta = 1.01f;

        polygon1.move(positionDelta);
        polygon1.rotate(rotationDelta);
        polygon1.scale(scaleDelta, scaleDelta);

        sf::Vector2f mouseWorld = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::CircleShape mouseDot(3.f);
        mouseDot.setFillColor(sf::Color::Red);
        mouseDot.setOrigin(3.f, 3.f);
        mouseDot.setPosition(mouseWorld);

        if (polygon1.contains(mouseWorld)) {
            outline1.setColor(sf::Color::Blue);
        } else {
            outline1.setColor(sf::Color::Green);
        }

        // Update outlines
        outline1.update();
        outline2.update();
        outline3.update();

        // Check collisions
        if (polygon1.intersects(polygon2)) {
            outline1.setColor(sf::Color::Yellow);
            outline2.setColor(sf::Color::Yellow);
        }

        if (polygon1.intersects(polygon3)) {
            outline1.setColor(sf::Color::Magenta);
            outline3.setColor(sf::Color::Magenta);
        }

        window.clear(sf::Color::Black);
        window.draw(mouseDot);

        window.draw(outline1);
        window.draw(outline2);
        window.draw(outline3);

        window.draw(bounds1);
        window.draw(bounds2);
        window.draw(bounds3);

        window.draw(centroid1);
        window.draw(centroid2);
        window.draw(centroid3);

        window.display();
    }

    std::cout << "Game loop exited." << std::endl;
    return 0;
}
