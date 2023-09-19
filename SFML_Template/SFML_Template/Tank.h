#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Tank {
private:
	Sprite m_baseSprite;
	Sprite m_turretSprite;

	float m_move_speed = 100.0f;
	float m_turret_rotate_speed = 120.0f;

	int m_health = 5;

	bool m_is_fire_button_down = false;

public:
	Tank(Texture* baseTexture_ptr, Texture* turretTexture_ptr, Vector2f position);
	~Tank();
	void Render(RenderWindow& window);
	void Update(RenderWindow& window, float deltaSeconds);

	void Fire();
};