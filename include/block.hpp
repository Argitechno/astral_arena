
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "GameObject.hpp"

class Block : public sf::Drawable, public GameObject {

    public:
        Block();
        Block(sf::Vector2f size, sf::Color color, sf::Color oColor, bool isDestructible = true);
        ~Block(){};

        bool touchingBullet();
        sf::FloatRect getGlobalBounds() const;
        void setSize(sf::Vector2f size);
        void setColor(sf::Color Color);
        void setOutline(sf::Color Color);
        void setPosition(sf::Vector2f position);
        inline void setDestructable(bool dest)
        {
            destructible = dest;
        }
        sf::Vector2f getPosition() { return block.getPosition(); }
    
        /// @brief Update the object, deltaTime being time since last tick
        /// @param deltaTime
        void update(float deltaTime) override;

        bool isDestructible() const { return destructible; }
        void destroy();
        bool isDestroyed() const { return destroyed; }
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            if (!destroyed) {
                target.draw(block, states);
            }
        }
    private:
        sf::RectangleShape block;
        bool destructible;
        bool destroyed = false;

        
};