#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "SoundManager.hpp"
#include "Constants.hpp"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void resetGame();

    sf::RenderWindow window;
    Paddle player1;
    Paddle player2;
    Ball ball;
    SoundManager soundManager;
    sf::Font font;

    int score1;
    int score2;
    bool gameOver;
    bool ballInPlay;

    sf::Text player1ScoreText;
    sf::Text player2ScoreText;
    sf::Text gameOverTextLine1;
    sf::Text gameOverTextLine2;

    sf::Clock resetClock;  // Clock to manage the reset delay
};

#endif // GAME_HPP
