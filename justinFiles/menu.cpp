#include "menu.h"

Menu::Menu(float width, float height) {
    font.loadFromFile("arial.ttf");  // Ensure this file is present in run directory

    // Load background
    if (!backgroundTexture.loadFromFile("menu_background.jpg")) {
        std::cerr << "Error: Could not load background image.\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }

    // Add transparent overlay to enhance contrast
    overlay.setSize(sf::Vector2f(width, height));
    overlay.setFillColor(sf::Color(0, 0, 0, 100));  // Slightly lightened

    // Title
    sf::Text title;
    title.setFont(font);
    title.setString("Astral Arena");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color(255, 200, 80));
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(2);
    title.setStyle(sf::Text::Bold);
    title.setPosition(width / 2.f - 160.f, height / 10.f);
    options.push_back(title); // Stored in options[0], not selectable

    // Menu labels
    std::vector<std::string> labels = {
        "Start Game", "Select Ship", "Select Map", "Match Count", "Exit"
    };

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setCharacterSize(28);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2);
        text.setFillColor(sf::Color(180, 0, 255));
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(2);
        text.setStyle(sf::Text::Bold);
        text.setPosition(width / 3.f, height / 4.f + 80 + i * 50);
        options.push_back(text);
    }

    selectedIndex = 1;  // Skip the title
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);  // Background first
    window.draw(overlay);           // Then darken
    for (const auto& text : options)
        window.draw(text);          // Then menu text on top
}

void Menu::moveUp() {
    if (selectedIndex > 1) { // Skip the title
        options[selectedIndex].setFillColor(sf::Color(220, 220, 255));  // Soft white for unselected
        selectedIndex--;
        options[selectedIndex].setFillColor(sf::Color(255, 51, 255));   // Magenta for selected
    }
}

void Menu::moveDown() {
    if (selectedIndex < options.size() - 1) {
        options[selectedIndex].setFillColor(sf::Color(220, 220, 255));
        selectedIndex++;
        options[selectedIndex].setFillColor(sf::Color(255, 51, 255));
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex - 1; // Adjust to skip title index
}
