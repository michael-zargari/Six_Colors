#pragma once

#include <vector>
#include<random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class GameResources
{
public:
	static GameResources& getGameResourcesInstance();
	GameResources(const GameResources&) = delete;//disable copy constructor
	GameResources operator=(const GameResources&) = delete;//disable assimenget operator
	sf::Texture& getMenuTexture();
	sf::Font& getFont(int index);
	void Playaffect(int index);
	sf::Text& createText(std::string, sf::Vector2f, sf::Color, int, int);
	sf::Color& getColor();
	sf::Color& getColor(int i);

private:
	//constructor/ distructor
	GameResources();
	~GameResources() = default;

	//members
	sf::Color m_color[6];
	std::vector <sf::Texture > m_menuTexture;
	std::vector <sf::Font> m_font;
	std::vector <sf::SoundBuffer> m_affects;
	sf::Sound m_affect;
	sf::Text m_text;
	std::random_device rd;//for random color
	std::uniform_int_distribution<int> distrib{ 0, 5 };//for random color

	//func
	void initTextures();
	void initFonts();
	void initSounds();
};