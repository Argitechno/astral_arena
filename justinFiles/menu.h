#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <cmath>


class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    void playSelectSound();
    int matchCount = 3;
    void incrementMatchCount();
    void decrementMatchCount();
    void updateMatchCountDisplay();
    void startEscHold();
    void cancelEscHold();
    bool isEscHeldLongEnough(float seconds);
    bool shouldShowEscHint() const;
    void toggleSound();
    bool isSoundEnabled() const;



private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedIndex;
    void updateColors();

    sf::SoundBuffer moveBuffer;
    sf::SoundBuffer selectBuffer;
    sf::Sound moveSound;
    sf::Sound selectSound;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape overlay;

    sf::Text navigationHint;
    sf::Clock pulseClock;
    sf::Clock backgroundClock;
    int scrollOffsetX = 0;

    sf::Clock escHoldClock;
    bool escPressed = false;
    bool escShown = false;
    float escPulseTime = 0.0f;
    sf::Text escHint;

    float titlePulseTime = 0.0f;
    bool soundEnabled = true;


};

