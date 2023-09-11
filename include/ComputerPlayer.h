#pragma once

#include "Player.h"
#include <memory>
#include "ColorChoosingBar.h"
#include"DifficultAlgorithm.h"
#include "Macros.h"

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(std::shared_ptr<ShapeNode<Exagon>>, std::shared_ptr<ColorChoosingBar>, Difficult, std::pair<int, int>);
	~ComputerPlayer() = default;
	bool playerTurn(sf::Vector2f) override;
	void setDifficult(Difficult difficult);
	void setFirstColor();
	double getAreaPercent() const;
	
private:
	std::vector<std::shared_ptr<ShapeNode<Exagon>>> m_belongs;//holds all the owned nodes of a player
	std::shared_ptr<ColorChoosingBar> m_colorBar;
	std::unique_ptr<DifficultAlgorithm> m_computerState;
};