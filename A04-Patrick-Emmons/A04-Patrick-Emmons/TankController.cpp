#include "TankController.h"

TankController::TankController(Tank* tank)
{
	m_tank_ptr = tank; 
	tank->SetController(this);
}
