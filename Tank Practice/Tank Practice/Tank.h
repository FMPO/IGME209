#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TankMap.h"
#include "TankController.h"
#include "Bullet.h"

using namespace std;
using namespace sf;

class TankController;

class Tank {
public:
	bool is_active = true;

private:
	Sprite m_baseSprite;
	Sprite m_turretSprite;

	float m_move_speed = 100.0f;
	int m_health = 100;
	int m_max_health = 100;

	TankController* m_controller = nullptr;

	float m_turretRoloadTotalTime = 0.25f;
	float m_turretRoloadLeftTime = 0.0f;

	// circle bounding volume
	float m_bounding_radius = 32.0f;

	Vector2f m_tankSize = Vector2f(64, 64);

	int m_tankID;

	Sprite m_health_sprite;
	Sprite m_health_empty_sprite;

	Vector2f m_health_bar_size = Vector2f(48, 4);
	Vector2f m_health_bar_offset = Vector2f(-24, -40);

public:
	Tank(Color color, Vector2f position, int tankID);
	~Tank();
	void Render(RenderWindow& window);
	void Update(RenderWindow& window, float deltaSeconds);
	void SetController(TankController* controller);

	Vector2f GetPosition();
	bool CheckGetHit(Bullet* bullet);

	void UpgradeTank(int engine, int armor, int turret);

private:
	void Fire();
};