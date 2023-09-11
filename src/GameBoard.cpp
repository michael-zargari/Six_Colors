#include "GameBoard.h"
#include "Macros.h"
#include "GameResources.h"
#include <map>

GameBoard::GameBoard()
	:m_amountInCols(0),m_amountInRows(0)
{}

void GameBoard::drawBoard(sf::RenderWindow& window) 
{
	for (const auto& i : m_data)
		window.draw(i.second->m_shape.getShape());
}

void GameBoard::createBoard()
{
	getSize();

	auto firstPosition = sf::Vector2f(100.f , 100.f);

	//create the grid
	for(int row = 0; row < m_amountInRows; row++)
	{
		auto previous = firstPosition.x;
		
		for(int col = 0; col < m_amountInCols ; col++)
		{
			auto position = sf::Vector2f(firstPosition.x, firstPosition.y);
			auto exagon = Exagon(RADIUS, position);
			auto vertexPosition = std::pair<int, int>{ row,col };
			auto node = std::make_shared<ShapeNode<Exagon>>(exagon, vertexPosition);
			auto toInsert = std::pair<std::pair<int, int>, std::shared_ptr<ShapeNode<Exagon>>>(vertexPosition, node);
			m_data.insert(toInsert);
			firstPosition.x += RADIUS * 2 * (std::sqrt(3.f) / 2);
		}
		firstPosition.x = previous + std::pow(-1, row) * RADIUS * (std::sqrt(3.f) / 2);
		firstPosition.y += RADIUS * 2 * 0.75;
		
		
	}
	initNeighbor();
}

//return board size
std::pair<int, int> GameBoard::getBoardSize()
{
	return std::pair<int, int>(m_amountInRows, m_amountInCols);
}

//calculate the amount of shapes that can enter in given area.
void GameBoard::getSize()
{
	auto firstPosition = sf::Vector2f(100.f, 100.f);

	while (firstPosition.y <= HIGHET + 100 + RADIUS * 2 * 0.75)
	{
		m_amountInRows++;
		firstPosition.y += RADIUS * 2 * 0.75;
	}
	while (firstPosition.x <= WIDTH + 100 + RADIUS / 2 + RADIUS * (std::sqrt(3.f) / 2))
	{
		m_amountInCols++;
		firstPosition.x += RADIUS * 2 * (std::sqrt(3.f) / 2);
	}
}

//return the player starting node - down left
std::shared_ptr<ShapeNode<Exagon>> GameBoard::getPlayerStartingNode()
{
	return m_data.getNode(std::make_pair<int, int>(m_amountInRows - 1, 0));
}

//return the computer starting node - top right
std::shared_ptr<ShapeNode<Exagon>> GameBoard::getComputerStartingNode()
{
	return m_data.getNode(std::make_pair<int, int>(0, m_amountInCols - 1));
}

//restart
void GameBoard::restart()
{
	m_data.clear();
	m_amountInCols = 0;
	m_amountInRows = 0;
}

//acording to the build of the board create a vector that holds the positions in the board of the neighbors
void GameBoard::initNeighbor()
{
	std::vector<std::vector<std::pair<int, int>>> neighcorPossible;
	auto  oddRow = std::vector<std::pair<int, int>>{ {0, 1}, { 0, -1 }, { -1,0 }, { -1,1 }, { 1,0 }, { 1,1 } };
	auto evenRow = std::vector<std::pair<int, int>>{ {0, 1}, { 0, -1 }, { -1,0 }, { -1,-1 }, { 1,0 }, { 1,-1 } };
	neighcorPossible.push_back(evenRow);
	neighcorPossible.push_back(oddRow);
	m_data.initNeighborList(neighcorPossible);
}


