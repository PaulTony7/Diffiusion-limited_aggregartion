// #include <iostream>
#include "SFML/Graphics.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Traingle");

    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = sf::Vector2f(10.f, 10.f);
    triangle[1].position = sf::Vector2f(400.f, 10.f);
    triangle[2].position = sf::Vector2f(10.f, 400.f);

    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Green;
    triangle[2].color = sf::Color::Blue;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(triangle);

        window.display();
    }

    return EXIT_SUCCESS;
}