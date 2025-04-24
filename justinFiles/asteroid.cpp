#include "map.h"
#include "asteroid.h"
#include "block.h"


/// @brief ASTEROID FUNCTIONS

Asteroid::Asteroid(sf::RenderWindow& win) : window(win)
{
    asteroid.setRadius(50);
    asteroid.setFillColor(sf::Color::White);
    mIncrement = sf::Vector2f(4.f, 4.f);
}

sf::Vector2f Asteroid::getPosition() const {
    return asteroid.getPosition();
}

float Asteroid::getRadius() const {
    return asteroid.getRadius();
}

bool Asteroid::touchingBullet() {
    //if touching bullet then destroy asteroid
    return false;
}

bool Asteroid::isTouchingAsteroid(const Asteroid& other) {
    sf::Vector2f pos1 = asteroid.getPosition();
    sf::Vector2f pos2 = other.getPosition();
    float dist = sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
    return dist < (asteroid.getRadius() + other.getRadius());
}

bool Asteroid::isTouchingBlock() {
     //if touching block then float back
     return false;
}

void Asteroid::setSize(int rad) {
    asteroid.setRadius(rad);
}

void Asteroid::setColor(sf::Color color) {
    asteroid.setFillColor(color);
}

void Asteroid::setPosition(sf::Vector2f position) {
    asteroid.setPosition(position);
}

void Asteroid::update(float dt) {
    moveAsteroid(dt);
}

void Asteroid::moveAsteroid(float dt)
{
    sf::Vector2u winSize = window.getSize(); 
    float speed = 5.f;
    float radius = asteroid.getRadius();

    sf::Vector2f position = asteroid.getPosition();
    // sf::Vector2f center = position + sf::Vector2f(radius, radius);

    // Subtract 5 from window width and height for the boundaries
    const float boundaryOffset = 5.f;

    if ((position.x + 2 * radius > winSize.x - boundaryOffset && mIncrement.x > 0) || (position.x < boundaryOffset && mIncrement.x < 0)) {
        mIncrement.x = -mIncrement.x;
        position.x = std::clamp(position.x, boundaryOffset, winSize.x - 2 * radius - boundaryOffset);
    }

    if ((position.y + 2 * radius > winSize.y - boundaryOffset && mIncrement.y > 0) || (position.y < boundaryOffset && mIncrement.y < 0)) {
        mIncrement.y = -mIncrement.y;
        position.y = std::clamp(position.y, boundaryOffset, winSize.y - 2 * radius - boundaryOffset);
    }

    asteroid.setPosition(
        position.x + mIncrement.x * dt * speed,
        position.y + mIncrement.y * dt * speed
    );
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(asteroid, states);
}

void Asteroid::bounceOff(const sf::FloatRect& blockBounds) {
    sf::FloatRect asteroidBounds = asteroid.getGlobalBounds();

    float dx = (asteroidBounds.left + asteroidBounds.width / 2) - (blockBounds.left + blockBounds.width / 2);
    float dy = (asteroidBounds.top + asteroidBounds.height / 2) - (blockBounds.top + blockBounds.height / 2);

    float overlapX = (blockBounds.width / 2 + asteroidBounds.width / 2) - std::abs(dx);
    float overlapY = (blockBounds.height / 2 + asteroidBounds.height / 2) - std::abs(dy);

    if (overlapX < overlapY) {
        if (dx > 0)
            asteroid.move(overlapX + 1.f, 0); // push out slightly more
        else
            asteroid.move(-overlapX - 1.f, 0);
        mIncrement.x = -mIncrement.x;
    } else {
        if (dy > 0)
            asteroid.move(0, overlapY + 1.f);
        else
            asteroid.move(0, -overlapY - 1.f);
        mIncrement.y = -mIncrement.y;
    }
}