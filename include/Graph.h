#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include<iostream>
#include <map>

template <typename SHAPE>
struct ShapeNode
{
	SHAPE m_shape;
	std::vector<std::shared_ptr<ShapeNode<SHAPE>>> m_neighborList;
	std::pair<int, int> m_position;
	std::string m_holdsBy; //who holds this node

	//constructor
	ShapeNode(SHAPE& shape, std::pair<int,int>& position)
		:m_shape(shape), m_position(position), m_holdsBy("None")
	{}
};

template <typename SHAPENODE>
class Graph
{
public:
	using Node = std::shared_ptr<ShapeNode<SHAPENODE>>;
	using Container = std::map<std::pair<int, int>, Node>;

	Graph() = default;
	~Graph() = default;
	void insert(std::pair<std::pair<int, int>, Node>&);
	void initNeighborList(std::vector<std::vector<std::pair<int, int>>> neighbor);
	int size() const;
	void clear();
	Node getNode(std::pair<int, int>);
	Container::iterator begin() { return m_findIn.begin();}
	Container::iterator end() { return m_findIn.end(); }
private:
	 Container m_findIn;
};

template<typename SHAPENODE>
inline void Graph<SHAPENODE>::insert(std::pair<std::pair<int,int>,Node>& toInsert)
{	
	m_findIn.insert(toInsert);
}

template<typename SHAPENODE>
inline int Graph<SHAPENODE>::size() const
{
	return m_findIn.size();
}

template<typename SHAPENODE>
inline void Graph<SHAPENODE>::clear()
{
	m_findIn.clear();
}

//after we create the graph init the neighboors list of each node
//just need to get the positions posibilities of neighboors 
template<typename SHAPENODE>
inline void Graph<SHAPENODE>::initNeighborList(std::vector<std::vector<std::pair<int, int>>> neighbor)
{ 
	for (const auto& i : m_findIn)
	{
		int row = i.second->m_position.first % 2;
		for (int j = 0; j < neighbor[row].size(); j++)
		{
			auto toFind = std::make_pair<int, int>(i.second->m_position.first + neighbor[row][j].first, i.second->m_position.second + neighbor[row][j].second);
			auto it = m_findIn.find(toFind);
			if (it != m_findIn.end())
			{
				i.second->m_neighborList.push_back(it->second);
			}
		}
	}
}

template<typename SHAPENODE>
inline Graph<SHAPENODE>::Node Graph<SHAPENODE>::getNode(std::pair<int, int> toFind)
{
	auto it = m_findIn.find(toFind);
	return it->second;
}