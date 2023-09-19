#pragma once
#include "AIController.h"
#include <vector>

#define MAX_MAP_SIZE 100
#define ERROR_RANGE 10.0f

class Tank;

class YourAIController :
    public AIController
{
public:
    YourAIController(Tank* tank) : AIController(tank) {};

private:
    void MakeADecision() override;
public:
    void Start() override;
    
private:
    // define your own variables below
    int distance_to_map_center[80][80]; // center as 40, 40
    int distance_to_tank[80][80]; // range as 21
    // define your own variables above

    void Path_Scanner(Vector2u source, int result[80][80], int limit);
    float GetRotationByTarget(Vector2f position_tank, Vector2f position_target);
};


