#include "Ball.hpp"

Ball::Ball(float startX, float startY) {
    ballShape.setRadius(ballRadius);
    ballShape.setPosition(startX, startY);
    ballShape.setFillColor(sf::Color::Yellow);

    // Set initial velocity
    velocity = sf::Vector2f(initialSpeed, initialSpeed);
}

void Ball::update() {
    sf::Vector2f pos = ballShape.getPosition();
    pos += velocity;

    if (pos.y <= 0) {
        velocity.y = -velocity.y;
        pos.y = 0;
    } else if (pos.y + ballRadius * 2 >= windowHeight) {
        velocity.y = -velocity.y;
        pos.y = windowHeight - ballRadius * 2;
    }

    ballShape.setPosition(pos);
}

void Ball::render(sf::RenderWindow& window) {
    window.draw(ballShape);
}

void Ball::checkCollision(const sf::RectangleShape& paddle1, const sf::RectangleShape& paddle2) {
    const float speedIncrement = 0.05f;
    if (ballShape.getGlobalBounds().intersects(paddle1.getGlobalBounds())) {
        velocity.x = -velocity.x * (1.0f + speedIncrement);  // Increase speed
        ballShape.setPosition(paddle1.getPosition().x + paddle1.getSize().x + 1.0f, ballShape.getPosition().y);
    }
    if (ballShape.getGlobalBounds().intersects(paddle2.getGlobalBounds())) {
        velocity.x = -velocity.x * (1.0f + speedIncrement);  // Increase speed
        ballShape.setPosition(paddle2.getPosition().x - ballShape.getRadius() * 2 - 1.0f, ballShape.getPosition().y);
    }
}

void Ball::reset() {
    ballShape.setPosition(windowWidth / 2 - ballRadius, windowHeight / 2 - ballRadius);

    // Randomize initial direction
    float angle = static_cast<float>(std::rand() % 360);  // Angle in degrees
    velocity = sf::Vector2f(initialSpeed * std::cos(angle), initialSpeed * std::sin(angle));
}

sf::Vector2f Ball::getPosition() const {
    return ballShape.getPosition();
}
