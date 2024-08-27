#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <cmath>  // For std::cos and std::sin
#include <cstdlib>  // For std::rand

class Ball {
public:
    Ball(float startX, float startY);

    void update();
    void render(sf::RenderWindow& window);
    void checkCollision(const sf::RectangleShape& paddle1, const sf::RectangleShape& paddle2);
    void reset();

    // Method to get the ball's position
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape ballShape;
    sf::Vector2f velocity;
    const float ballRadius = 10.0f;
    const float initialSpeed = 0.05f;
    const float maxSpeed = 0.3f;  // Cap for the ball's speed
    const float windowWidth = 800.0f;
    const float windowHeight = 600.0f;

    void clampSpeed();  // Helper method to cap the speed
};

#endif
