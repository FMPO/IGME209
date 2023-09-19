#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "TankMap.h"
#include "Tank.h"

using namespace std;
using namespace sf;

class ViewManager
{
public:
	static ViewManager* s_instance;
private:
	View m_full_view;

	bool m_is_full_camera_button_down = false;

	enum class VIEW_TYPE {
		FOCUS = 0,
		FREE = 1
	};

	VIEW_TYPE m_view_type = VIEW_TYPE::FOCUS;
	Tank* m_tank;

	Font font;
public:
	ViewManager(RenderWindow& window, TankMap* tankMap_ptr, Tank* tank_ptr);
	void Update(RenderWindow& window, float deltaSeconds);
	void Render(RenderWindow& window);
	View GetFullView();
};

