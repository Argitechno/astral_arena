/**
 * @file creditsmenu.cpp
 * @author Will Hall 
 * @brief Displays credits with animated scrolling and pulsing title.
 *
 * Lists contributors and asset attributions. Includes soft background scroll,
 * semi-transparent overlay, and return-to-menu instruction at the bottom.
 * 
 * @date 2025-05-06
 * 
 */
#include "creditsmenu.h"
#include <iostream>
#include <cmath>

/**
 * @brief Prepares credit text blocks, background, and footer hint.
 */
CreditsMenu::CreditsMenu(float width, float height) {
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Error loading font.\n";
    }

    if (!backgroundTexture.loadFromFile("assets/images/menu_background.jpg")) {
        std::cerr << "Error loading background.\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }

    overlay.setSize(sf::Vector2f(width, height));
    overlay.setFillColor(sf::Color(0, 0, 0, 100));

    std::vector<std::string> credits = {
        "Astral Arena",
        "",
        "Created by: The Three Amigos",
        "Caleb Blondell - Player Logic",
        "Justin Keimer - Map / Arena",
        "Will Hall - Menu System",
        "",
        "Powered by SFML",
        "Sound effects: freesound.org",
        "Font: Arial (system)"
    };

    float y = height / 6.f;
    for (const auto& line : credits) {
        sf::Text t;
        t.setFont(font);
        t.setString(line);
        t.setCharacterSize(line == "Astral Arena" ? 36 : 22);
        t.setFillColor(sf::Color::White);
        t.setOutlineColor(sf::Color::Black);
        t.setOutlineThickness(1);
        centerText(t, width, y);
        y += 40;
        textBlocks.push_back(t);
    }

    // Footer hint
    footerHint.setFont(font);
    footerHint.setString("Press Enter or ESC to return");
    footerHint.setCharacterSize(18);
    footerHint.setFillColor(sf::Color(200, 200, 200));
    footerHint.setOutlineColor(sf::Color::Black);
    footerHint.setOutlineThickness(1);
    sf::FloatRect hintBounds = footerHint.getLocalBounds();
    footerHint.setOrigin(hintBounds.width / 2.f, hintBounds.height / 2.f);
    footerHint.setPosition(width / 2.f, height - 30.f);
}

/**
 * @brief Centers the text horizontally at a given y-coordinate.
 * 
 * @param text The text to center.
 * @param width The width of the window.
 * @param y The y-coordinate for positioning.
 */
void CreditsMenu::centerText(sf::Text& text, float width, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    text.setPosition(width / 2.f, y);
}

/**
 * @brief Draws the credits screen with animated title and scrolling text.
 * 
 * @param window The window to draw on.
 */
void CreditsMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(overlay);

    titlePulseTime += 0.03f;
    if (titlePulseTime > 1000.f) titlePulseTime = 0.f;
    float glow = 200 + 55 * std::sin(titlePulseTime);

    // Scroll offset
    scrollOffset += 0.2f;

    for (size_t i = 0; i < textBlocks.size(); ++i) {
        sf::Text drawText = textBlocks[i];
        sf::Vector2f pos = drawText.getPosition();
        pos.y -= scrollOffset;
        drawText.setPosition(pos);

        if (i == 0) { // Title glow
            drawText.setFillColor(sf::Color(glow, 180, 50));
        }

        // Draw if visible
        if (pos.y > -50 && pos.y < 650)
            window.draw(drawText);
    }

    window.draw(footerHint);
}

/**
 * @brief Runs the event loop for the credits screen.
 * 
 * @param window The window to run the event loop on.
 */
void CreditsMenu::run(sf::RenderWindow& window) {
    bool running = true;
    sf::Event event;

    while (window.isOpen() && running) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)) {
                running = false;
            }
        }

        window.clear();
        draw(window);
        window.display();
    }
}