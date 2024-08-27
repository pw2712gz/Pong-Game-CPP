#include "Paddle.hpp"

Paddle::Paddle(float startX, float startY) {
    paddleShape.setSize(sf::Vector2f(paddleWidth, paddleHeight));
    paddleShape.setPosition(startX, startY);
    paddleShape.setFillColor(sf::Color::White);
    yVelocity = 0.0f;
}

void Paddle::moveUp(float deltaTime) {
    yVelocity = -paddleSpeed;
}

void Paddle::moveDown(float deltaTime) {
    yVelocity = paddleSpeed;
}

void Paddle::update(float deltaTime) {
    sf::Vector2f pos = paddleShape.getPosition();
    pos.y += yVelocity * deltaTime;

    if (pos.y < 0) pos.y = 0;
    if (pos.y + paddleHeight > windowHeight) pos.y = windowHeight - paddleHeight;

    paddleShape.setPosition(pos);

    yVelocity = 0.0f;  // Reset velocity after applying movement
}

void Paddle::render(sf::RenderWindow& window) {
    window.draw(paddleShape);
}

sf::RectangleShape Paddle::getShape() const {
    return paddleShape;
}
