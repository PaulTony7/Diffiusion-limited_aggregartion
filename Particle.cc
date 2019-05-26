#include "Particle.hh"
#include <random>
#include "time.h"



Particle::Particle(const sf::Vector2u& position): position(position) {}

sf::Vector2u Particle::Move() {
    position.x += (rand() % 3 - 1) * 4;
    position.y += (rand() % 3 - 1) * 4;
    if(position.x < 0) position.x = rand() % SCREEN_WIDTH;
    else if(position.x >= SCREEN_WIDTH) position.x = rand() % SCREEN_WIDTH;

    if(position.y < 0) position.y = rand() % SCREEN_HEIGHT;
    else if(position.y >= SCREEN_HEIGHT) position.y = rand() % SCREEN_HEIGHT;

    return position;
}

void Particle::Reset(const int& x, const int& y) {
    position.x = x;
    position.y = y;
}