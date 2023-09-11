#pragma once

#include "Graph.h"
#include "Exagon.h"
#include<string>

class DifficultAlgorithm
{
public:
	DifficultAlgorithm(std::string&);
	~DifficultAlgorithm() = default;
	
	sf::Color& chooseColor(std::vector<std::shared_ptr<ShapeNode<Exagon>>>&, sf::Color, sf::Color, std::pair<int,int>);
	void Dfs(std::shared_ptr<ShapeNode<Exagon>> node, std::vector<std::vector<bool>>& visited, sf::Color, int&);
	void MediumHard(std::vector< std::shared_ptr<ShapeNode<Exagon>>>&, std::vector<std::vector<bool>>& );
	void updateAmountArray(int amount[], sf::Color, int);
	int getColorIndex(int amount[]) const;
private:
	std::string m_difficult;
	sf::Color m_choosing;
};