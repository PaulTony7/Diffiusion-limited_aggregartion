#include "SFML/Graphics.hpp"
#include "Particle.hh"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#define TWO_PI 6.28318530718

void particleReset(Particle& particle, const int& ring_width, const int& ring) {
    float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/TWO_PI));
    float radius = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/ring_width)) + ring;
    particle.Reset(sin(angle) * radius + SCREEN_WIDTH / 2, cos(angle) * radius + SCREEN_HEIGHT / 2); 
    // std::cout << sin(angle) << "  " << cos(angle) << std::endl;
}
int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Diffiusion limited aggregation");
    std::srand(time(NULL));
    
    int ring = 1;
    int ring_width = 7;
    int ring_out = ring + ring_width; 
    //initiated values
    std::vector<sf::Vector2u> tree;
    sf::CircleShape circle;
    circle.setRadius(ring);
    circle.setPosition(SCREEN_WIDTH / 2 - ring, SCREEN_HEIGHT / 2 - ring);
    circle.setFillColor(sf::Color(0,0,0,0));
    circle.setOutlineThickness(1);
    circle.setOutlineColor(sf::Color::Blue);

    sf::CircleShape circle2;
    circle2.setRadius(ring_out);
    circle2.setPosition(SCREEN_WIDTH / 2 - ring_out, SCREEN_HEIGHT / 2 - ring_out);
    circle2.setFillColor(sf::Color(0,0,0,0));
    circle2.setOutlineThickness(1);
    circle2.setOutlineColor(sf::Color::Blue);

    bool tree_filled[SCREEN_WIDTH][SCREEN_HEIGHT];

    sf::Uint8* pixels = new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4];
    for(int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for(int x = 0; x < SCREEN_WIDTH; x++)
        {
            pixels[(y * SCREEN_WIDTH + x) * 4 ]     =   0; // R
            pixels[(y * SCREEN_WIDTH + x) * 4 + 1]  =   0; // G
            pixels[(y * SCREEN_WIDTH + x) * 4 + 2]  =   0; // B
            pixels[(y * SCREEN_WIDTH + x) * 4 + 3]  = 255; // A
            tree_filled[x][y] = false;
        }
    }
    tree_filled[SCREEN_WIDTH/2][SCREEN_HEIGHT/2] = true;
    sf::Texture texture;
    texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
    sf::Sprite sprite;
    texture.update(pixels);
    sprite.setTexture(texture);


    sf::Vector2u initialPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    //starting seed
    
    int particleCount = 200;
    Particle particles[particleCount];
    for(int i = 0; i < particleCount; i++) {
        particleReset(particles[i], ring_width, ring);  
    }
    
    sf::Vector2u particlePosition;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        if(tree.size() < 250000) {
            for(int j = 0; j < particleCount; j++) {
                particlePosition = particles[j].Move();
                uint x = particlePosition.x;
                uint y = particlePosition.y;
                if(x < 1 || x >= SCREEN_WIDTH-1 || y < 1 || y >= SCREEN_HEIGHT-1) {
                    particleReset(particles[j], ring_width, ring);

                    continue;
                }
                if(tree_filled[x-1][y-1] || tree_filled[x][y-1] || tree_filled[x+1][y-1] ||
                   tree_filled[x-1][y]   ||                        tree_filled[x+1][y]   ||
                   tree_filled[x-1][y+1] || tree_filled[x][y+1] || tree_filled[x+1][y+1] ) {
                    tree.push_back(particlePosition);

                    int distFromMiddle = (SCREEN_WIDTH / 2 - x) * (SCREEN_WIDTH / 2 - x) 
                    + (SCREEN_HEIGHT / 2 - y) * (SCREEN_HEIGHT / 2 - y);
                    distFromMiddle = sqrt(distFromMiddle);
                    pixels[(y * SCREEN_WIDTH + x) * 4] = 255;
                    pixels[(y * SCREEN_WIDTH + x) * 4 + 1] = 255;
                    pixels[(y * SCREEN_WIDTH + x) * 4 + 2] = 255;
                    tree_filled[x][y] = true;

                    if(distFromMiddle > ring) {

                        ring = (int)distFromMiddle + 1;
                        ring_out = ring + ring_width;
                        circle.setRadius(ring);
                        circle.setPosition(SCREEN_WIDTH / 2 - ring, SCREEN_HEIGHT / 2 - ring);

                        circle2.setRadius(ring_out);
                        circle2.setPosition(SCREEN_WIDTH / 2 - ring_out, SCREEN_HEIGHT / 2 - ring_out);
                    }
                    particleReset(particles[j], ring_width, ring);
                }
            }
        }

        texture.update(pixels);
        sprite.setTexture(texture);
        
        window.clear();
        window.draw(sprite);
        window.draw(circle);
        window.draw(circle2);

        window.display();
    }

    delete pixels;
    return EXIT_SUCCESS;
}