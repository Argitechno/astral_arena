#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Asteroid : public sf::Drawable {
    public:
        //constructor & destructors
        Asteroid();
        Asteroid(sf::RenderWindow& window);
        ~Asteroid(){};

        //getter functions
        sf::Vector2f getPosition() const;
        float getRadius() const;

        //bool
        bool touchingBullet();
        bool isTouchingAsteroid(const Asteroid& other);
        bool isTouchingBlock();

        //movement
        void moveAsteroid(float dt);
        //void reverseDirection();
        void update(float dt);
        void reverseDirectionX() { mIncrement.x = -mIncrement.x; }
        void reverseDirectionY() { mIncrement.y = -mIncrement.y; }
        void bounceOff(const sf::FloatRect& blockBounds);

        //setter functions
        void setSize(int size);
        void setColor(sf::Color mapColor);
        void setPosition(sf::Vector2f position);

    private:
        sf::RenderWindow& window;
        sf::Vector2f aPosition;
        sf::Vector2f mIncrement;
        sf::Texture aTexture;
        sf:: Color aColor;
        sf::CircleShape asteroid;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};