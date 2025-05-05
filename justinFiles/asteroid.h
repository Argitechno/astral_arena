#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

class Asteroid : public sf::Drawable {
    public:
        //constructor & destructors
        Asteroid();
        Asteroid(sf::RenderWindow& window, sf::Texture* tex);
        ~Asteroid(){};

        //getter functions
        sf::Vector2f getPosition() const;
        float getRadius() const;

        //bool
        bool touchingBullet();
        bool isTouchingAsteroid(const Asteroid& other);
        bool isTouchingBlock();
        bool isDestroyed() const { return destroyed; }
        void destroy() { destroyed = true; asteroid.setFillColor(sf::Color::Transparent); }

        //movement
        void moveAsteroid(float dt);
        //void reverseDirection();
        void update(float dt);
        void reverseDirectionX() { mIncrement.x = -mIncrement.x; }
        void reverseDirectionY() { mIncrement.y = -mIncrement.y; }
        void bounceOff(const sf::FloatRect& blockBounds);
        void bounceOffSpaceship(const sf::ConvexShape& ship);

        //setter functions
        void setSize(int size);
        void setColor(sf::Color mapColor);
        void setPosition(sf::Vector2f position);
        void loadTexture();
        void setTexture(sf:: Texture text);
        

    private:
        sf::RenderWindow& window;
        sf::Vector2f aPosition;
        sf::Vector2f mIncrement;
        sf::Texture* texture;
        sf:: Color aColor;
        sf::CircleShape asteroid;
        bool destroyed = false;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};