#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TankMap.h"
#include "Tank.h"

using namespace std;
using namespace sf;

class Tank;

class TankController {
public:
	bool is_fire_active = false;

	enum class MOVE_DIRECTION {
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3,
		IDLE = 4,
	};

	MOVE_DIRECTION direction = MOVE_DIRECTION::IDLE;

	TankController(Tank* tank);
	virtual void Update(RenderWindow& window, float deltaSeconds) = 0;
	virtual void Start() = 0;

protected:
	Tank* m_tank_ptr;
};