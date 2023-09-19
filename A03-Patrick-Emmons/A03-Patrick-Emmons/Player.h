#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Player {
private:
	Sprite m_playerSprite;
	Sprite m_healthSprite;


	int m_healthIndex = 0;
	const int m_maxHealthIndex = 4;

	bool m_is_heal_button_down = false;
	bool m_is_attack_button_down = false;

public:
	Player(Texture* playerTexture_ptr, Texture* healthTexture_ptr, Vector2f position);
	~Player();
	void Render(RenderWindow& window);
	void Update(RenderWindow& window, float deltaSeconds);

	void Heal(RenderWindow& window);
	void Attack(RenderWindow& window);
};
