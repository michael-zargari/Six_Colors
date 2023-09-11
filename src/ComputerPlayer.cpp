#include "ComputerPlayer.h"
#include "GameResources.h"

ComputerPlayer::ComputerPlayer(std::shared_ptr<ShapeNode<Exagon>> node, std::shared_ptr<ColorChoosingBar> bar, Difficult difficult, std::pair<int, int> BoardSize)
	:m_colorBar(bar), Player(BoardSize)
{
	m_belongs.push_back(node);
	setFirstColor();
	setDifficult(difficult);
}

//computer turn
bool ComputerPlayer::playerTurn(sf::Vector2f location)
{
	//get the current color of the player and the computer and choose from the other colors according to the level 
	auto current = m_colorBar->getCurrentColor("Computer");
	auto playerCurrent = m_colorBar->getCurrentColor("Player");
	auto choise = m_computerState -> chooseColor(m_belongs,current, playerCurrent, getSize());
	
	if(current != choise)
		m_colorBar->setColorChoiseComputer(current , choise); //set color to choose

	for (auto& i : m_belongs)//change to choosing color
		i->m_shape.changeColor(choise);
		

	BfsWalk(this->m_belongs, choise, "Computer");//get all the neighbors with the same color

	return true;
}

void ComputerPlayer::setDifficult(Difficult difficult)
{
	std::vector<std::string>difficults{ "Easy", "Medium", "Hard" };
	switch (difficult)
	{
	case Difficult::Easy: m_computerState.reset( new DifficultAlgorithm(difficults[0]));       break;
	case Difficult::Medium: m_computerState.reset(new DifficultAlgorithm(difficults[1]));      break;
	case Difficult::Hard: m_computerState.reset(new DifficultAlgorithm(difficults[2]));      break;
	}
	
}

void ComputerPlayer::setFirstColor()
{
	//in case the random color generate gave both the player and the computer the same color
	while (m_belongs[0]->m_shape.getShape().getFillColor() == m_colorBar->getCurrentColor("Player"))
		m_belongs[0] ->m_shape.changeColor(GameResources::getGameResourcesInstance().getColor());

	m_colorBar->setFirstColors(m_belongs[0]->m_shape.getShape().getFillColor(), "Computer");
	BfsWalk(this->m_belongs, m_belongs[0]->m_shape.getShape().getFillColor(), "Computer");
}

double ComputerPlayer::getAreaPercent() const
{
	auto temp = getSize();
	return (double(m_belongs.size()) / (temp.first * temp.second))*100;
}


