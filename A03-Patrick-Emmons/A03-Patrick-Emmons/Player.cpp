#include "Player.h"

Player::Player(Texture* playerTexture_ptr, Texture* healthTexture_ptr, Vector2f position)
{
    m_playerSprite.setTexture(*playerTexture_ptr); 
    m_healthSprite.setTexture(*healthTexture_ptr);
    m_healthSprite.setTextureRect(sf::IntRect(0, 0, 128, 32));

    // init origin
    m_playerSprite.setOrigin(playerTexture_ptr->getSize().x / 2.0f, playerTexture_ptr->getSize().y / 2.0f);
    m_healthSprite.setOrigin(0, 0);

    // init position
    m_playerSprite.setPosition(position);
    m_healthSprite.setPosition(50, 50);

    // init rotation
    m_playerSprite.setRotation(0);
    m_healthSprite.setRotation(0);

    // init scale
    m_playerSprite.setScale(2, 2);
    m_healthSprite.setScale(4, 4);
}


Player::~Player()
{
}

void Player::Update(RenderWindow& window, float deltaSeconds)
{

    int health = 4;  




    if (m_is_heal_button_down == false && Keyboard::isKeyPressed(Keyboard::H)) {
        this->Heal(window);
    }
    m_is_heal_button_down = Keyboard::isKeyPressed(Keyboard::H);

    if (m_is_attack_button_down == false && Keyboard::isKeyPressed(Keyboard::A)) {
        this->Attack(window);
    }
    m_is_attack_button_down = Keyboard::isKeyPressed(Keyboard::A);
}

void Player::Render(RenderWindow& window)
{
    window.draw(m_playerSprite);
    window.draw(m_healthSprite);
}

void Player::Heal(RenderWindow& window) {
    if (m_healthIndex > 0) {
        m_healthIndex--;
        m_healthSprite.setTextureRect(sf::IntRect(m_healthIndex*128, 0, 128, 32));
    }
    
}

void Player::Attack(RenderWindow& window) {
    if (m_healthIndex < m_maxHealthIndex) {
        m_healthIndex++;
        m_healthSprite.setTextureRect(sf::IntRect(m_healthIndex * 128, 0, 128, 32));
    }
}