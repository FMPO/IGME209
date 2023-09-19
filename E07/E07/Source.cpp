#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void Render(sf::RenderWindow& window) {
    //draw foot (left)
    sf::CircleShape footLeft(40.f, 60);
    footLeft.setFillColor(sf::Color(255, 20, 71));
    footLeft.setPosition(220.f, 680.f);
    footLeft.setScale(2.f, 2.f);
    footLeft.scale(3.f, 2.f);
    footLeft.rotate(10.f);
    window.draw(footLeft);

    //draw foot (right)
    sf::CircleShape footRight(40.f, 60);
    footRight.setFillColor(sf::Color(255, 20, 71));
    footRight.setPosition(720.f, 760.f);
    footRight.setScale(2.f, 2.f);
    footRight.scale(3.f, 2.f);
    footRight.rotate(350.f);
    window.draw(footRight);

    // draw the arm (left)
    sf::CircleShape armLeft(60.f, 50);
    armLeft.setFillColor(sf::Color(255, 131, 189));
    armLeft.setPosition(200.f, 360.f);
    armLeft.setScale(3.f, 2.f);
    armLeft.rotate(20.f);
    window.draw(armLeft);

    // draw the arm (right)
    sf::CircleShape armRight(60.f, 50);
    armRight.setFillColor(sf::Color(255, 131, 189));
    armRight.setPosition(870.f, 440.f);
    armRight.setScale(3.f, 2.f);
    armRight.rotate(340.f);
    window.draw(armRight);

    // draw the body
    sf::CircleShape body(400.f, 50);
    body.setFillColor(sf::Color(255, 131, 189));
    body.setPosition(300.f, 150.f);
    window.draw(body);

    //eyes
    sf::CircleShape eyeLeft(50.f, 50);
    eyeLeft.setFillColor(sf::Color(0, 0, 0));
    eyeLeft.setPosition(530.f, 350.f);
    eyeLeft.setScale(1.f, 1.f);
    eyeLeft.scale(1.f, 2.f);
    window.draw(eyeLeft);

    sf::CircleShape eyeRight(50.f, 50);
    eyeRight.setFillColor(sf::Color(0, 0, 0));
    eyeRight.setPosition(740.f, 350.f);
    eyeRight.setScale(1.f, 1.f);
    eyeRight.scale(1.f, 2.f);
    window.draw(eyeRight);

    //iris
    sf::CircleShape irisLeft(40.f, 50);
    irisLeft.setFillColor(sf::Color(0, 81, 255));
    irisLeft.setPosition(540.f, 370.f);
    irisLeft.setScale(1.f, 1.f);
    irisLeft.scale(1.f, 2.f);
    window.draw(irisLeft);

    sf::CircleShape irisRight(40.f, 50);
    irisRight.setFillColor(sf::Color(0, 81, 255));
    irisRight.setPosition(750.f, 370.f);
    irisRight.setScale(1.f, 1.f);
    irisRight.scale(1.f, 2.f);
    window.draw(irisRight);

    //pupils
    sf::CircleShape pupilsLeft(40.f, 50);
    pupilsLeft.setFillColor(sf::Color(0, 0, 0));
    pupilsLeft.setPosition(540.f, 350.f);
    pupilsLeft.setScale(1.f, 1.f);
    pupilsLeft.scale(1.f, 2.f);
    window.draw(pupilsLeft);

    sf::CircleShape pupilsRight(40.f, 50);
    pupilsRight.setFillColor(sf::Color(0, 0, 0));
    pupilsRight.setPosition(750.f, 350.f);
    pupilsRight.setScale(1.f, 1.f);
    pupilsRight.scale(1.f, 2.f);
    window.draw(pupilsRight);

    //shines
    sf::CircleShape shineLeft(20.f, 50);
    shineLeft.setFillColor(sf::Color(255, 255, 255));
    shineLeft.setPosition(560.f, 370.f);
    shineLeft.setScale(1.f, 1.f);
    shineLeft.scale(1.f, 2.f);
    window.draw(shineLeft);

    sf::CircleShape shineRight(20.f, 50);
... (55 lines left)