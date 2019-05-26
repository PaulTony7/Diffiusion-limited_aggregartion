#include "SFML/Graphics.hpp"


const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

class Particle {
private:
public:
    Particle(const sf::Vector2u& position);
    sf::Vector2u position;
    Particle() {}
    ~Particle() {}
    sf::Vector2u Move();
    void Reset(const int& x, const int& y);
};