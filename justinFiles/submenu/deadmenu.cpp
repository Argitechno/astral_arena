#include "deadmenu.h"
#include <iostream>

DeadMenu::DeadMenu(float width, float height) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font.\n";
    }

    if (!backgroundTexture.loadFromFile("menu_background.jpg")) {
        std::cerr << "Error loading background image.\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }

    overlay.setSize(sf::Vector2f(width, height));
    overlay.setFillColor(sf::Color(0, 0, 0, 100));

    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("Feature Under Construction");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color(255, 180, 0));
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    centerText(title, width, height / 3.f);
    texts.push_back(title);

    // Return option
    sf::Text back;
    back.setFont(font);
    back.setString("Return to Main Menu");
    back.setCharacterSize(28);
    back.setFillColor(sf::Color::White);
    back.setOutlineColor(sf::Color::Black);
    back.setOutlineThickness(2);
    centerText(back, width, height / 2.f + 40);
    texts.push_back(back);

    // Hint
    sf::Text hint;
    hint.setFont(font);
    hint.setString("Press Enter or Esc to return");
    hint.setCharacterSize(18);
    hint.setFillColor(sf::Color(200, 200, 200));
    hint.setOutlineColor(sf::Color::Black);
    hint.setOutlineThickness(1);
    centerText(hint, width, height * 0.75f);
    texts.push_back(hint);
}

void DeadMenu::centerText(sf::Text& text, float windowWidth, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    text.setPosition(windowWidth / 2.f, y);
}

void DeadMenu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(overlay);
    for (const auto& text : texts)
        window.draw(text);
}

void DeadMenu::run(sf::RenderWindow& window) {
    bool running = true;
    sf::Event event;

    while (window.isOpen() && running) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape)) {
                running = false;
            }
        }

        window.clear();
        draw(window);
        window.display();
    }
}
