#pragma once

#include "Player.h"
#include <memory>
#include "ColorChoosingBar.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(std::shared_ptr<ShapeNode<Exagon>>, std::shared_ptr<ColorChoosingBar>, std::pair<int, int>);
	~HumanPlayer() = default;
	bool playerTurn(sf::Vector2f) override;
	double getAreaPercent() const override;
	void setFirstColor() override;

private:
	std::vector<std::shared_ptr<ShapeNode<Exagon>>> m_belongs;//holds all the owned nodes of a player
	std::shared_ptr<ColorChoosingBar> m_colorBar;
};