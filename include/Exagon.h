#pragma once

#include <SFML/Graphics.hpp>
//#include <set>

class Exagon
{
public:
	explicit Exagon(float, sf::Vector2f);
	~Exagon() = default;
	const sf::CircleShape getShape() const;
    sf::Vector2f getDeviation() const;
    void changeColor(sf::Color);
private:
    //members
    sf::CircleShape m_exagon;
    sf::Vector2f m_deviationValues;

    //init func
    sf::CircleShape createExagon(float, sf::Vector2f);
};