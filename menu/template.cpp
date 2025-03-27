#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class MenuState {
    MAIN_MENU,
    GAME_SETUP,
    EXIT
};

struct GameSettings {
    int numPlayers = 2;
    int numMatches = 3;
    std::string selectedMap = "Default Map";
    std::vector<int> selectedShips = {0, 1};
    bool includeCPU = false;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Astral Arena - Menu");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    MenuState currentState = MenuState::MAIN_MENU;
    int selectedIndex = 0;

    std::vector<std::string> mainMenuOptions = {
        "Start Game",
        "Exit"
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (currentState == MenuState::MAIN_MENU) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedIndex = (selectedIndex - 1 + mainMenuOptions.size()) % mainMenuOptions.size();
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        selectedIndex = (selectedIndex + 1) % mainMenuOptions.size();
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        if (selectedIndex == 0) {
                            currentState = MenuState::GAME_SETUP;
                        } else if (selectedIndex == 1) {
                            window.close();
                        }
                    }
                } else if (currentState == MenuState::GAME_SETUP) {
                    // exits with ESC to main menu - can add more key events here
                    if (event.key.code == sf::Keyboard::Escape) {
                        currentState = MenuState::MAIN_MENU;
                    }
                }
            }
        }

        window.clear();

        if (currentState == MenuState::MAIN_MENU) {
            for (size_t i = 0; i < mainMenuOptions.size(); ++i) {
                sf::Text option;
                option.setFont(font);
                option.setString(mainMenuOptions[i]);
                option.setCharacterSize(36);
                option.setPosition(300.f, 200.f + i * 50.f);
                option.setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
                window.draw(option);
            }
        } else if (currentState == MenuState::GAME_SETUP) {
            sf::Text setupText("Game Setup - Press ESC to return", font, 24);
            setupText.setPosition(200.f, 300.f);
            window.draw(setupText);
        }

        window.display();
    }

    return 0;
}
