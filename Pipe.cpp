#include "Pipe.hpp"
#include <stdlib.h> // for rand()

std::vector<sf::Sprite> Pipe::screenpipes;


Pipe::Pipe() {
    
}

void Pipe::generatePipes(const sf::Texture& texture, int gap) {
    int r = rand() % 275 + 75;
    

    // lower pipe
    sf::Sprite pipeL;
    pipeL.setTexture(texture);
    pipeL.setPosition(1000, r + gap);
    pipeL.setScale(2, 2);

    // upper pipe
    sf::Sprite pipeU;
    pipeU.setTexture(texture);
    pipeU.setPosition(1000, r);
    pipeU.setScale(2, -2);

    // push to the array
    screenpipes.push_back(pipeL);
    screenpipes.push_back(pipeU);
}

void Pipe::movePipes(float speed) {
    for (auto& pipe : screenpipes) {
        pipe.move(-speed, 0);
    }
}

void Pipe::removeOffscreenPipes() {
    auto end_itr = screenpipes.begin();

    for (; end_itr != screenpipes.end(); end_itr++) {
        if (end_itr->getPosition().x > -104) {
            break;
        }
    }

    screenpipes.erase(Pipe::screenpipes.begin(), end_itr);
}
