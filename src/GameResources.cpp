#include "GameResources.h"
#include <cstdlib>

//constructor
GameResources::GameResources()
    :m_color{ sf::Color::Blue, sf::Color::Red, sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan, sf::Color::Magenta }
{
    initTextures();
    initFonts();
    initSounds();
}

//static func - singelton class
//return intance to the class
GameResources& GameResources::getGameResourcesInstance()
{
    static GameResources resources;
    return resources;
}

//get the textures for the menu window
sf::Texture& GameResources::getMenuTexture()
{
    return m_menuTexture[0];
}

//get font
sf::Font& GameResources::getFont(int index)
{
    if (index < 2 && index >= 0)
        return m_font[index];
}

//play a wanted affect
void GameResources::Playaffect(int index)
{
    if (index < 2 && index >= 0)
    {
        m_affect.setBuffer(m_affects[index]);
        m_affect.play();
    }
}

//create the text 
sf::Text& GameResources::createText(std::string dataName, sf::Vector2f position, sf::Color color, int font, int size)
{
    m_text.setString(dataName);
    m_text.setFont(getFont(font));
    m_text.setPosition(position);
    const auto rect = m_text.getLocalBounds();
    m_text.setOrigin(rect.width / 2, rect.height / 2);
    m_text.setCharacterSize(size);
    m_text.setFillColor(color);
    m_text.setStyle(sf::Text::Regular);
    return m_text;
}

sf::Color& GameResources::getColor()
{
    return m_color[distrib(rd)];
}

sf::Color& GameResources::getColor(int i)
{
    return m_color[i];
}


//load the texture for the game
void GameResources::initTextures()
{
    sf::Texture name;
    name.loadFromFile("letter-x.png");
    m_menuTexture.push_back(name);
}

//load the fonts for the game
void GameResources::initFonts()
{
    char fontsPath[2][50] = { "C:/Windows/Fonts/Arial.ttf" ,"C:/Windows/Fonts/Ravie.ttf" };
    for (int i = 0; i < 2; i++)
    {
        sf::Font temp;
        temp.loadFromFile(fontsPath[i]);
        m_font.push_back(temp);
    }
}

void GameResources::initSounds()
{

    auto affect1 = sf::SoundBuffer();
    auto affect2 = sf::SoundBuffer();
    affect1.loadFromFile("player.wav");
    affect2.loadFromFile("computer.wav");
    m_affects.push_back(affect1);
    m_affects.push_back(affect2);
 
}

