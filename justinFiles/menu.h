#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include <cmath>

/**
 * @brief Controls the main menu system for Astral Arena.
 *        Handles drawing, selection, sound effects, and animated polish.
 */
class Menu {
public:
    /**
     * @brief Build the menu system with all visuals and options.
     * @param width Screen width
     * @param height Screen height
     */
    Menu(float width, float height);

    /// Draws the full menu screen with animations
    void draw(sf::RenderWindow& window);

    /// Move menu selection up
    void moveUp();

    /// Move menu selection down
    void moveDown();

    /// Get index of currently selected menu item
    int getSelectedIndex() const;

    /// Play selection sound (Enter)
    void playSelectSound();

    /// Increase match count (odd only)
    void incrementMatchCount();

    /// Decrease match count (odd only)
    void decrementMatchCount();

    /// Update the visible label for match count
    void updateMatchCountDisplay();

    /// Start ESC hold timer for exit logic
    void startEscHold();

    /// Cancel ESC hold state
    void cancelEscHold();

    /// Check if ESC has been held long enough to quit
    bool isEscHeldLongEnough(float seconds);

    /// Should the ESC hint be displayed?
    bool shouldShowEscHint() const;

    /// Toggle sound (on/off)
    void toggleSound();

    /// Is sound currently enabled?
    bool isSoundEnabled() const;

private:
    sf::Font font;
    std::vector<sf::Text> options;
    int selectedIndex;
    void updateColors();

    // Sound assets and playback
    sf::SoundBuffer moveBuffer;
    sf::SoundBuffer selectBuffer;
    sf::Sound moveSound;
    sf::Sound selectSound;

    // Background visuals
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape overlay;

    // UI hints and animated values
    sf::Text navigationHint;
    sf::Clock pulseClock;
    sf::Clock backgroundClock;
    int scrollOffsetX = 0;

    // ESC exit logic
    sf::Clock escHoldClock;
    bool escPressed = false;
    bool escShown = false;
    float escPulseTime = 0.0f;
    sf::Text escHint;

    float titlePulseTime = 0.0f;

    bool soundEnabled = true;
    int matchCount = 3;
};

#endif // MENU_H
