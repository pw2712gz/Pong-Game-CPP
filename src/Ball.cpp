#include "Ball.hpp"

Ball::Ball(float startX, float startY) {
    ballShape.setRadius(ballRadius);
    ballShape.setPosition(startX, startY);
    ballShape.setFillColor(sf::Color::Yellow);  // Changed ball color to Yellow

    velocity = sf::Vector2f(0.0f, 0.0f);  // Keep the ball stationary for now
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
    if (ballShape.getGlobalBounds().intersects(paddle1.getGlobalBounds())) {
        velocity.x = -velocity.x;
        ballShape.setPosition(paddle1.getPosition().x + paddle1.getSize().x, ballShape.getPosition().y);
    }
    if (ballShape.getGlobalBounds().intersects(paddle2.getGlobalBounds())) {
        velocity.x = -velocity.x;
        ballShape.setPosition(paddle2.getPosition().x - ballShape.getRadius() * 2, ballShape.getPosition().y);
    }
}

void Ball::reset() {
    ballShape.setPosition(windowWidth / 2 - ballRadius, windowHeight / 2 - ballRadius);
    velocity = sf::Vector2f(0.0f, 0.0f);  // Keep the ball stationary for now
}

sf::Vector2f Ball::getPosition() const {
    return ballShape.getPosition();
}
