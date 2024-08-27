#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");

    Paddle player1(50.0f, 250.0f);
    Paddle player2(730.0f, 250.0f);
    Ball ball(400.0f, 300.0f);

    int score1 = 0;  // Score for player 1
    int score2 = 0;  // Score for player 2

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font 'arial.ttf'" << std::endl;
        return -1;
    }

    // Create the player 1 score text
    sf::Text player1ScoreText;
    player1ScoreText.setFont(font);
    player1ScoreText.setCharacterSize(24);
    player1ScoreText.setFillColor(sf::Color::Red);
    player1ScoreText.setString("Player 1: 0");
    player1ScoreText.setPosition(window.getSize().x / 2.0f - 200.0f, window.getSize().y - 50.0f);

    // Create the player 2 score text
    sf::Text player2ScoreText;
    player2ScoreText.setFont(font);
    player2ScoreText.setCharacterSize(24);
    player2ScoreText.setFillColor(sf::Color::Blue);
    player2ScoreText.setString("Player 2: 0");
    player2ScoreText.setPosition(window.getSize().x / 2.0f + 50.0f, window.getSize().y - 50.0f);

    // Create the dashed middle line
    std::vector<sf::RectangleShape> dashedLine;
    float dashHeight = 15.0f;
    float dashSpacing = 15.0f;
    for (float y = 0; y < window.getSize().y; y += dashHeight + dashSpacing) {
        sf::RectangleShape dash(sf::Vector2f(2.0f, dashHeight));
        dash.setPosition(window.getSize().x / 2.0f, y);
        dash.setFillColor(sf::Color::White);
        dashedLine.push_back(dash);
    }

    // Create border lines
    sf::RectangleShape topBorder(sf::Vector2f(window.getSize().x, 5.0f));
    topBorder.setPosition(0.0f, 0.0f);
    topBorder.setFillColor(sf::Color::White);

    sf::RectangleShape bottomBorder(sf::Vector2f(window.getSize().x, 5.0f));
    bottomBorder.setPosition(0.0f, window.getSize().y - 5.0f);
    bottomBorder.setFillColor(sf::Color::White);

    sf::RectangleShape leftBorder(sf::Vector2f(5.0f, window.getSize().y));
    leftBorder.setPosition(0.0f, 0.0f);
    leftBorder.setFillColor(sf::Color::White);

    sf::RectangleShape rightBorder(sf::Vector2f(5.0f, window.getSize().y));
    rightBorder.setPosition(window.getSize().x - 5.0f, 0.0f);
    rightBorder.setFillColor(sf::Color::White);

    sf::Clock clock;
    sf::Clock resetClock;  // Clock to manage the reset delay

    bool ballInPlay = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        if (ballInPlay) {
            // Paddle movement
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player1.moveUp(deltaTime);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player1.moveDown(deltaTime);
            }
            player1.update(deltaTime);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                player2.moveUp(deltaTime);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                player2.moveDown(deltaTime);
            }
            player2.update(deltaTime);

            // Update ball
            ball.update();
            ball.checkCollision(player1.getShape(), player2.getShape());

            // Check if ball goes out of bounds and update scores
            if (ball.getPosition().x < 0) {
                score2++;  // Player 2 scores
                ballInPlay = false;
                resetClock.restart();  // Start the reset delay
            } else if (ball.getPosition().x > 800) {
                score1++;  // Player 1 scores
                ballInPlay = false;
                resetClock.restart();  // Start the reset delay
            }
        } else if (resetClock.getElapsedTime().asSeconds() > 1.0f) {  // 1-second delay before the ball is put back in play
            ball.reset();
            ballInPlay = true;
        }

        // Update the score displays
        player1ScoreText.setString("Player 1: " + std::to_string(score1));
        player2ScoreText.setString("Player 2: " + std::to_string(score2));

        // Render everything
        window.clear();
        window.draw(topBorder);
        window.draw(bottomBorder);
        window.draw(leftBorder);
        window.draw(rightBorder);

        for (const auto& dash : dashedLine) {
            window.draw(dash);  // Draw each dash of the middle line
        }

        player1.render(window);
        player2.render(window);
        ball.render(window);
        window.draw(player1ScoreText);  // Draw Player 1's name and score
        window.draw(player2ScoreText);  // Draw Player 2's name and score
        window.display();
    }

    return 0;
}
