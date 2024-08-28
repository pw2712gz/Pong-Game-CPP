#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(float startX, float startY);

    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);

    sf::RectangleShape getShape() const;

private:
    sf::RectangleShape paddleShape;
    float yVelocity;
    const float paddleSpeed = 450.0f;
    const float paddleHeight = 100.0f;
    const float paddleWidth = 10.0f;
    const float windowHeight = 600.0f;
};

#endif
