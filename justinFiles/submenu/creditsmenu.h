#ifndef CREDITSMENU_H
#define CREDITSMENU_H

#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Displays game credits with title animation and smooth scroll.
 */
class CreditsMenu {
public:
    /// Sets up fonts, layout, and credit lines
    CreditsMenu(float width, float height);

    /// Runs the credit screen event loop
    void run(sf::RenderWindow& window);

    /// Draws the credits (scrolling + animated title)
    void draw(sf::RenderWindow& window);

    /// Center a given sf::Text horizontally
    void centerText(sf::Text& text, float width, float y);

private:
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape overlay;

    std::vector<sf::Text> textBlocks;
    sf::Text footerHint;

    float titlePulseTime = 0.0f;
    float scrollOffset = 0.0f;
};

#endif // CREDITSMENU_H
