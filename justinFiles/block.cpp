#include "map.h"
#include "asteroid.h"
#include "block.h"

/// @brief BLOCK FUNCTIONS

Block::Block() : Block(sf::Vector2f{100,100}, sf::Color::Yellow, true) {}

Block::Block(sf::Vector2f size, sf::Color color, bool isDestructible) {
    block.setSize(size);
    block.setFillColor(color);
    destructible = isDestructible;
    destroyed = false;
}

sf::FloatRect Block::getGlobalBounds() const {
    return block.getGlobalBounds();
}

void Block::destroy() {
    destroyed = true;
    block.setFillColor(sf::Color::Transparent);
}

bool Block::touchingBullet() {
    //if bullet object touching bounds of block and is destructable then destroy block
    return false;
}

void Block::setSize(sf::Vector2f size) {
    block.setSize(size);
}

void Block::setColor(sf::Color color) {
    block.setFillColor(color);
}

void Block::setPosition(sf::Vector2f position) {
    block.setPosition(position);
}
