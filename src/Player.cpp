#include "Player.h"
#include <iostream>

Player::Player(std::pair<int, int> BoardSize)
	:m_size(BoardSize)
{}

std::pair<int, int> Player::getSize() const
{
    return m_size;
}

//bfs algorithem to get the neighbors with the same color
void Player::BfsWalk(std::vector<std::shared_ptr<ShapeNode<Exagon>>>& Nodes, sf::Color color,std::string owner)
{
	std::vector<std::vector<bool>> visited(m_size.first, std::vector<bool>(m_size.second, false));
    // Create a queue for BFS
    std::list< std::shared_ptr<ShapeNode<Exagon>>> queue;

    // Mark the current node as visited and enqueue it
    for (const auto& i : Nodes)
    {
        visited[i->m_position.first][i->m_position.second] = true;
        queue.push_back(i);
    }

    while (!queue.empty()) 
    {
        auto node = queue.front();
        for(auto &j : node->m_neighborList) 
            if (j->m_shape.getShape().getFillColor() == color && j->m_holdsBy == "None") //check if it has the same color
            {
                if (!visited[j->m_position.first][j->m_position.second])//check if not visited
                {
                    Nodes.push_back(j);//insert to owner vector(player/computer)
                    visited[j->m_position.first][j->m_position.second] = true;//chnge to visited
                    j->m_holdsBy = owner;//determine the owner
                    queue.push_back(j);
                }
            }
        queue.pop_front();
    }
}
