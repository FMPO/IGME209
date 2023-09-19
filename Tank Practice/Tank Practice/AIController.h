#pragma once
#include "TankController.h"
#include <vector>

#define MAX_MAP_SIZE 100
#define ERROR_RANGE 5.0f

class AIController :
    public TankController
{
public:
    AIController(Tank* tank) : TankController(tank) {};
    void Update(RenderWindow& window, float deltaSeconds) override;
    void Start() override;

private:    
    int const offset_x[4] = { -1, 1, 0, 0 }; // up down left right
    int const offset_y[4] = { 0, 0, -1, 1 }; // up down left right

    int m_reverse_path[MAX_MAP_SIZE][MAX_MAP_SIZE]{ -1 };
    int m_path[MAX_MAP_SIZE][MAX_MAP_SIZE]{ -1 };

    Vector2f m_next_destination;    // index of next destination
    Vector2f m_final_destination;   // index of current destination
    bool m_path_existing_to_destination;

    float m_time_to_next_decision = 0.0f;

private:
    void MoveTowardDestination();
    bool SetDestination(Vector2u destination); // set a new destination, return true if there exsit a path, path will be saved in m_path
    
    bool PathFindingBFS(Vector2u source, Vector2u destination);
    void PrintPath(Vector2u source, Vector2u destination);
    void MakeADecision();
};

