#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
using namespace sf;

// window size
unsigned int win_W = 800;
unsigned int win_H = 800;

// deltaTime
Time g_preDeltaTime;
Clock g_deltaClock;

class AABB { // axis-aligned bounding box (AABB)
public:
    Vector2f min;
    Vector2f max;

    Color color;

    AABB(Vector2f min, Vector2f max, Color color) {
        this->min = min;
        this->max = max;
        this->color = color;
    }

    void draw(RenderWindow& window) {
        // draw the box as quad
        sf::VertexArray quad(sf::Quads, 4);

        quad[0].position = Vector2f(min.x, min.y);
        quad[1].position = Vector2f(max.x, min.y);
        quad[2].position = Vector2f(max.x, max.y);
        quad[3].position = Vector2f(min.x, max.y);

        quad[0].color = color;
        quad[1].color = color;
        quad[2].color = color;
        quad[3].color = color;
        window.draw(quad);
    }
};

bool isOverlapping(AABB* box1, AABB* box2) {
    // Write your code below
        if (
        box1->max.x >= box2->min.x &&
        box2->max.x >= box1->min.x &&
        box1->max.y >= box2->min.y &&
        box2->max.y >= box1->min.y
        )
        return true;

    else
        return false;
    // Write your code above
}

AABB* box1;
AABB* box2;

void Init(sf::RenderWindow& window) {
    // initialize box1 and box2
    box1 = new AABB(Vector2f(100, 200), Vector2f(200, 250), Color(0, 0, 0, 150));
    box2 = new AABB(Vector2f(300, 100), Vector2f(500, 400), Color(0, 0, 0, 150));

    // start clocking
    g_deltaClock.restart();
    g_deltaClock.getElapsedTime();
}

void Update(sf::RenderWindow& window) {
    // calculate deltaTime
    Time currentTime = g_deltaClock.getElapsedTime();
    Time deltaTime = currentTime - g_preDeltaTime;
    float deltaSeconds = deltaTime.asSeconds();
    g_preDeltaTime = currentTime;

    float speed = 100;

    // control box1
    if (Keyboard::isKeyPressed(Keyboard::W) == true) {
        box1->min.y -= speed * deltaSeconds;
        box1->max.y -= speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::S) == true) {
        box1->min.y += speed * deltaSeconds;
        box1->max.y += speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::A) == true) {
        box1->min.x -= speed * deltaSeconds;
        box1->max.x -= speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::D) == true) {
        box1->min.x += speed * deltaSeconds;
        box1->max.x += speed * deltaSeconds;
    }

    // control box2
    if (Keyboard::isKeyPressed(Keyboard::Up) == true) {
        box2->min.y -= speed * deltaSeconds;
        box2->max.y -= speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) == true) {
        box2->min.y += speed * deltaSeconds;
        box2->max.y += speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left) == true) {
        box2->min.x -= speed * deltaSeconds;
        box2->max.x -= speed * deltaSeconds;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) == true) {
        box2->min.x += speed * deltaSeconds;
        box2->max.x += speed * deltaSeconds;
    }

    // change the color if two boxes overlaps
    if (isOverlapping(box1, box2)) {
        box1->color = Color(255, 0, 0, 150);
        box2->color = Color(255, 0, 0, 150);
    }
    else {
        box1->color = Color(0, 0, 0, 150);
        box2->color = Color(0, 0, 0, 150);
    }
}

void Render(sf::RenderWindow& window) {
    // draw box1 and box2
    box1->draw(window);
    box2->draw(window);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(win_W, win_H), "IGME209-E10");

    window.setFramerateLimit(60);

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