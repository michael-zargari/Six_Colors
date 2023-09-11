#pragma once

#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Exagon.h"

class Player
{
public:
	Player(std ::pair<int,int>); 
	virtual ~Player() = default;
	virtual bool playerTurn(sf::Vector2f) = 0;
	std::pair<int, int> getSize() const;
	void BfsWalk(std::vector<std::shared_ptr<ShapeNode<Exagon>>>&, sf::Color, std::string);
	virtual double getAreaPercent() const = 0;
	virtual void setFirstColor() = 0;
private:
	std::pair<int, int> m_size;//hods board size


};