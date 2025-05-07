#include "map.hpp"


/// @brief MAP FUNCTIONS
Map::Map()
{
    reset();   
}

void Map::reset()
{
    border.setSize({590,590});
    border.setPosition(5,5);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::Magenta);
    border.setOutlineThickness(5);
    if (!m_sharedTexture.loadFromFile("../assets/images/asteroid.jpg")) {
        std::cerr << "Failed to load texture\n";
    }
    for (int i = 0; i < 4; ++i) {
        m_Asteroids[i].setTexture(&m_sharedTexture);
        addObject(&m_Asteroids[i], false);

        m_Blocks[i * 2].setColor(sf::Color::Yellow);
        m_Blocks[i * 2].setOutline(sf::Color::White);
        m_Blocks[i * 2].setSize({60, 60});
        addObject(&m_Blocks[i * 2], false);

        m_Blocks[i * 2 + 1].setColor(sf::Color::Blue);
        m_Blocks[i * 2 + 1].setOutline(sf::Color::White);
        m_Blocks[i * 2 + 1].setDestructable(false);
        m_Blocks[i * 2 + 1].setSize({100, 100});
        addObject(&m_Blocks[i * 2 + 1], false);
    }

    addObject(&m_Players[0], false);
    addObject(&m_Players[1], false);

    m_Asteroids[0].setPosition({80.f, 80.f});
    m_Asteroids[1].setPosition({525.f, 55.f});
    m_Asteroids[2].setPosition({75.f, 575.f});
    m_Asteroids[3].setPosition({510.f, 530.f});
    //non destructable
    m_Blocks[1].setPosition({10.f, 250.f});
    m_Blocks[3].setPosition({250.f, 10.f});
    m_Blocks[5].setPosition({250.f, 490.f});
    m_Blocks[7].setPosition({490.f, 250.f});

    //destructable
    m_Blocks[0].setPosition({270.f, 120.f});
    m_Blocks[2].setPosition({270.f, 180.f});
    m_Blocks[4].setPosition({270.f, 365.f});
    m_Blocks[6].setPosition({270.f, 425.f});

    m_Players[0].setColor(sf::Color::Cyan);
    m_Players[1].setColor(sf::Color::Red);

    m_Players[0].setPosition({550.f, 550.f});
    m_Players[1].setPosition({200.f, 100.f});
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    ObjectManager::draw(target, states);
    target.draw(border);
}


void Map::userInput()
{
    // --- Player 1 (WASD)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_Players[0].applyThrust();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_Players[0].applyTorque(false); // Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_Players[0].applyTorque(true); // Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_Players[0].shoot(); // Right

    // --- Player 2 (Arrow Keys)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_Players[1].applyThrust();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_Players[1].applyTorque(false); // Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_Players[1].applyTorque(true); // Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_Players[1].shoot(); // Right
}

void Map::update(float deltaTime)
{
    ObjectManager::update(deltaTime);

    userInput();

    for (size_t i = 0; i < m_Asteroids.size(); ++i) {
        for (size_t j = i + 1; j < m_Asteroids.size(); ++j) {
            if (m_Asteroids[i].isTouchingAsteroid(m_Asteroids[j])) {
                sf::Vector2f dir = m_Asteroids[i].getPosition() - m_Asteroids[j].getPosition();
            
                if (std::abs(dir.x) > std::abs(dir.y)) {
                    m_Asteroids[i].reverseDirectionX();
                    m_Asteroids[j].reverseDirectionX();
                } else {
                    m_Asteroids[i].reverseDirectionY();
                    m_Asteroids[j].reverseDirectionY();
                }
            
                // Push apart
                float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                if (dist == 0) dist = 1; // Avoid division by zero
            
                sf::Vector2f offset = dir / dist * (m_Asteroids[i].getRadius() + m_Asteroids[j].getRadius() - dist) / 2.f;
                m_Asteroids[i].setPosition(m_Asteroids[i].getPosition() + offset);
                m_Asteroids[j].setPosition(m_Asteroids[j].getPosition() - offset);
            }
        }
    }

    for (auto& asteroid : m_Asteroids) {
        for (auto& block : m_Blocks) {
            if (block.isDestroyed()) {
                continue;
            }
    
            sf::Vector2f asteroidPos = asteroid.getPosition();
            float radius = asteroid.getRadius();
            sf::FloatRect asteroidBounds(asteroidPos.x, asteroidPos.y, radius * 2, radius * 2);
    
            sf::FloatRect blockBounds = block.getGlobalBounds();
    
            if (asteroidBounds.intersects(blockBounds)) {
                
                asteroid.bounceOff(blockBounds);
    
            }
        }
    }
}