#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(std::shared_ptr<ShapeNode<Exagon>> node, std::shared_ptr<ColorChoosingBar> bar, std::pair<int, int> BoardSize)
	:m_colorBar(bar), Player(BoardSize)
{
	m_belongs.push_back(node);
	setFirstColor();
}

//player turn
bool HumanPlayer::playerTurn(sf::Vector2f location)
{
	bool validChoise = false;
	sf::Color Choise = m_colorBar->getCurrentColor("Player");

	m_colorBar->setColorChoiseHuman(location, validChoise, Choise);//set color to choose

	if(!validChoise)//if the set was not okay
		return false;

	for (auto& i : m_belongs)//change to choosing color
		i->m_shape.changeColor(Choise);

	BfsWalk(this->m_belongs, Choise, "Player");//get all the neighbors with the same color

	return true;
}

double HumanPlayer::getAreaPercent() const
{
	auto temp = getSize();
	return (double(m_belongs.size()) / (temp.first * temp.second)) * 100;
}

void HumanPlayer::setFirstColor()
{
	m_colorBar->setFirstColors(m_belongs[0]->m_shape.getShape().getFillColor(), "Player");
	BfsWalk(this->m_belongs, m_belongs[0]->m_shape.getShape().getFillColor(), "Player");
}


