#include <stdio.h>
#include <iostream>

using namespace std;

class Enemy abstract {
protected:
	string name;
	int life;
	int attack_power;
public:
	virtual int Attack() {
		cout << name << " Attack! " << attack_power << endl;
		return attack_power;
	}
	virtual void GetHit(int _attack_power) {
		life -= _attack_power;
		cout << name << " get hit" << " life = " << life << endl;
		if (life <= 0) {
			cout << name << " died" << endl;
		}
	}
	virtual void Move(float _distance) {
		cout << name << " moved " << _distance << endl;
	};
};

class Goblin : public Enemy {
public:
	Goblin() {
		name = "Goblin";
		life = 10;
		attack_power = 5;
	}
	~Goblin() {};
};

class Troll : public Enemy {
public:
	Troll() {
		name = "Troll";
		life = 50;
		attack_power = 15;
	}
	~Troll() {};
};

class Dragon : public Enemy {
public:
	Dragon() {
		name = "Dragon";
		life = 150;
		attack_power = 50;
	}
	~Dragon() {};
	void Move(float _distance) override {
		cout << name << " fly " << _distance << endl;
	}
};

//delete the number on the method name you want to run, and add one to the main methods you dont want to run
int main2() {
	Enemy* enemy_arr[3];
	enemy_arr[0] = new Goblin();
	enemy_arr[1] = new Troll();
	enemy_arr[2] = new Dragon();

	for (int i = 0; i < 3; i++) {
		enemy_arr[i]->Attack();
		enemy_arr[i]->Move(2.0f);
	}

	enemy_arr[0]->GetHit(enemy_arr[2]->Attack());

	return 0;
}