#include "ClassmateAIController.h"
#include <queue>

void ClassmateAIController::MakeADecision()
{
	// here is an example of how to get information from the information object
	Vector2f position = information->my_tank_position(); // get the current position of your tank, for example (250, 350)
	Vector2u block_index = information->PositionToMapIndex(position); // get the currect block index of your tank, for example [5][6]


	// generate a new random destination
	while (true) {
		int randx = 35 + rand() % 10;
		int randy = 35 + rand() % 10;
		
		// find a path to the destination
		bool find_path = this->SetDestination(Vector2u(randx, randy));

		if (find_path == true)
			break;	
	}

	// generate a new random rotation target
	int rotation = rand() % 360;
	this->SetTurretRotation(rotation);
}