#pragma once
#include "AIController.h"
#include <vector>

class Tank;

class ClassmateAIController :
    public AIController
{
public:
    ClassmateAIController(Tank* tank) : AIController(tank) {};
    // void Start() override;

private:
    void MakeADecision() override;
};

