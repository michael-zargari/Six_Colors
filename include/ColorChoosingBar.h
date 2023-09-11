#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include"GameResources.h"

class ColorChoosingBar
{
public:
	ColorChoosingBar();
	~ColorChoosingBar() = default;
	void setFirstColors(sf::Color, std::string);
	void setColorChoiseHuman(sf::Vector2f, bool&, sf::Color&);
	void setColorChoiseComputer(sf::Color, sf::Color);
	void draw(sf::RenderWindow&);
	sf::Color& getCurrentColor(std::string);
	void restart();

private:
	//members
	std::vector <std::pair<sf::RectangleShape, std::string>> m_ColorChooseBar;
	std::string m_belongsTo;
	sf::Color m_temp;

	//functions
	void initColorToChoose();
	sf::RectangleShape createShape(sf::Vector2f, sf::Vector2f, int, sf::Color, sf::Color);
};