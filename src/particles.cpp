#include <vector>
#include <cmath>
#include <random>
#include <SFML/Graphics.hpp>
#include "particles.h"

ParticleSystem::ParticleSystem(const ParticleSystemConfig &config)
    : config(config), rng(std::random_device{}())
{
    createParticles();
}

void ParticleSystem::createParticles()
{
    std::uniform_real_distribution<float> angleDist(0, config.angleRange);
    std::uniform_real_distribution<float> velocityDist(0.8f * config.initialVelocity, 1.2f * config.initialVelocity);

    for (unsigned int i = 0; i < config.particleCount; ++i)
    {
        float angle = angleDist(rng);
        float velocity = velocityDist(rng);

        sf::Vector2f vel(velocity * std::cos(angle), velocity * std::sin(angle));

        data.positions.push_back(config.initialPosition); // Starting position
        data.velocities.push_back(vel);
        data.lifespans.push_back(config.particleLifespan);
        data.colors.push_back(config.particleColor);
        data.ages.push_back(0);
    }
}

void ParticleSystem::update(float deltaTime)
{
    for (size_t i = 0; i < data.positions.size(); ++i)
    {
        if (data.ages[i] < data.lifespans[i])
        {
            data.positions[i] += data.velocities[i] * deltaTime;
            data.ages[i] += deltaTime;
        }
        else if (!config.isOneShot)
        {
            std::uniform_real_distribution<float> angleDist(0, config.angleRange);
            std::uniform_real_distribution<float> velocityDist(0.8f * config.initialVelocity, 1.2f * config.initialVelocity);
            data.ages[i] = 0;
            float angle = angleDist(rng);
            float velocity = velocityDist(rng);
            sf::Vector2f vel(velocity * std::cos(angle), velocity * std::sin(angle));
            data.positions[i] = config.initialPosition;
            data.velocities[i] = vel;
        }
    }
}

void ParticleSystem::render(sf::RenderWindow &window)
{
    for (size_t i = 0; i < data.positions.size(); ++i)
    {
        if (data.ages[i] < data.lifespans[i])
        {
            sf::CircleShape particle(2.0f);
            particle.setPosition(data.positions[i]);
            particle.setFillColor(data.colors[i]);
            window.draw(particle);
        }
    }
}
