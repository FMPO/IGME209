#pragma once
#include "TankController.h"

class PlayerController :
    public TankController
{
public:
	PlayerController(Tank* tank) : TankController(tank) {};
    void Update(RenderWindow& window, float deltaSeconds) override;
	void Start() override;

private:
    bool m_is_fire_button_down = false;
	bool m_is_camera_switch_button_down = false;

	enum class VIEW_TYPE {
		FOCUS = 0,
		FREE = 1
	};

	VIEW_TYPE m_view_type = VIEW_TYPE::FREE;
};

