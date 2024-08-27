#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong Game");

    Paddle player1(50.0f, 250.0f);
    Paddle player2(730.0f, 250.0f);
    Ball ball(400.0f, 300.0f);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calculate delta time
        float deltaTime = clock.restart().asSeconds();

        // Input handling
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player1.moveUp(deltaTime);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player1.moveDown(deltaTime);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player2.moveUp(deltaTime);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player2.moveDown(deltaTime);
        }

        // Update game state
        player1.update();
        player2.update();
        ball.update();
        ball.checkCollision(player1.getShape(), player2.getShape());

        // Render
        window.clear();
        player1.render(window);
        player2.render(window);
        ball.render(window);
        window.display();
    }

    return 0;
}
