#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "GameBoard.h"
#include "HumanPlayer.h"
#include "ComputerPlayer.h"
#include <memory>
#include "ColorChoosingBar.h"

class GameController
{
public:
	//consructor
	explicit GameController();
	~GameController() = default;

	//methods
	void run();
	void chooseDifficult();
	void handleClick(sf::Vector2f);
	void drawGame();
	void drawChoosing();
	void changeOption(int);
	Difficult getDifficult() const;
	void checkStatusGame();
	std::string getWinMessage();
	std::string getLostMessage();
	void endScreen(std::string);
	void restart();

private:
	sf::RenderWindow m_window;
	std::vector<sf::Text> m_difficultOptions;
	std::vector<sf::Text> m_names; // holds the game name and the programer name
	bool m_choosing;
	bool m_gameOver;
	sf::Sprite m_background;
	GameBoard gameBoard;
	std::vector < std::unique_ptr<Player>> m_players;
	std::shared_ptr<ColorChoosingBar> m_colorBar;
	
	////func
	void initText();

};
