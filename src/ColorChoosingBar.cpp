#include "ColorChoosingBar.h"

ColorChoosingBar::ColorChoosingBar()
    :m_belongsTo("None")
{
	initColorToChoose();
}

//set the first color for the player(human or computer) in the bar
void ColorChoosingBar::setFirstColors(sf::Color choosing , std::string belongTo)
{
    for (auto& i : m_ColorChooseBar)
        if (i.first.getFillColor() == choosing)
        {
            i.first.setTexture(&GameResources::getGameResourcesInstance().getMenuTexture(), true);
            i.first.setOutlineColor(choosing);
            i.second = belongTo;
        }
           
}

//set the color choise for human
void ColorChoosingBar::setColorChoiseHuman(sf::Vector2f location, bool& valid , sf::Color& color)
{
    for(auto& i : m_ColorChooseBar)
        if (i.first.getGlobalBounds().contains(location))
            if (i.second == "Player")
                break;
            else if (i.second == "None" /*&& i.second != "Computer"*/)
            {
                for (auto& c : m_ColorChooseBar)
                {
                    if (&c == &i)
                        continue;
                    else if (c.second == "Player")
                    {
                        c.second = "None";
                        c.first.setTexture(nullptr);
                        c.first.setOutlineColor(sf::Color::Black);
                    }
                }
                i.second = "Player";
                color = i.first.getFillColor();
                i.first.setTexture(&GameResources::getGameResourcesInstance().getMenuTexture(), true);
                i.first.setOutlineColor(color);
                valid = true;
            }
}

//set color coise for computer
void ColorChoosingBar::setColorChoiseComputer(sf::Color current, sf::Color choise)
{
    for (auto& i : m_ColorChooseBar)
    {
        if (i.first.getFillColor() == current)
        {
            i.second = "None";
            i.first.setTexture(nullptr);
            i.first.setOutlineColor(sf::Color::Black);
        }
        else if (i.first.getFillColor() == choise)
        {
            i.second = "Computer";
            auto color = i.first.getFillColor();
            i.first.setTexture(&GameResources::getGameResourcesInstance().getMenuTexture(), true);
            i.first.setOutlineColor(color);
        }
    }

}

//drae color bar
void ColorChoosingBar::draw(sf::RenderWindow& window)
{
	for (const auto& i : m_ColorChooseBar)
		window.draw(i.first);
}

//get the requested color
sf::Color& ColorChoosingBar::getCurrentColor(std::string wanted)
{
    int i = 0;
    while(i < m_ColorChooseBar.size() && m_ColorChooseBar[i].second != wanted) i++;
    m_temp =  m_ColorChooseBar[i].first.getFillColor();
    return m_temp;
}

//reset data for restart
void ColorChoosingBar::restart()
{
    for(auto& i : m_ColorChooseBar)
        if (i.first.getTexture() != nullptr)
        {
            i.first.setTexture(nullptr);
            i.first.setOutlineColor(sf::Color::Black);
            i.second = "None";
        }
}

//initilaize
void ColorChoosingBar::initColorToChoose()
{
    //create the color choosing buttons, hold as pair of the object and bolean integer, 
    //the bolean integer gave the information if the buttu=on is pressed or not
    m_ColorChooseBar.push_back(std::pair<sf::RectangleShape, std::string>(createShape(sf::Vector2f(40, 40), sf::Vector2f(260, 700), 5, sf::Color::Black, sf::Color::Blue), "None"));
    m_ColorChooseBar.push_back(std::pair<sf::RectangleShape, std::string>(createShape(sf::Vector2f(40, 40), sf::Vector2f(360, 700), 5, sf::Color::Black, sf::Color::Red), "None"));
    m_ColorChooseBar.push_back(std::pair<sf::RectangleShape, std::string>(createShape(sf::Vector2f(40, 40), sf::Vector2f(460, 700), 5, sf::Color::Black, sf::Color::Yellow), "None"));
    m_ColorChooseBar.push_back(std::pair<sf::RectangleShape, std::string>(createShape(sf::Vector2f(40, 40), sf::Vector2f(560, 700), 5, sf::Color::Black, sf::Color::Green), "None"));
    m_ColorChooseBar.push_back(std::pair<sf::RectangleShape, std::string>(createShape(sf::Vector2f(40, 40), sf::Vector2f(660, 700), 5, sf::Color::Black, sf::Color::Cyan), "None"));
    m_ColorChooseBar.push_back(std::pair<sf::RectangleShape, std::string>(createShape(sf::Vector2f(40, 40), sf::Vector2f(760, 700), 5, sf::Color::Black, sf::Color::Magenta), "None"));
}

//create shape
sf::RectangleShape ColorChoosingBar::createShape(sf::Vector2f size, sf::Vector2f position, int thicness, sf::Color colorout, sf::Color colorin)
{
    auto shape = sf::RectangleShape(size);
    shape.setFillColor(colorin);
    shape.setOutlineColor(colorout);
    shape.setOutlineThickness(thicness);
    shape.setOrigin(shape.getSize().x / 2, shape.getSize().y / 2);
    shape.setPosition(position);

    return shape;
}