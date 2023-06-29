#ifndef GAMEINITIALIZATION_HPP
#define GAMEINITIALIZATION_HPP

#include <SFML/Graphics.hpp>
#include "Resources.hpp"
#include "Flappy.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include <vector>

using namespace sf;
using namespace std;

void initializeGame(RenderWindow &window, Game &game, Flappy &flappy, Pipe &pipes, Resources &resources);


#endif  // GAMEINITIALIZATION_HPP
