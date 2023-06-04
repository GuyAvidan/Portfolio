#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <memory>

int main()
{
    sf::Texture* texture0 = new sf::Texture;
    if(!texture0->loadFromFile("../../res/silver.png"))
    {
        std::cerr << "Error loading texture\n";
    }
    std::unique_ptr<sf::Texture> buf(texture0);
    //std::shared_ptr<sf::Texture> buf(texture0);
    sf::Vector2f windowSize(400.0f,600.1f);
    sf::RenderWindow window(sf::VideoMode(windowSize.x , windowSize.y), "SFML works!");
    float circleSize = 20.0f;
    sf::CircleShape shape(circleSize);
    shape.setTexture(buf.get());
    window.setFramerateLimit(60);
    sf::CircleShape shape2(30);
    shape2.setTexture(buf.get());

    sf::Vector2f position(0.0f,0.1f);
    float deltaX = 2.0f;
    float deltaY = 2.0f;

    sf::Vector2f position2(100.0f,100.1f);
    float deltaX2 = 3.0f;
    float deltaY2 = 2.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(position.x > windowSize.x - circleSize*2 || position.x < 0){
            
            deltaX = -deltaX;
        } else if(position.y > windowSize.y - circleSize*2 || position.y < 0)
        {
            deltaY = -deltaY;

        }

        position.x += deltaX;
        position.y += deltaY;

        if(position2.x > windowSize.x - 30*2 || position2.x < 0){
            
            deltaX2 = -deltaX2;
        } else if(position2.y > windowSize.y - 30*2 || position2.y < 0)
        {
            deltaY2 = -deltaY2;

        }

        position2.x += deltaX2;
        position2.y += deltaY2;

        shape.setPosition(position);
        shape2.setPosition(position2);

        window.clear();
        window.draw(shape);
        window.draw(shape2);
        window.display();
    }

    return 0;
}
