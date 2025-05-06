#include "menu.h"

Menu::Menu(float width, float height) {
    font.loadFromFile("arial.ttf");  // You need a font in the working dir
    std::vector<std::string> labels = {
        "Start Game", "Select Ship", "Select Map", "Match Count", "Exit"
    };

    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(labels[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setPosition(width / 3.f, height / 4.f + i * 50);
        options.push_back(text);
    }

    selectedIndex = 0;
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& text : options)
        window.draw(text);
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        options[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        options[selectedIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedIndex < options.size() - 1) {
        options[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        options[selectedIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex;
}
