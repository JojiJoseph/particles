#ifndef PARTICLES_H
#define PARTICLES_H

#include <vector>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>

struct ParticleData
{
    std::vector<sf::Vector2f> positions;
    std::vector<sf::Vector2f> velocities;
    std::vector<float> lifespans;
    std::vector<sf::Color> colors;
    std::vector<float> ages;
};

struct ParticleSystemConfig
{
    unsigned int particleCount = 100;
    float initialVelocity = 300.0f;
    float angleRange = 2 * M_PI;
    float particleLifespan = 5.0f;
    bool isExplosive = true;
    bool isOneShot = false;
    sf::Color particleColor = sf::Color::Red;
    sf::Vector2f initialPosition = sf::Vector2f(400, 300); // Center of the screen by default

    ParticleSystemConfig() = default;
    ParticleSystemConfig(unsigned int count, float velocity, float angle, float lifespan, bool explosive, sf::Color color, sf::Vector2f position)
        : particleCount(count), initialVelocity(velocity), angleRange(angle), particleLifespan(lifespan), isExplosive(explosive), particleColor(color), initialPosition(position) {}
};


class ParticleSystem
{
public:
    ParticleSystem(const ParticleSystemConfig &config);

    void update(float deltaTime);
    void render(sf::RenderWindow &window);

private:
    void createParticles();

    ParticleSystemConfig config;
    ParticleData data;
    unsigned int particleCount;
    float initialVelocity;
    float angleRange;
    float particleLifespan;
    bool isExplosive;
    sf::Color particleColor;
    bool particlesCreated;
    std::mt19937 rng;
};

#endif // PARTICLES_H