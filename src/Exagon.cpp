#include "Exagon.h"
#include <iostream>
#include "Macros.h"
#include "GameResources.h"

Exagon::Exagon(float radius, sf::Vector2f position)
	:m_exagon(createExagon(radius, position)), 
     m_deviationValues(RADIUS * 2 * (std::sqrt(3.f) / 2), RADIUS * 2 * 0.75)
{}

const sf::CircleShape Exagon::getShape() const
{
    return m_exagon;
}

sf::Vector2f Exagon::getDeviation() const
{
    return m_deviationValues;
}

void Exagon::changeColor(sf::Color color)
{
    m_exagon.setFillColor(color);
}


sf::CircleShape Exagon::createExagon(float radius, sf::Vector2f position)
{
    auto shape = sf::CircleShape(radius, 6);
    shape.setFillColor(GameResources::getGameResourcesInstance().getColor());
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);

    return shape;
}

