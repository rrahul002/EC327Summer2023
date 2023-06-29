// GameLoop.cpp
#include "GameLoop.hpp"

using namespace sf;
using namespace std;

GameLoop::GameLoop() : window(sf::VideoMode(1000, 600), "Floppy Bird") {
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    srand(time(0));

    ::initializeGame(window, game, flappy, pipes, resources);
}


void GameLoop::handleEvents() {
    Event event;
    while (window.pollEvent(event)) {

        // bye bye
        if (event.type == Event::Closed) {
            window.close();
        }
        
        // flap
        else if (event.type == Event::KeyPressed &&
                    event.key.code == Keyboard::Space) {
            if (game.gameState == waiting) {
                game.gameState = started;
            }

            if (game.gameState == started) {
                flappy.v = -8;
                resources.sounds.hop.play();
            }

        // restart
        } else if (event.type == Event::KeyPressed &&
                    event.key.code == Keyboard::C &&
                    game.gameState == gameover) {
            game.gameState = waiting;
            flappy.sprite.setPosition(250, 300);
            game.score = 0;
            Pipe::screenpipes.clear();
        }
    }
}

void GameLoop::update() {
    flappy.sprite.setTexture(resources.textures.flappy[1]);
    game.scoreText.setString(to_string(game.score));
    game.highscoreText.setString("HI " + to_string(game.highscore));

    float fx = flappy.sprite.getPosition().x;
    float fy = flappy.sprite.getPosition().y;
    float fw = 34 * flappy.sprite.getScale().x;
    float fh = 24 * flappy.sprite.getScale().y;

    if (game.gameState == waiting || game.gameState == started) {
        if (game.frames % 6 == 0) {
            flappy.frame += 1;
        }
        if (flappy.frame == 3) {
            flappy.frame = 0;
        }
    }

    flappy.sprite.setTexture(resources.textures.flappy[flappy.frame]);

    if (game.gameState == started) {
        flappy.sprite.move(0, flappy.v);
        flappy.v += 0.5;
    }

    if (game.gameState == started) {
        if (fy < 0) {
            flappy.sprite.setPosition(250, 0);
            flappy.v = 0;
        } else if (fy > 600) {
            flappy.v = 0;
            game.gameState = gameover;
            resources.sounds.dishk.play();
        }
    }

    for (vector<Sprite>::iterator itr = Pipe::screenpipes.begin(); itr != Pipe::screenpipes.end(); itr++) {
        if (game.gameState == started && (*itr).getPosition().x == 250) {
            game.score++;
            resources.sounds.ching.play();

            if (game.score > game.highscore) {
                game.highscore = game.score;
            }

            break;
        }
    }

    if (game.gameState == started && game.frames % 90 == 0) {
        pipes.generatePipes(resources.textures.pipe, 150);
    }

    if (game.gameState == started) {
        pipes.movePipes(3.0);
    }

    pipes.removeOffscreenPipes();

    if (game.gameState == started) {
        for (vector<Sprite>::iterator itr = Pipe::screenpipes.begin(); itr != Pipe::screenpipes.end(); itr++) {

            float px, py, pw, ph;

            if ((*itr).getScale().y > 0) {
                px = (*itr).getPosition().x;
                py = (*itr).getPosition().y;
                pw = 52 * (*itr).getScale().x;
                ph = 320 * (*itr).getScale().y;
            } else {
                pw = 52 * (*itr).getScale().x;
                ph = -320 * (*itr).getScale().y;
                px = (*itr).getPosition().x;
                py = (*itr).getPosition().y - ph;
            }

            if (collides(fx, fy, fw, fh, px, py, pw, ph)) {
                game.gameState = gameover;
                resources.sounds.dishk.play();
            }
        }
    }

    game.frames++;
}

void GameLoop::render() {
    window.clear();
    window.draw(game.background[0]);
    window.draw(game.background[1]);
    window.draw(game.background[2]);
    window.draw(flappy.sprite);

    for (vector<Sprite>::iterator itr = Pipe::screenpipes.begin(); itr != Pipe::screenpipes.end(); itr++) {
        window.draw(*itr);
    }

    window.draw(game.scoreText);
    window.draw(game.highscoreText);

    if (game.gameState == gameover) {
        window.draw(game.gameover);

        if (game.frames % 60 < 30) {
            window.draw(game.pressC);
        }
    }
    window.display();
}

void GameLoop::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}
