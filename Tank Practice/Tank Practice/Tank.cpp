#include "Tank.h"

Tank::Tank(Color color, Vector2f position, int tankID)
{
    // create textures
    Texture* baseTexture_ptr = new Texture();
    baseTexture_ptr->loadFromFile("Images/tankBase.png"); // load tank base textures
    Texture* turretTexture_ptr = new Texture();
    turretTexture_ptr->loadFromFile("Images/tankTurret.png"); // load tank turret textures

    m_baseSprite.setTexture(*baseTexture_ptr); // assign the base texture to base sprite
    m_turretSprite.setTexture(*turretTexture_ptr); // assign the turretTexture to turret sprite

    // init origin
    m_baseSprite.setOrigin(baseTexture_ptr->getSize().x / 2.0f, baseTexture_ptr->getSize().y / 2.0f);
    m_turretSprite.setOrigin(turretTexture_ptr->getSize().x / 2.0f, turretTexture_ptr->getSize().y / 2.0f);

    // init position
    m_baseSprite.setPosition(position);
    m_turretSprite.setPosition(position);

    // init rotation
    m_baseSprite.setRotation(0);
    m_turretSprite.setRotation(0);

    // init scale
    m_baseSprite.setScale(m_tankSize.x / baseTexture_ptr->getSize().x, m_tankSize.y / baseTexture_ptr->getSize().y);
    m_turretSprite.setScale(m_tankSize.x / baseTexture_ptr->getSize().x, m_tankSize.y / baseTexture_ptr->getSize().y);

    // set color
    m_baseSprite.setColor(color);
    m_turretSprite.setColor(color);

   
    Texture* healthTexture_ptr = new Texture();
    healthTexture_ptr->loadFromFile("Images/health.png");
    Texture* healthEmptyTexture_ptr = new Texture();
    healthEmptyTexture_ptr->loadFromFile("Images/health_empty.png");

    m_health_sprite.setTexture(*healthTexture_ptr);
    m_health_empty_sprite.setTexture(*healthEmptyTexture_ptr);

    m_health_sprite.setScale((float)m_health / m_max_health * m_health_bar_size.x / healthTexture_ptr->getSize().x, 
        m_health_bar_size.y / healthTexture_ptr->getSize().y);
    m_health_empty_sprite.setScale(m_health_bar_size.x / healthTexture_ptr->getSize().x, m_health_bar_size.y / healthTexture_ptr->getSize().y);

    m_health_sprite.setPosition(position + m_health_bar_offset);
    m_health_empty_sprite.setPosition(position + m_health_bar_offset);

    m_tankID = tankID;
}

Tank::~Tank()
{
}

void Tank::Render(RenderWindow& window)
{
    window.draw(m_baseSprite);// draw the base sprite

    if (is_active == true)
        window.draw(m_turretSprite);// draw the base sprite 

    window.draw(m_health_empty_sprite);
    window.draw(m_health_sprite);
}

void Tank::Update(RenderWindow& window, float deltaSeconds)
{
    if (is_active == false)
        return;

    m_controller->Update(window, deltaSeconds);

    Vector2f movement = Vector2f(0, 0);
    float rotation = m_baseSprite.getRotation();

    if (m_controller->direction == TankController::MOVE_DIRECTION::UP) {
        rotation = 0;
        movement.y -= m_move_speed * deltaSeconds;
    }
    else if (m_controller->direction == TankController::MOVE_DIRECTION::DOWN) {
        rotation = 180;
        movement.y += m_move_speed * deltaSeconds;
    }
    else if (m_controller->direction == TankController::MOVE_DIRECTION::LEFT) {
        rotation = -90;
        movement.x -= m_move_speed * deltaSeconds;
    }
    else if (m_controller->direction == TankController::MOVE_DIRECTION::RIGHT) {
        rotation = 90;
        movement.x += m_move_speed * deltaSeconds;
    }

    Vector2f newPosition = m_baseSprite.getPosition() + movement;
    if (TankMap::s_instance->CheckRectTankPassable(newPosition, Vector2f(m_baseSprite.getTexture()->getSize()) * m_baseSprite.getScale().x)) {
        m_baseSprite.setPosition(newPosition);
        m_turretSprite.setPosition(newPosition);

        m_health_sprite.setPosition(newPosition + m_health_bar_offset);
        m_health_empty_sprite.setPosition(newPosition + m_health_bar_offset);
    }

    // set rotation
    m_baseSprite.setRotation(rotation);
    m_turretSprite.setRotation(rotation);

    // fire!
    m_turretRoloadLeftTime -= deltaSeconds;
    if (m_controller->is_fire_active) {
        this->Fire();
    }
}

void Tank::SetController(TankController* controller)
{
    m_controller = controller;
}

Vector2f Tank::GetPosition()
{
    return m_baseSprite.getPosition();
}

float distance(Vector2f v1, Vector2f v2) {
    return sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

bool Tank::CheckGetHit(Bullet* bullet)
{
    if (bullet->GetTankID() == m_tankID)
        return false;
    else {
        if (distance(this->GetPosition(), bullet->GetPosition()) < m_bounding_radius) { // a sphere bounding volume
            m_health -= bullet->GetPower();
            if (m_health <= 0) { // life <= 0
                m_health = 0;
                is_active = false;
                m_baseSprite.setColor(Color(50, 50, 50));
            }

            // update the health bar
            m_health_sprite.setScale((float)m_health / m_max_health * m_health_bar_size.x / m_health_sprite.getTexture()->getSize().x,
                m_health_bar_size.y / m_health_sprite.getTexture()->getSize().y);

            // set the active of bullet to be false
            bullet->is_active = false;
        }
    }
}

void Tank::UpgradeTank(int engine, int armor, int turret)
{
    if (engine + armor + turret > 10)
        return;
    m_move_speed += 5.0f * engine;
    
    m_max_health += 10 * armor;
    m_health = m_max_health;

    m_turretRoloadTotalTime -= 0.0125f * turret;
}

void Tank::Fire()
{
    if (m_turretRoloadLeftTime <= 0.0f) {
        Bullet* bullet = new Bullet(m_turretSprite.getPosition(), m_turretSprite.getRotation(), m_tankID);
        m_turretRoloadLeftTime = m_turretRoloadTotalTime;
    }
}
