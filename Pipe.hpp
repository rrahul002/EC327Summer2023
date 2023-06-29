#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Pipe {
public:

   static std::vector<sf::Sprite> screenpipes;  

    Pipe(); // constructor
    void generatePipes(const sf::Texture& texture, int gap);
    void movePipes(float speed);
    void removeOffscreenPipes();

   
};

#endif // PIPE_H
