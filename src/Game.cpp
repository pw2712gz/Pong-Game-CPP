#include "Game.hpp"
#include "Constants.hpp"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong Game"),
      player1(50.0f, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2.0f),
      player2(WINDOW_WIDTH - 50.0f - PADDLE_WIDTH, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2.0f),
      ball(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f),
      score1(0), score2(0), gameOver(false), ballInPlay(true) {

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font 'arial.ttf'" << std::endl;
    }

    // Load sounds
    soundManager.loadSound("paddle_hit", "assets/sounds/paddle_hit.wav");
    soundManager.loadSound("wall_hit", "assets/sounds/wall_hit.wav");
    soundManager.loadSound("score", "assets/sounds/score.wav");
    soundManager.loadSound("game_over", "assets/sounds/game-over-arcade.wav");

    // Initialize score texts
    player1ScoreText.setFont(font);
    player1ScoreText.setCharacterSize(24);
    player1ScoreText.setFillColor(sf::Color::Red);
    player1ScoreText.setPosition(WINDOW_WIDTH / 2.0f - 200.0f, WINDOW_HEIGHT - 50.0f);

    player2ScoreText.setFont(font);
    player2ScoreText.setCharacterSize(24);
    player2ScoreText.setFillColor(sf::Color::Blue);
    player2ScoreText.setPosition(WINDOW_WIDTH / 2.0f + 50.0f, WINDOW_HEIGHT - 50.0f);

    gameOverTextLine1.setFont(font);
    gameOverTextLine1.setCharacterSize(48);
    gameOverTextLine1.setFillColor(sf::Color::Green);

    gameOverTextLine2.setFont(font);
    gameOverTextLine2.setCharacterSize(24);
    gameOverTextLine2.setFillColor(sf::Color::Green);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        processEvents();
        update(clock.restart().asSeconds());
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (gameOver && event.type == sf::Event::KeyPressed) {
            resetGame();
        }
    }
}

void Game::update(float deltaTime) {
    if (!gameOver) {
        if (ballInPlay) {
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

            ball.update();
            ball.checkCollision(player1.getShape(), player2.getShape());

            if (ball.getPosition().y <= 0 || ball.getPosition().y + ball.getRadius() * 2 >= WINDOW_HEIGHT) {
                soundManager.playSound("wall_hit");
            }

            if (ball.getPosition().x < 0) {
                score2++;
                soundManager.playSound("score");
                ballInPlay = false;
                resetClock.restart();
            } else if (ball.getPosition().x > WINDOW_WIDTH) {
                score1++;
                soundManager.playSound("score");
                ballInPlay = false;
                resetClock.restart();
            }

            if (ball.getPosition().x <= player1.getShape().getPosition().x + player1.getShape().getSize().x ||
                ball.getPosition().x + ball.getRadius() * 2 >= player2.getShape().getPosition().x) {
                soundManager.playSound("paddle_hit");
            }

        } else if (resetClock.getElapsedTime().asSeconds() > 1.0f) {
            ball.reset();
            ballInPlay = true;
        }

        if (score1 >= WINNING_SCORE) {
            gameOver = true;
            gameOverTextLine1.setString("Player 1 Wins!");
            gameOverTextLine2.setString("Press any key to restart");
            soundManager.playSound("game_over");
        } else if (score2 >= WINNING_SCORE) {
            gameOver = true;
            gameOverTextLine1.setString("Player 2 Wins!");
            gameOverTextLine2.setString("Press any key to restart");
            soundManager.playSound("game_over");
        }

        sf::FloatRect textRect1 = gameOverTextLine1.getLocalBounds();
        gameOverTextLine1.setOrigin(textRect1.width / 2.0f, textRect1.height / 2.0f);
        gameOverTextLine1.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f - textRect1.height);

        sf::FloatRect textRect2 = gameOverTextLine2.getLocalBounds();
        gameOverTextLine2.setOrigin(textRect2.width / 2.0f, textRect2.height / 2.0f);
        gameOverTextLine2.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + textRect2.height);

        player1ScoreText.setString("Player 1: " + std::to_string(score1));
        player2ScoreText.setString("Player 2: " + std::to_string(score2));
    }
}

void Game::render() {
    window.clear();

    // Render the paddles, ball, and other elements
    player1.render(window);
    player2.render(window);
    ball.render(window);

    window.draw(player1ScoreText);
    window.draw(player2ScoreText);

    if (gameOver) {
        window.draw(gameOverTextLine1);
        window.draw(gameOverTextLine2);
    }

    window.display();
}

void Game::resetGame() {
    score1 = 0;
    score2 = 0;
    gameOver = false;
    ballInPlay = true;
    gameOverTextLine1.setString("");
    gameOverTextLine2.setString("");
    ball.reset();
}
