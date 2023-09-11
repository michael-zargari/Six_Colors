#pragma once

#include <vector>
#include "Exagon.h"
#include "Graph.h"
#include <string>
#include <memory>

class GameBoard
{
public:
	GameBoard();
	~GameBoard() = default;
	void drawBoard(sf::RenderWindow&);
	void createBoard();
	std::pair<int, int> getBoardSize();
	void getSize();
	std::shared_ptr<ShapeNode<Exagon>> getPlayerStartingNode();
	std::shared_ptr<ShapeNode<Exagon>> getComputerStartingNode();
	void restart();
	void initNeighbor();
private:
    Graph <Exagon> m_data;//holds the tiles
	int m_amountInCols;
	int m_amountInRows;

};
