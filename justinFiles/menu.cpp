/**
 * @file menu.cpp
 * @author Will Hall 
 * @brief Core menu logic and rendering system.
 *
 * Implements animated visuals for menu options, title glow, ESC hints, and
 * scrolling background. Controls sound playback, input navigation, and toggle
 * logic for match count and SFX. This is where the visual polish happens.

 * @date 2025-04-25
 *  
 */
#include "menu.h"

/**
 * @brief Construct a new Menu:: Menu object
 * 
 * @param width 
 * @param height 
 */
Menu::Menu(float width, float height) {
    font.loadFromFile("arial.ttf");
    if (!moveBuffer.loadFromFile("move.wav"))
        std::cerr << "Failed to load move.wav\n";
        moveSound.setBuffer(moveBuffer);

    if (!selectBuffer.loadFromFile("select.wav"))
        std::cerr << "Failed to load select.wav\n";
        selectSound.setBuffer(selectBuffer);
    
    // Load background
    if (!backgroundTexture.loadFromFile("menu_background.jpg")) {
        std::cerr << "Error: Could not load background image.\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);

        // Scroll texture over time (safe only if image is loaded)
        float scrollSpeed = 30.0f; // pixels per second
        unsigned int bgWidth = backgroundTexture.getSize().x;
        if (bgWidth > 0) {
            scrollOffsetX = static_cast<int>(backgroundClock.getElapsedTime().asSeconds() * scrollSpeed) % bgWidth;
            backgroundSprite.setTextureRect(sf::IntRect(scrollOffsetX, 0, 800, 600));
        }
    }

    std::cout << "Texture size: " << backgroundTexture.getSize().x << "x" << backgroundTexture.getSize().y << "\n";


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
        "Start Game", "Select Ship", "Select Map", "Match Count: 3", "Sound: On", "Credits", "Exit"
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
    
    navigationHint.setFont(font);
    navigationHint.setString("[W] / [S] to navigate, [Enter] to select");
    navigationHint.setCharacterSize(18);
    navigationHint.setFillColor(sf::Color(200, 200, 200));
    navigationHint.setOutlineColor(sf::Color::Black);
    navigationHint.setOutlineThickness(1);

    sf::FloatRect hintBounds = navigationHint.getLocalBounds();
    navigationHint.setOrigin(hintBounds.width / 2, hintBounds.height / 2);
    navigationHint.setPosition(width / 2.f, height - 40.f);

    escHint.setFont(font);
    escHint.setString("Hold [Esc] to quit");
    escHint.setCharacterSize(18);
    escHint.setFillColor(sf::Color(255, 100, 100));  // reddish
    escHint.setOutlineColor(sf::Color::Black);
    escHint.setOutlineThickness(1);

    sf::FloatRect escBounds = escHint.getLocalBounds();
    escHint.setOrigin(escBounds.width / 2, escBounds.height / 2);
    escHint.setPosition(width / 2.f, height - 20.f);  // just below nav hint

    selectedIndex = 1;  // Skip the title
    updateColors();
}

/**
 * @brief Draws and runs the full animated main menu.
 * This includes background scroll, pulsing selected item,
 * glow on the title, ESC hint, and navigation instructions.
 */
void Menu::draw(sf::RenderWindow& window) {
    if (backgroundTexture.getSize().x > 0) {
        float time = backgroundClock.getElapsedTime().asSeconds();
        float scrollSpeed = 30.0f; // pixels per second
        int scroll = static_cast<int>(time * scrollSpeed) % backgroundTexture.getSize().x;
    
        // First background tile
        backgroundSprite.setTextureRect(sf::IntRect(scroll, 0, 800, 600));
        backgroundSprite.setPosition(0, 0);
        window.draw(backgroundSprite);
    
        // Second tile to fill the gap (if needed)
        if (scroll > backgroundTexture.getSize().x - 800) {
            backgroundSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
            backgroundSprite.setPosition(backgroundTexture.getSize().x - scroll, 0);
            window.draw(backgroundSprite);
        }
    }
    window.draw(overlay);           // Then darken
        for (size_t i = 0; i < options.size(); ++i) {// 1. Draw animated glowing title
            sf::Text title = options[0];  // Copy title
            titlePulseTime += 0.03f;
            if (titlePulseTime > 1000.f) titlePulseTime = 0.f;
            float intensity = 200 + 55 * std::sin(titlePulseTime);
            title.setFillColor(sf::Color(intensity, 180, 50));  // Warm golden pulse
            window.draw(title);
            // 2. Draw menu items (skip index 0 — title)
            for (size_t i = 1; i < options.size(); ++i) {
                sf::Text drawableText = options[i];  // Copy so we can modify
            
                if (i == selectedIndex) {
                    float time = pulseClock.getElapsedTime().asSeconds();
                    float scale = 1.0f + 0.05f * std::sin(3.0f * time);
                    drawableText.setScale(scale, scale);
                    sf::FloatRect bounds = drawableText.getLocalBounds();
                    drawableText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
                    drawableText.setPosition(
                        options[i].getPosition().x + bounds.width / 2.f,
                        options[i].getPosition().y + bounds.height / 2.f
                    );
                }
                window.draw(drawableText);
            }            
    }
    if (shouldShowEscHint()) {
        escPulseTime += 0.05f;
        if (escPulseTime > 1000.0f) escPulseTime = 0.0f;
    
        float brightness = 180 + 75 * std::sin(escPulseTime);
        escHint.setFillColor(sf::Color(brightness, 80, 80));  // Red pulse
        window.draw(escHint);
    }
}

/**
 * @brief Move the menu selection up or down.
 * 
 * @param direction 1 for down, -1 for up
 */
void Menu::moveUp() {
    if (selectedIndex > 1) {
        selectedIndex--;
        updateColors();
        if (soundEnabled) moveSound.play();
    }
}   

/**
 * @brief Move the menu selection down or up.
 * 
 * @param direction 1 for down, -1 for up
 */
void Menu::moveDown() {
    if (selectedIndex < options.size() - 1) {
        selectedIndex++;
        updateColors();
        if (soundEnabled) moveSound.play();
    }
}

/**
 * @brief Get the index of the currently selected menu item.
 * 
 * @return int Index of the selected item (0 = title)
 */
int Menu::getSelectedIndex() const {
    return selectedIndex - 1; // Adjust to skip title index
}

/**
 * @brief Play the selection sound (Enter).
 * 
 * This is called when the user selects an option.
 */
void Menu::playSelectSound() {
    if (soundEnabled) selectSound.play();
}

/**
 * @brief Update the color of the menu items based on selection.
 * 
 * This function highlights the selected item and resets others.
 */
void Menu::updateColors() {
    for (size_t i = 1; i < options.size(); ++i) { // skip title at index 0
        options[i].setFillColor(i == selectedIndex ? sf::Color(128, 0, 255) : sf::Color::White); // purple for selected
    }
}

/**
 * @brief Update the match count display.
 * 
 * This function updates the label for the match count based on the current value.
 */
void Menu::updateMatchCountDisplay() {
    // "Match Count" is the 4th label = index 4 in options (0 = title)
    std::string base = "Match Count: ";
    options[4].setString(base + std::to_string(matchCount));
}

/**
 * @brief Increment the match count by 2 (odd only).
 * 
 * This function ensures the match count remains odd and updates the display.
 */
void Menu::incrementMatchCount() {
    if (matchCount < 9) matchCount+= 2;
    updateMatchCountDisplay();
}

/**
 * @brief Decrement the match count by 2 (odd only).
 * 
 * This function ensures the match count remains odd and updates the display.
 */
void Menu::decrementMatchCount() {
    if (matchCount > 1) matchCount-= 2;
    updateMatchCountDisplay();
}

/**
 * @brief Start the ESC hold timer for exit logic.
 * 
 * This function sets the state for holding ESC to quit.
 */
void Menu::startEscHold() {
    if (!escPressed) {
        escPressed = true;
        escShown = true;
        escHoldClock.restart();
    }
}

/**
 * @brief Cancel the ESC hold state.
 * 
 * This function resets the ESC hold state and hides the hint.
 */
void Menu::cancelEscHold() {
    escPressed = false;
    escShown = false;
}

/**
 * @brief Check if ESC has been held long enough to quit.
 * 
 * @param seconds The time in seconds to check against
 * @return true If ESC has been held long enough
 * @return false If not
 */
bool Menu::isEscHeldLongEnough(float seconds) {
    return escPressed && escHoldClock.getElapsedTime().asSeconds() >= seconds;
}

/**
 * @brief Check if the ESC hint should be displayed.
 * 
 * @return true If the hint should be shown
 * @return false If not
 */
bool Menu::shouldShowEscHint() const {
    return escShown;
}

/**
 * @brief Toggle the sound on or off.
 * 
 * This function updates the sound state and changes the label accordingly.
 */
void Menu::toggleSound() {
    soundEnabled = !soundEnabled;
    options[5].setString(soundEnabled ? "Sound: On" : "Sound: Off");
}

/**
 * @brief Check if sound is currently enabled.
 * 
 * @return true If sound is enabled
 * @return false If not
 */
bool Menu::isSoundEnabled() const {
    return soundEnabled;
}
