#include "map.h"
#include "asteroid.h"
#include "block.h"

/// @brief MAP FUNCTIONS
Map::Map() : map(sf::VideoMode(600,600), "Astral Arena"){
    border.setSize({590,590});
    border.setPosition(5,5);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::Red);
    border.setOutlineThickness(5);
}

sf::RenderWindow& Map::getWindow() {
    return map;
}

void Map::run() {

    std::vector<Asteroid> asteroids;
    for (int i = 0; i < 5; ++i) {
        Asteroid asteroid(map); 
        asteroid.setColor(sf::Color::White);
        asteroid.setSize(20);
        asteroids.push_back(asteroid);
    }
    asteroids[0].setPosition({50.f, 50.f});
    asteroids[1].setPosition({550.f, 50.f});
    asteroids[2].setPosition({50.f, 550.f});
    asteroids[3].setPosition({550.f, 550.f});
    asteroids[4].setPosition({300.f, 300.f});

    std::vector<Block> blocks;

    // Add destructible and indestructible blocks
    for (int i = 0; i < 4; ++i) {
        Block destructibleBlock({60.f, 60.f}, sf::Color::Yellow, true);
        blocks.push_back(destructibleBlock);

        Block indestructibleBlock({100.f, 100.f}, sf::Color::Blue, false);
        blocks.push_back(indestructibleBlock);
    }
    //non destructable
    blocks[1].setPosition({5.f, 250.f});
    blocks[3].setPosition({250.f, 5.f});
    blocks[5].setPosition({250.f, 495.f});
    blocks[7].setPosition({495.f, 250.f});

    //destructable
    blocks[0].setPosition({270.f, 100.f});
    blocks[2].setPosition({270.f, 160.f});
    blocks[4].setPosition({270.f, 375.f});
    blocks[6].setPosition({270.f, 435.f});


    sf::Event event;
    sf::Clock clock;
    while (map.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (map.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                map.close();
        }

        for (auto& asteroid : asteroids) {
            asteroid.update(dt);
        }


        for (size_t i = 0; i < asteroids.size(); ++i) {
            for (size_t j = i + 1; j < asteroids.size(); ++j) {
                if (asteroids[i].isTouchingAsteroid(asteroids[j])) {
                    sf::Vector2f dir = asteroids[i].getPosition() - asteroids[j].getPosition();
                
                    if (std::abs(dir.x) > std::abs(dir.y)) {
                        asteroids[i].reverseDirectionX();
                        asteroids[j].reverseDirectionX();
                    } else {
                        asteroids[i].reverseDirectionY();
                        asteroids[j].reverseDirectionY();
                    }
                
                    // Push apart
                    float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                    if (dist == 0) dist = 1; // Avoid division by zero
                
                    sf::Vector2f offset = dir / dist * (asteroids[i].getRadius() + asteroids[j].getRadius() - dist) / 2.f;
                    asteroids[i].setPosition(asteroids[i].getPosition() + offset);
                    asteroids[j].setPosition(asteroids[j].getPosition() - offset);
                }
            }
        }

        for (auto& asteroid : asteroids) {
            for (auto& block : blocks) {
                if (block.isDestroyed()) {
                    continue;
                }
        
                sf::Vector2f asteroidPos = asteroid.getPosition();
                float radius = asteroid.getRadius();
                sf::FloatRect asteroidBounds(asteroidPos.x, asteroidPos.y, radius * 2, radius * 2);
        
                sf::FloatRect blockBounds = block.getGlobalBounds();
        
                if (asteroidBounds.intersects(blockBounds)) {
                    
                    asteroid.bounceOff(blockBounds);
        
                    // if (block.isDestructible()) {
                    //     block.destroy();
                    // }
                }
            }
        }
        
        map.clear();
        map.draw(border);
        for (const auto& asteroid : asteroids) {
            map.draw(asteroid);
        }
        for (const auto& block : blocks) {
            map.draw(block);
        }
        map.display();
    }
}