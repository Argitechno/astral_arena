#ifndef DEADMENU_H
#define DEADMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @brief Temporary placeholder screen for unfinished features.
 */
class DeadMenu {
public:
    /**
     * @brief Initializes the submenu layout and style
     */
    DeadMenu(float width, float height);

    /// Run the event loop for this screen
    void run(sf::RenderWindow& parentWindow);

    /// Draws the entire dead menu screen
    void draw(sf::RenderWindow& window);

    /// Centers text horizontally
    void centerText(sf::Text& text, float windowWidth, float y);

private:
    sf::Font font;
    sf::Text title;
    sf::Text backOption;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape overlay;

    std::vector<sf::Text> texts;
};

#endif // DEADMENU_H
