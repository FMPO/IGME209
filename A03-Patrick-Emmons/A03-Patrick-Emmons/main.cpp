#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace std;

Player* player_ptr; 

// deltaTime
Time g_preDeltaTime;
Clock g_deltaClock;

void Init(sf::RenderWindow& window) {
    // load textures
    Texture* playerTexture_ptr = new Texture();
    playerTexture_ptr->loadFromFile("Images/richard_px_01.png");

    Texture* healthTexture_ptr = new Texture();
    healthTexture_ptr->loadFromFile("Images/healthBar.png");
    

    player_ptr = new Player(playerTexture_ptr, healthTexture_ptr, sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));

    g_deltaClock.restart();
    g_preDeltaTime = g_deltaClock.getElapsedTime();
}

void Update(sf::RenderWindow& window) {
    Time currentTime = g_deltaClock.getElapsedTime();
    Time deltaTime = currentTime - g_preDeltaTime;
    float deltaSeconds = deltaTime.asSeconds();
    g_preDeltaTime = currentTime;

    if (player_ptr != NULL)
        player_ptr->Update(window, deltaSeconds);
}

void Render(sf::RenderWindow& window) {
    if (player_ptr != NULL)
        player_ptr->Render(window);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 960), "IGME209-A03");

    Init(window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 255, 255)); // clear the window with color(255,255,255)

        Update(window);
        Render(window);

        window.display(); // display the window
    }

    return 0;
}