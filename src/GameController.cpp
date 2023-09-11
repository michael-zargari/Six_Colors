#include "GameController.h"
#include "GameResources.h"
#include <chrono>

GameController::GameController()
	:m_window(sf::VideoMode(1000, 800), "6 Colors"),m_choosing(false) ,m_gameOver(false), m_colorBar(std::make_shared<ColorChoosingBar>())
{
    //initSprite();
    initText();
}

void GameController::run()
{
    bool computer = false;
    gameBoard.createBoard();
    chooseDifficult();
    m_window.clear(sf::Color(100, 100, 100, 0));
    drawGame();
    m_window.display();
    while (m_window.isOpen() && !m_gameOver)
    {
        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                if (m_names[3].getGlobalBounds().contains(location))//new game
                {
                    computer = false;
                    restart();//init for restart
                    continue;
                }
                if (!computer)//player turn
                {
                    GameResources::getGameResourcesInstance().Playaffect(0);
                    if(m_players[0]->playerTurn(location))
                        computer = true;

                    m_window.clear(sf::Color(100, 100, 100, 0));
                    drawGame();
                    m_window.display();
                }
                if (computer)//computer turn
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(250));
                    GameResources::getGameResourcesInstance().Playaffect(1);
                    m_players[1]->playerTurn(location);
                    m_window.clear(sf::Color(100, 100, 100, 0));
                    drawGame();
                    m_window.display();
                    computer = false;
                }
                     
                break;
            }
            }
        }
        checkStatusGame();
    }
}

//choose difficult screen
void GameController::chooseDifficult()
{
    while (m_window.isOpen() && !m_choosing)
    {
        m_window.clear(sf::Color(100, 100, 100, 0));
        drawChoosing();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::KeyPressed: 
            {
                if (event.key.code == sf::Keyboard::Up)
                    changeOption(-1);
                else if (event.key.code == sf::Keyboard::Down)
                    changeOption(1);
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    m_players.push_back(std::make_unique<HumanPlayer>(gameBoard.getPlayerStartingNode(), this->m_colorBar, gameBoard.getBoardSize()));
                    m_players.push_back(std::make_unique<ComputerPlayer>(gameBoard.getComputerStartingNode(), this->m_colorBar, getDifficult(), gameBoard.getBoardSize()));
                    m_choosing = true;
                }
                break;
            }
            }
        }
    }
}

void GameController::drawGame()
{
    gameBoard.drawBoard(this -> m_window);//draw bord
    
    m_colorBar->draw(this->m_window);//draw the color bar

    //draw the percent of the board that the player hold
    m_window.draw(GameResources::getGameResourcesInstance().createText("Player", sf::Vector2f(100, 700), sf::Color::White, 0,20));
    m_window.draw(GameResources::getGameResourcesInstance().createText(std::to_string(m_players[0]->getAreaPercent()),
                                                                        sf::Vector2f(100, 750), sf::Color::White, 0, 20));

    //draw the percent of the board that the computer hold
    m_window.draw(GameResources::getGameResourcesInstance().createText("Computer",sf::Vector2f(900, 700), sf::Color::White, 0,20));
    m_window.draw(GameResources::getGameResourcesInstance().createText(std::to_string(m_players[1]->getAreaPercent()), 
                                                                       sf::Vector2f(900, 750), sf::Color::White, 0, 20));
   //draw the new game buttun
    m_window.draw(m_names[3]);
}

//function draw for the choosing screen
void GameController::drawChoosing()
{
    //draw difficult options
    for(const auto& i : m_difficultOptions)
        m_window.draw(i);

    for (int i = 0;i < 3; i++)
        m_window.draw(m_names[i]);
}

//when key board press 
void GameController::changeOption(int toMove)
{
    int index = 0;
    while (m_difficultOptions[index].getFillColor() != sf::Color::White) index++;//get the current "pointer"

    if (index + toMove > 2 || index + toMove < 0)
        return;

    m_difficultOptions[index].setFillColor(sf::Color::Black);
    m_difficultOptions[index + toMove].setFillColor(sf::Color::White);
}

//when enter is pressed
Difficult GameController::getDifficult() const
{
    int index;
    for (index = 0; index < m_difficultOptions.size() && m_difficultOptions[index].getFillColor() != sf::Color::White; index++);
    return Difficult(index);
}

//check if somone win
void GameController::checkStatusGame()
{
    if (m_players[0]->getAreaPercent() >= 50.0)
        endScreen(getWinMessage());

    else if (m_players[1]->getAreaPercent() >= 50.0)
        endScreen(getLostMessage());
}

void GameController::initText()
{
    m_difficultOptions.push_back(GameResources::getGameResourcesInstance().createText("Easy", sf::Vector2f(500, 300), sf::Color::White, 1,30));
    m_difficultOptions.push_back(GameResources::getGameResourcesInstance().createText("Medium", sf::Vector2f(500, 400), sf::Color::Black, 1,30));
    m_difficultOptions.push_back(GameResources::getGameResourcesInstance().createText("Hard", sf::Vector2f(500, 500), sf::Color::Black, 1,30));
    m_names.push_back(GameResources::getGameResourcesInstance().createText("6ix 6olors", sf::Vector2f(500, 100), sf::Color::Black, 1,30));
    m_names.push_back(GameResources::getGameResourcesInstance().createText("Michael Zargari", sf::Vector2f(500, 700), sf::Color::Black, 1,30));
    m_names.push_back(GameResources::getGameResourcesInstance().createText("use the keyboard to choose level", sf::Vector2f(500, 765), sf::Color::Red, 0, 30));
    m_names.push_back(GameResources::getGameResourcesInstance().createText("New Game", sf::Vector2f(500, 765), sf::Color::Black, 0, 25));
}

//draw goodbye massege
void GameController::endScreen(std::string toDisplay)
{
    m_window.clear(sf::Color(100, 100, 100, 0));
    m_window.draw(GameResources::getGameResourcesInstance().createText(toDisplay, sf::Vector2f(400, 400), sf::Color::White, 0, 30));
    m_window.display();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    m_gameOver = true;
}

//reset data for new game
void GameController::restart()
{
    m_choosing = false;
    gameBoard.restart();
    m_players.clear();
    m_colorBar->restart();
    gameBoard.createBoard();
    chooseDifficult();
    m_window.clear(sf::Color(100, 100, 100, 0));
    drawGame();
    m_window.display();
}

std::string GameController::getLostMessage()
{
    return "+----------------------------------------------------------+\n"
        "|                           You Lose!                               |\n"
        "|                   Thank you for playing!                  |\n"
        "+----------------------------------------------------------+\n";
}

std::string GameController::getWinMessage()
{
    return "+----------------------------------------------------------+\n"
        "|                           You Win!                                |\n"
        "|                 Thank you for playing!                   |\n"
        "+----------------------------------------------------------+\n";
}
