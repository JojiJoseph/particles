#include <SFML/Graphics.hpp>
#include "particles.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Particle System");

    ParticleSystemConfig config;
    config.particleCount = 160;
    config.initialVelocity = 400.0f;
    config.angleRange = 2*M_PI;
    config.particleLifespan = 3.0f;
    config.isExplosive = true;
    config.particleColor = sf::Color::Red;
    config.initialPosition = sf::Vector2f(400, 300); // Center of the screen

    ParticleSystem explosion(config);


    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        explosion.update(deltaTime);

        window.clear();
        explosion.render(window);
        window.display();
    }

    return 0;
}
