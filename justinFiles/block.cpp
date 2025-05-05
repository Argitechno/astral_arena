#include "map.h"
#include "asteroid.h"
#include "block.h"

/// @brief BLOCK FUNCTIONS

Block::Block() : Block(sf::Vector2f{100,100}, sf::Color::Yellow, sf::Color::White, true) {}

Block::Block(sf::Vector2f size, sf::Color color, sf::Color oColor, bool isDestructible) {
    block.setSize(size);
    block.setFillColor(color);
    block.setOutlineColor(oColor);
    block.setOutlineThickness(5);
    destructible = isDestructible;
    destroyed = false;
}

sf::FloatRect Block::getGlobalBounds() const {
    return block.getGlobalBounds();
}

void Block::setOutline(sf::Color Color) {
    block.setOutlineColor(Color);
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
