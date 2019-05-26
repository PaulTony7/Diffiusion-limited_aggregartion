#include "SFML/Graphics.hpp"
#include "Particle.hh"
#include <vector>
#include <stdlib.h>



int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Triangle");
    // window.setFramerateLimit(60);
    std::srand(time(NULL));
    
    float radius = 4.f;
    std::vector<sf::Vector2u> tree;
    sf::CircleShape leaf(radius, 4);
    leaf.setFillColor(sf::Color::White);

    sf::VertexArray points(sf::Points, SCREEN_WIDTH * SCREEN_HEIGHT);
    for(int i = 0; i < SCREEN_WIDTH; i++) {
        for(int j = 1; j <= SCREEN_HEIGHT; j++) {
            points[j + SCREEN_WIDTH * i].position = sf::Vector2f(float(i), float(j));
            points[j + SCREEN_WIDTH * i].color = sf::Color(20, 20, 20);
        }
    }

    points[SCREEN_WIDTH / 2 + SCREEN_WIDTH * (SCREEN_HEIGHT / 2)].color = sf::Color::Red;
    tree.push_back(sf::Vector2u(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
    Particle particles[100];
    for(int i = 0; i < 100; i++) {
        particles[i].Reset(rand() % SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, rand() % SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 4);
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

        // for(int i = 0; i < 100; i++) {
        //     points[particles[i].position.x + particles[i].position.y * SCREEN_WIDTH].color = sf::Color::White;
        // }

        for(int j = 0; j < 100; j++) {
            particlePosition = particles[j].Move();
            std::size_t treeSize = tree.size();
            for(std::size_t i = 0; i < treeSize; i++) {
                int compareX = tree[i].x - particlePosition.x;
                int compareY = tree[i].y - particlePosition.y;
                if(compareX * compareX <= radius * radius * 3 && compareY * compareY <= radius * radius * 3) {
                    tree.push_back(particlePosition);
                    particles[j].Reset(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);            
                }
            }
        }
        window.clear();

        for(std::size_t i = 0; i < tree.size(); i++) {
            leaf.setPosition(sf::Vector2f(tree[i]));
            window.draw(leaf);
        }

        window.display();
    }

    return EXIT_SUCCESS;
}