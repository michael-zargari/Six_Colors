#include "DifficultAlgorithm.h"
#include "GameResources.h"
#include "Macros.h"

DifficultAlgorithm::DifficultAlgorithm(std::string& difficult)
	:m_difficult(difficult)
{
    srand(time(nullptr));
}

//the choosing color function 
sf::Color& DifficultAlgorithm::chooseColor(std::vector<std::shared_ptr<ShapeNode<Exagon>>>& Nodes, sf::Color current, sf::Color playerCurrent, std::pair<int, int> size)
{
    std::vector<std::vector<bool>> visited(size.first, std::vector<bool>(size.second, false));
    
    std::vector< std::shared_ptr<ShapeNode<Exagon>>> neighborHold;

    for (const auto& i : Nodes)
        visited[i->m_position.first][i->m_position.second] = true;

    // Mark the current node as visited and enqueue it
    for (const auto& i : Nodes)
    {
        //get the neighbors that are with diffrent colors from the current and the player
        for (auto& it : i->m_neighborList)
            if (!visited[it->m_position.first][it->m_position.second] &&
                (it->m_shape.getShape().getFillColor() != current && it->m_shape.getShape().getFillColor() != playerCurrent))
            {
                visited[it->m_position.first][it->m_position.second] = true;
                neighborHold.push_back(it);
            }      
    }

    //easy - random color from the options
    if (m_difficult == "Easy")
        m_choosing = neighborHold[rand() % neighborHold.size()]->m_shape.getShape().getFillColor();

    if (m_difficult == "Medium" || m_difficult == "Hard")
        MediumHard(neighborHold, visited);

    return m_choosing;
}

//use dfs to get neighbor of neighbor of ......(using for hard difficulty)
void DifficultAlgorithm::Dfs(std::shared_ptr<ShapeNode<Exagon>> node, std::vector<std::vector<bool>>& visited, sf::Color color, int& amount)
{

    // Mark the current node as visited
    visited[node->m_position.first][node->m_position.second] = true;

    for (auto& it : node->m_neighborList)
        if (!visited[it->m_position.first][it->m_position.second] && it->m_shape.getShape().getFillColor() == color)
            Dfs(it, visited, color, amount += 1);
}

//the medium and the hard difficult algorithems using the same approach -> choosing the color according to the amount the occurs,
//the diffrence is that the medium look only the "level 1" neighboors, while the hard one looking above to choose the color.
void DifficultAlgorithm::MediumHard(std::vector<std::shared_ptr<ShapeNode<Exagon>>>& neighborHold, std::vector<std::vector<bool>>& visited)
{
    int amount[6] = { 0 };
    for (auto& it : neighborHold)
    {
        int colorAmount = 1;
        if (m_difficult == "Hard")
            Dfs(it, visited, it->m_shape.getShape().getFillColor(), colorAmount);

        updateAmountArray(amount, it->m_shape.getShape().getFillColor(), colorAmount);
    }
    m_choosing = GameResources::getGameResourcesInstance().getColor(getColorIndex(amount));
}

//update the array that save the amount in every color occur
void DifficultAlgorithm::updateAmountArray(int amount[], sf::Color color, int toAdd)
{
    if (color == sf::Color::Blue)
        amount[int(Colors::Blue)] += toAdd;
    else if (color == sf::Color::Red)
        amount[int(Colors::Red)] += toAdd;
    else if (color == sf::Color::Yellow)
        amount[int(Colors::Yellow)] += toAdd;
    else if (color == sf::Color::Green)
        amount[int(Colors::Green)] += toAdd;
    else if (color == sf::Color::Cyan)
        amount[int(Colors::Cyan)] += toAdd;
    else if (color == sf::Color::Magenta)
        amount[int(Colors::Magenta)] += toAdd;
}

//get the undex of the color that occur the most in this turn
int DifficultAlgorithm::getColorIndex(int amount[]) const
{
    int bigger = 0;
    int index = 0;
    for (int i = 0; i < 6; i++)
        if (amount[i] > bigger)
        {
            bigger = amount[i];
            index = i;
        }
    return index;
}
