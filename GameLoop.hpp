// GameLoop.hpp
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Collisions.hpp"
#include "Sounds.hpp"
#include "Textures.hpp"
#include "Flappy.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "Resources.hpp"
#include "GameInitialization.hpp"
#include "Pipe.hpp"

class GameLoop {
private:
    sf::RenderWindow window;
    Resources resources;
    Flappy flappy;
    Pipe pipes;
    Game game;

public:

    GameLoop();

    void handleEvents();
    void update();
    void render();
    void run();
};
