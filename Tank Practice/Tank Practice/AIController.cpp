#include "AIController.h"
#include <queue>


void AIController::Update(RenderWindow& window, float deltaSeconds)
{
	m_time_to_next_decision -= deltaSeconds;
	if (m_time_to_next_decision < 0.0f) {
		MakeADecision();
	}

	MoveTowardDestination();
}

void AIController::Start()
{
	MakeADecision();
}


void AIController::MakeADecision()
{
	// generate a random valid destination
	while (true) {
		int randx = rand() % 10;
		int randy = rand() % 10;
		m_path_existing_to_destination = SetDestination(Vector2u(randx, randy));

		if (m_path_existing_to_destination == true)
			break;
	}

	m_time_to_next_decision = 2.0f;
}

void AIController::MoveTowardDestination()
{
	if (m_path_existing_to_destination == true) {
		Vector2f current_position = this->m_tank_ptr->GetPosition();

		bool arrive_destination = false;
		if (direction == MOVE_DIRECTION::LEFT && current_position.x <= m_next_destination.x) {
			arrive_destination = true;
		}
		else if (direction == MOVE_DIRECTION::RIGHT && current_position.x >= m_next_destination.x) {
			arrive_destination = true;
		}
		else if (direction == MOVE_DIRECTION::UP && current_position.y <= m_next_destination.y) {
			arrive_destination = true;
		}
		else if (direction == MOVE_DIRECTION::DOWN && current_position.y >= m_next_destination.y) {
			arrive_destination = true;
		}

		//if (distance(current_position, m_next_destination) < ERROR_RANGE) { // reach the center
		//	arrive_destination = true;
		//}

		if (arrive_destination == true) {
			Vector2u current_index = TankMap::s_instance->GetIndexByPosition(current_position); // current index
			int k = m_path[current_index.x][current_index.y]; // next direction

			if (k < 0) {
				direction = MOVE_DIRECTION::IDLE;
				return;
			}

			Vector2u next_index = current_index + Vector2u(offset_x[k], offset_y[k]); // next index
			Vector2f next_position = TankMap::s_instance->GetCenterPositionByIndex(next_index); // next center position;
			m_next_destination = next_position;

			direction = (MOVE_DIRECTION)k;
		}	
	}
}

bool AIController::SetDestination(Vector2u destination)
{
	for (int i = 0; i < MAX_MAP_SIZE; i++) {
		for (int j = 0; j < MAX_MAP_SIZE; j++) {
			m_reverse_path[i][j] = -1;
			m_path[i][j] = -1;
		}
	}

	Vector2u source = TankMap::s_instance->GetIndexByPosition(this->m_tank_ptr->GetPosition());

	bool path_existing = PathFindingBFS(source, destination);
	if (path_existing == true) {
		m_final_destination = TankMap::s_instance->GetCenterPositionByIndex(destination);
		
		
		m_next_destination = TankMap::s_instance->GetCenterPositionByIndex(source);
		
		// the tank needs to go to the center of the current block first before moving towards the target
		Vector2f tank_position = m_tank_ptr->GetPosition(); // tank position
		int k = m_path[source.x][source.y];
		if (k == 0 || k == 1) { // up down
			if (tank_position.x > m_next_destination.x) 
				direction = MOVE_DIRECTION::LEFT; // tank at the right side of the block
			else 
				direction = MOVE_DIRECTION::RIGHT; // tank at the left side of the block
		}
		else if (k == 2 || k == 3) { // left right
			if (tank_position.y < m_next_destination.y) 
				direction = MOVE_DIRECTION::DOWN; // tank is above the block
			else
				direction = MOVE_DIRECTION::UP; // tank is under the block
		}
		else {
			direction = MOVE_DIRECTION::IDLE;
		}
	}
	else {
		direction = MOVE_DIRECTION::IDLE;
	}
	return path_existing;
}

bool AIController::PathFindingBFS(Vector2u source, Vector2u destination) {
	queue<Vector2u> m_queue;
	m_queue.push(source);  // push the start point into the queue

	bool visited[MAX_MAP_SIZE][MAX_MAP_SIZE] {false}; // the node has been visited
	visited[source.x][source.y] = true;

	while (m_queue.empty() == false) {
		Vector2u nodeCurrent = m_queue.front(); // get the first node of the queue
		m_queue.pop();

		if (nodeCurrent.x == destination.x && nodeCurrent.y == destination.y) { // found the destination
			cout << "Path found :";
			PrintPath(source, destination);
			cout << endl;
			return true;
		}

		// push all adjacent nodes into the queue if not visited
		for (int k = 0; k < 4; k++) {
			Vector2u nodeNext = Vector2u(nodeCurrent.x + offset_x[k], nodeCurrent.y + offset_y[k]);

			// solution 1: calculate if the tank can go to the next node in real time
			if (TankMap::s_instance->GetTerrainByIndex(nodeNext.x, nodeNext.y).tank_passable == true 
				&& visited[nodeNext.x][nodeNext.y] == false) {
				m_queue.push(nodeNext);
				visited[nodeNext.x][nodeNext.y] = true;
				m_reverse_path[nodeNext.x][nodeNext.y] = k;
			}
		}
	}

	cout << "No path found" << endl;
	return false;
}

void AIController::PrintPath(Vector2u source, Vector2u destination)
{
	if (source.x != destination.x || source.y != destination.y) {
		int k = m_reverse_path[destination.x][destination.y];
		Vector2u one_step_back = Vector2u(destination.x - offset_x[k], destination.y - offset_y[k]);
		m_path[one_step_back.x][one_step_back.y] = k;

		PrintPath(source, one_step_back);
	}
	cout << "(" << destination.x << "," << destination.y << ") ";


}
