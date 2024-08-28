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

void Ball::render(sf::RenderWindow& window) {  // Ensure this is correctly implemented
    window.draw(ballShape);
}

void Ball::checkCollision(const sf::RectangleShape& paddle1, const sf::RectangleShape& paddle2) {
    const float speedIncrement = 0.03f;
    if (ballShape.getGlobalBounds().intersects(paddle1.getGlobalBounds())) {
        velocity.x = -velocity.x * (1.0f + speedIncrement);  // Increase speed
        clampSpeed();  // Cap the speed
        ballShape.setPosition(paddle1.getPosition().x + paddle1.getSize().x + 1.0f, ballShape.getPosition().y);
    }
    if (ballShape.getGlobalBounds().intersects(paddle2.getGlobalBounds())) {
        velocity.x = -velocity.x * (1.0f + speedIncrement);  // Increase speed
        clampSpeed();  // Cap the speed
        ballShape.setPosition(paddle2.getPosition().x - ballShape.getRadius() * 2 - 1.0f, ballShape.getPosition().y);
    }
}

void Ball::reset() {
    ballShape.setPosition(windowWidth / 2 - ballRadius, windowHeight / 2 - ballRadius);

    // Increase the speed slightly for reset
    float resetSpeed = initialSpeed * 1.5f;  // Adjust the multiplier as needed for more speed
    float angle = static_cast<float>((std::rand() % 120) + 30);  // Angle between 30 and 150 degrees
    float radians = angle * 3.14159f / 180.0f;  // Convert to radians

    // Set the velocity maintaining the increased speed magnitude
    float speedX = resetSpeed * std::cos(radians);
    float speedY = resetSpeed * std::sin(radians);
    velocity = sf::Vector2f(speedX, speedY);
}

sf::Vector2f Ball::getPosition() const {
    return ballShape.getPosition();
}

float Ball::getRadius() const {
    return ballRadius;
}

void Ball::clampSpeed() {
    if (std::abs(velocity.x) > maxSpeed) {
        velocity.x = maxSpeed * (velocity.x / std::abs(velocity.x));  // Keep the sign of x
    }
    if (std::abs(velocity.y) > maxSpeed) {
        velocity.y = maxSpeed * (velocity.y / std::abs(velocity.y));  // Keep the sign of y
    }
}
