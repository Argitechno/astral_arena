#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class DeadMenu {
public:
    DeadMenu(float width, float height);
    void run(sf::RenderWindow& parentWindow);  // Entry point
    void centerText(sf::Text& text, float windowWidth, float y);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text title;
    sf::Text backOption;
    int selectedIndex;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape overlay;

    std::vector<sf::Text> texts;
};
