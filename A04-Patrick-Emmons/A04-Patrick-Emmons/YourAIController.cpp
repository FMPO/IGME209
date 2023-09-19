#include "YourAIController.h"
#include <queue>
#include <math.h>

void YourAIController::MakeADecision()
{
	// you can use ClassmateAIController as the reference
	// this function will be called 1 time per second
	
	// you can get the information of the game scene by calling the function of the information object
	// for example, 
	// Vector2f position = information->my_tank_position(); // get the current position of your tank, for example (250, 350)
	// Vector2u block_index = information->PositionToMapIndex(position); // get the currect block index of your tank, for example [5][6]
	information;
	
	// write your code below
	Vector2u target_map_index = Vector2u(40, 40);
	float target_rotation = 30.0f;
	bool fire_or_not = true;
	
	/*********** write your AI here *****************/
	Vector2u tank_map_index = information->my_tank_map_index();

	this->Path_Scanner(tank_map_index, distance_to_tank, 20);

	int score[80][80];

	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 80; j++) {
			score[i][j] = 0;
		}
	}

	// change the scaler
	float scaler_distance_to_center = 1.0f;
	float scaler_distance_to_tank = 1.0f;
	float scaler_fog = 2.0f;
	float scaler_enemy_tank = 3.0f;
	float scaler_health = 120.0f;
	float scaler_turret = 60.0f;
	float scaler_engine = 50.0f;
	float scaler_armor = 70.0f;
	float scaler_all = 90.0f;

	// consider distance to the center
	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 80; j++) {
			int distance = distance_to_map_center[i][j];
			if (distance == -1)
				score[i][j] -= 1000;
			else
				score[i][j] -= scaler_distance_to_center * distance;
		}
	}

	// consider fog
	int min_row = information->map_no_fog_min_row();
	int max_row = information->map_no_fog_max_row();
	int min_col = information->map_no_fog_min_column();
	int max_col = information->map_no_fog_max_column();
	int offset = 5; // keep a distance from the fog
	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 80; j++) {
			if (i < min_row + offset || i > max_row - offset || j < min_col + offset || j > max_col - offset)
				score[i][j] -= 1000;
			else {
				// may be we want to let the tank stay around the boundary of the fog? why
			}
		}
	}

	// consider distance to the tank
	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 80; j++) {
			int distance = distance_to_tank[i][j];
			if (distance == -1)
				score[i][j] -= 1000;
			else
				score[i][j] -= scaler_distance_to_tank * distance;
		}
	}

	// consider enemy tank
	vector<Vector2f> enemy_tanks = information->nearby_enenmy_tank_position();
	for (int i = 0; i < enemy_tanks.size(); i++) {
		Vector2u index = information->PositionToMapIndex(enemy_tanks[i]);
		score[index.x][index.y] -= scaler_enemy_tank;

		// Could it be better if we also adjust the score of nearby blocks? 
	}

	// consider item
	vector<Vector2f> items = information->nearby_item_position();
	vector<UpgradeItem::ITEM_TYPE> itemTypes = information->nearby_item_type();
	for (int i = 0; i < items.size(); i++) {
		Vector2u index = information->PositionToMapIndex(items[i]);
		int distance = distance_to_tank[index.x][index.y];
		switch (itemTypes[i])
		{
		case UpgradeItem::ITEM_TYPE::HEART:
			if (information->my_tank_health() + 50 <= information->my_tank_max_health()) {
				score[index.x][index.y] += scaler_health * (20 - distance);
			}
			break;
		case UpgradeItem::ITEM_TYPE::ARMOR:
			score[index.x][index.y] += scaler_armor * (20 - distance);
			break;
		case UpgradeItem::ITEM_TYPE::ENGINE:
			score[index.x][index.y] += scaler_engine * (20 - distance);
			break;
		case UpgradeItem::ITEM_TYPE::TURRET:
			score[index.x][index.y] += scaler_turret * (20 - distance);
			break;
		case UpgradeItem::ITEM_TYPE::STAR:
			score[index.x][index.y] += scaler_all * (20 - distance);
			break;
		default:
			break;
		}
		
		
	}

	// find the highest score as destination
	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 80; j++) {
			if (score[i][j] > score[target_map_index.x][target_map_index.y])
				target_map_index = Vector2u(i, j);
		}
	}


	// target to the other tank
	Vector2f tank_position = information->my_tank_position();
	if (enemy_tanks.size() > 0) {
		int closestTankIndex = 0;
		for (int i = 0; i < enemy_tanks.size(); i++) {
			if (distance_to_tank[(int)enemy_tanks[i].x][(int)enemy_tanks[i].y] < distance_to_tank[(int)enemy_tanks[closestTankIndex].x][(int)enemy_tanks[closestTankIndex].y]) {
				closestTankIndex = i;
			}
		}
		target_rotation = this->GetRotationByTarget(tank_position, enemy_tanks[closestTankIndex]);
	}
	// target to the nearest enemy?
	


	this->SetDestination(target_map_index);
	this->SetTurretRotation(target_rotation);
	is_fire_active = fire_or_not;
	// write your code above
}

void YourAIController::Start()
{
	information = new InformationYouCanGet(m_tank_ptr);
	
	// decide how you want to spend the 10 skill points to upgrade your tank
	// You can change the value below
	// the summary needs to equal to 10
	unsigned int engine_upgrade = 4;
	unsigned int armor_upgrade = 4;
	unsigned int turret_upgrade = 2;

	// give your tank a nickname
	// you can change the value below, don't be too long
	// you can set the name as "anonymous" if you want.
	name_of_my_tank = "Kazowa Supreme";
	
	// initialize the variable you defined below
	// if you don't define any new variable in the YourAIControler.h, leave it blank



	Path_Scanner(Vector2u(40, 40), distance_to_map_center, 1000);

	// initialize the variable you defined above


	m_tank_ptr->SetName(name_of_my_tank);
	m_tank_ptr->UpgradeTank(engine_upgrade, armor_upgrade, turret_upgrade); // upgrade your tank
	MakeADecision(); // make the first decision
}

void YourAIController::Path_Scanner(Vector2u source, int result[80][80], int limit)
{
	int const offset_x[4] = { -1, 1, 0, 0 }; // up down left right
	int const offset_y[4] = { 0, 0, -1, 1 }; // up down left right

	for (int i = 0; i < 80; i++) {
		for (int j = 0; j < 80; j++) {
			result[i][j] = -1; // set the initial distance as -1, which means is not walkable
		}
	}
	result[source.x][source.y] = 0; // set the distance from source to itself = 0

	// write your code blow
	queue<Vector2u> m_queue;
	bool visited[80][80] = { false };
	m_queue.push(source);
	visited[source.x][source.y] = true;

	while (m_queue.empty() == false) {
		Vector2u node = m_queue.front();
		m_queue.pop();

		if (result[node.x][node.y] > limit) // set a maxium step
			return;

		for (int k = 0; k < 4; k++) {
			Vector2u nextNode = Vector2u(node.x + offset_x[k], node.y + offset_y[k]);

			if (nextNode.x >= 0 && nextNode.y >= 0 && nextNode.x < 80 && nextNode.y < 80 && visited[nextNode.x][nextNode.y] == false) {
				if (information->GetTerrain_from_MapIndex(nextNode).tank_passable == true) {
					visited[nextNode.x][nextNode.y] = true;
					m_queue.push(nextNode);
					result[nextNode.x][nextNode.y] = result[node.x][node.y] + 1; // the distance of nextNode = the distance of node + 1 
				}
			}
		}
	}
}

float YourAIController::GetRotationByTarget(Vector2f position_tank, Vector2f position_target)
{
	Vector2f tank_to_target_direction = position_target - position_tank;
	tank_to_target_direction.y = -tank_to_target_direction.y;
	return atan2f(tank_to_target_direction.x, tank_to_target_direction.y) * 180.0f / 3.1415926f;
}
