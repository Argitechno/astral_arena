#include "asteroid.hpp"
#include "block.hpp"


/// @brief ASTEROID FUNCTIONS

Asteroid::Asteroid()
{
    asteroid.setRadius(20);
    asteroid.setTextureRect(sf::IntRect(50, 50, 100, 100));
    mIncrement = sf::Vector2f(4.f, 4.f);
}

Asteroid::Asteroid(sf::Texture* tex) 
: 
    Asteroid()
{
    texture = tex;
    asteroid.setTexture(texture);
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

void Asteroid::setSize(int rad) {
    asteroid.setRadius(rad);
}

void Asteroid::setColor(sf::Color color) {
    asteroid.setFillColor(color);
}

void Asteroid::setPosition(sf::Vector2f position) {
    asteroid.setPosition(position);
}

void Asteroid::update(float deltaTime) {
    moveAsteroid(deltaTime);
    if (!isDestroyed() && touchingBullet()) {
        destroy();
    }
}

void Asteroid::moveAsteroid(float dt)
{
    float speed = 2.f;
    float radius = asteroid.getRadius();
    sf::Vector2f position = asteroid.getPosition();

    const float boundaryOffset = 5.f;

    if ((position.x + 2 * radius > 600 - boundaryOffset && mIncrement.x > 0) ||
        (position.x < boundaryOffset && mIncrement.x < 0)) {
        mIncrement.x = -mIncrement.x;
        position.x = std::clamp(position.x, boundaryOffset, 600 - 2 * radius - boundaryOffset);
    }

    if ((position.y + 2 * radius > 600 - boundaryOffset && mIncrement.y > 0) ||
        (position.y < boundaryOffset && mIncrement.y < 0)) {
        mIncrement.y = -mIncrement.y;
        position.y = std::clamp(position.y, boundaryOffset, 600 - 2 * radius - boundaryOffset);
    }

    asteroid.setPosition(
        position.x + mIncrement.x * dt * speed,
        position.y + mIncrement.y * dt * speed
    );
}

void Asteroid::setTexture(sf::Texture* text)
{
    texture = text;
    asteroid.setTexture(texture);
}

void Asteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (!destroyed)
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

void Asteroid::bounceOffSpaceship(const sf::ConvexShape& ship) {
    sf::FloatRect shipBounds = ship.getGlobalBounds();
    sf::FloatRect asteroidBounds = asteroid.getGlobalBounds();

    if (!shipBounds.intersects(asteroidBounds)) return; // Quick check

    sf::Vector2f aCenter = {
        asteroidBounds.left + asteroidBounds.width / 2.f,
        asteroidBounds.top + asteroidBounds.height / 2.f
    };
    sf::Vector2f sCenter = {
        shipBounds.left + shipBounds.width / 2.f,
        shipBounds.top + shipBounds.height / 2.f
    };

    float dx = aCenter.x - sCenter.x;
    float dy = aCenter.y - sCenter.y;

    float overlapX = (shipBounds.width / 2 + asteroidBounds.width / 2) - std::abs(dx);
    float overlapY = (shipBounds.height / 2 + asteroidBounds.height / 2) - std::abs(dy);

    if (overlapX < overlapY) {
        if (dx > 0)
            asteroid.move(overlapX + 1.f, 0);
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
