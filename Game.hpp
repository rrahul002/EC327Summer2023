#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"

struct Game {
   int score = 0;
   int highscore = 0;
   int frames = 0;
   GameState gameState = waiting;
   sf::Sprite background[3];
   sf::Sprite gameover;
   sf::Text pressC;
   sf::Text scoreText;
   sf::Text highscoreText;
   sf::Font font;
};
