#include "ViewManager.h"

ViewManager* ViewManager::s_instance = nullptr;

ViewManager::ViewManager(RenderWindow& window, TankMap* tankMap_ptr, Tank* tank_ptr)
{
    s_instance = this;

    m_full_view = window.getDefaultView();
    m_full_view.setSize(tankMap_ptr->GetMapSizePixel());
    m_full_view.setCenter(tankMap_ptr->GetMapSizePixel() / 2.0f);

    window.setView(m_full_view);
    m_view_type = VIEW_TYPE::FREE;

    m_tank = tank_ptr;

    font.loadFromFile("Assets/Fonts/arial.ttf");
}

void ViewManager::Update(RenderWindow& window, float deltaSeconds)
{
    if (m_is_full_camera_button_down == false && Keyboard::isKeyPressed(Keyboard::C)) {
        if (m_view_type == VIEW_TYPE::FOCUS) {
            window.setView(m_full_view);
            m_view_type = VIEW_TYPE::FREE;
        }
        else if (m_view_type == VIEW_TYPE::FREE) {
            m_view_type = VIEW_TYPE::FOCUS;
        }
    }

    if (m_view_type == VIEW_TYPE::FOCUS) {
        View view = window.getDefaultView();
        view.setCenter(m_tank->GetPosition());
        view.setSize(view.getSize() * 2.0f);
        window.setView(view);
    }

    m_is_full_camera_button_down = Keyboard::isKeyPressed(Keyboard::C);
}

void ViewManager::Render(RenderWindow& window)
{
    Text text;
    text.setFont(font);
    string name = m_tank->GetName();
    string hp = "HP: " + to_string((int)m_tank->GetHealth()) + "/" + to_string((int)m_tank->GetMaxHealth());
    string move_speed = "Movement Speed: " + to_string((int)m_tank->GetSpeed());
    string attack_speed = "Attack Speed: " + to_string(m_tank->GetReloadTime());

    text.setString(
        name + "\n"
        + hp + "\n"
        + move_speed + "\n"
        + attack_speed
    );

    if (m_view_type == VIEW_TYPE::FREE)
        text.setCharacterSize(200);
    else {
        text.setCharacterSize(64);
        text.setPosition(window.getView().getCenter() - window.getView().getSize() / 2.0f);
    }

    window.draw(text);
}

View ViewManager::GetFullView()
{
    return m_full_view;
}
