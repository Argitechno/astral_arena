#include "ObjectManager.hpp"
#include "Polygon.hpp"
#include "PolygonOutline.hpp"
#include "Timer.hpp"

#include "DebugDrawer.hpp"
#include "VectorUtils.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "map.hpp"


#include <iostream>
#include <cmath>

#include "GameRun.hpp"

void GameRun() {
    bool mIsDone;
    sf::Vector2u baseResolution = {600, 600};
    sf::View view;
    sf::RenderWindow window(sf::VideoMode(baseResolution.x, baseResolution.y), "Astral Arena", sf::Style::Default);
    view.setSize(600, 600);
    view.setCenter(300, 300); // center of base res
    window.setView(view);

    Map map;
    

    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::Resized) {
                float aspectRatio = float(event.size.width) / float(event.size.height);
                if (aspectRatio >= 1.0f) {
                    view.setSize(600 * aspectRatio, 600);
                } else {
                    view.setSize(600, 600 / aspectRatio);
                }
                view.setCenter(300, 300);
                window.setView(view);
            }
        }
        
    
        // Update logic
        map.update(dt);

        // Draw
        window.clear();
        window.draw(map);
        window.display();
    }
}

