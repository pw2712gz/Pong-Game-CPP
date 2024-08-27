#include "Paddle.hpp"

Paddle::Paddle(float startX, float startY) {
    paddleShape.setSize(sf::Vector2f(paddleWidth, paddleHeight));
    paddleShape.setPosition(startX, startY);
    paddleShape.setFillColor(sf::Color::White);
    yVelocity = 0.0f;
}

void Paddle::moveUp(float deltaTime) {
    yVelocity = -paddleSpeed;
    sf::Vector2f pos = paddleShape.getPosition();
    pos.y += yVelocity * deltaTime;

    if (pos.y < 0) pos.y = 0;

    paddleShape.setPosition(pos);
}

void Paddle::moveDown(float deltaTime) {
    yVelocity = paddleSpeed;
    sf::Vector2f pos = paddleShape.getPosition();
    pos.y += yVelocity * deltaTime;

    if (pos.y + paddleHeight > windowHeight) pos.y = windowHeight - paddleHeight;

    paddleShape.setPosition(pos);
}

void Paddle::update() {
    // Additional logic can be added here if necessary
}

void Paddle::render(sf::RenderWindow& window) {
    window.draw(paddleShape);
}

sf::RectangleShape Paddle::getShape() {
    return paddleShape;
}
