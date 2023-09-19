#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tank.h"     
#include "TankMap.h"  
#include "TankController.h"
#include "PlayerController.h"
#include "AIController.h"
#include "ClassmateAIController.h"
#include "ViewManager.h"
#include "UpgradeItem.h"
#include "InformationYouCanGet.h"
#include "YourAIController.h"
#include <fstream>

using namespace std;

ViewManager* g_viewManager; // view managere

Tank* g_tank_ptr;       // tank pointer
TankMap* g_map_ptr;     // map pointer

vector<Tank*> g_classmate_tank_array;
int g_classmate_number = 10; // how many enemy tank in the map, you can change this variable for debugging

// deltaTime
Time g_preTime;         // the ElapsedTime of last frame
Clock g_deltaClock;     // the clock used to get the ElapsedTime

BulletManager* g_bullet_manager; // manage all bullets
UpgradeItemManager* g_item_manager; // manage all items

bool const g_keyboard_or_ai_control = false; // true = keyboard control, false = ai control

// used to random start position
vector<Vector2u> g_start_positions;

#pragma region Initialization

Vector2u GetARandomStartPositionIndex() {
    if (g_start_positions.size() == 0)
        return Vector2u(0, 0);
    else {
        int n = rand() % g_start_positions.size();
        Vector2u v = g_start_positions[n];
        g_start_positions.erase(g_start_positions.begin() + n);
        return v;
    }
}

void InitPlayerTank(sf::RenderWindow& window) {
    Vector2f position = g_map_ptr->GetCenterPositionByIndex(GetARandomStartPositionIndex());

    g_tank_ptr = new Tank(Color::White, position, 0, "Player");
    TankController* tank_controller_ptr;
    if (g_keyboard_or_ai_control == true) {
        tank_controller_ptr = new PlayerController(g_tank_ptr);
    }
    else {
        tank_controller_ptr = new YourAIController(g_tank_ptr);
    }
    tank_controller_ptr->Start();
}
void InitClassmate(sf::RenderWindow& window) {
    for (int i = 0; i < g_classmate_number; i++) {
        Vector2f position = g_map_ptr->GetCenterPositionByIndex(GetARandomStartPositionIndex());

        Tank* tank_ptr = new Tank(Color::Red, position, i + 1, "Classmate" + to_string(i + 1));
        ClassmateAIController* controller_ptr = new ClassmateAIController(tank_ptr);
        controller_ptr->Start();

        g_classmate_tank_array.push_back(tank_ptr);
    }
}
void InitMap(sf::RenderWindow& window) {
    // create and load the game map
    g_map_ptr = new TankMap("Maps/level1.txt");

    g_item_manager = new UpgradeItemManager();

    for (int i = 0; i < g_map_ptr->GetMapSize().x; i++) {
        for (int j = 0; j < g_map_ptr->GetMapSize().y; j++) {
            if (g_map_ptr->GetTerrainByIndex(i, j).name == "dirt3") {
                g_start_positions.push_back(Vector2u(i, j));
            }
        }
    }
}
void InitClock(sf::RenderWindow& window) {
    // let the clock start to clocking the time 
    g_deltaClock.restart();
    g_preTime = g_deltaClock.getElapsedTime(); // set the default value of previous time
}

void InitView(RenderWindow& window) {
    g_viewManager = new ViewManager(window, g_map_ptr, g_tank_ptr);
}

// initialization
void Init(sf::RenderWindow& window) {
    srand(time(NULL));
    InitMap(window);
    InitPlayerTank(window);
    InitClassmate(window);
    InitView(window);
    InitClock(window);

    g_bullet_manager = new BulletManager();
}
#pragma endregion

#pragma region Update
float UpdateDeltaTime() {
    Time currentTime = g_deltaClock.getElapsedTime();   // get the current time
    Time deltaTime = currentTime - g_preTime;           // calculate the delta time
    float deltaSeconds = deltaTime.asSeconds();         // time to seconds
    g_preTime = currentTime;                            // the current time become the preTime for next frame

    return deltaSeconds;
}
// update game logic
void Update(sf::RenderWindow& window) {
    float deltaSeconds = UpdateDeltaTime();

    deltaSeconds = 0.01f;

    for (int i = 0; i < g_classmate_tank_array.size(); i++)
        g_classmate_tank_array[i]->Update(window, deltaSeconds);

    if (g_keyboard_or_ai_control == false)
        ((AIController*)g_tank_ptr->GetController())->UpdateAllInformation(g_classmate_tank_array, g_item_manager->item_array, g_bullet_manager->bullet_array);

    g_tank_ptr->Update(window, deltaSeconds);       // update the tank

    g_bullet_manager->Update(window, deltaSeconds);
    g_viewManager->Update(window, deltaSeconds);
    g_map_ptr->Update(window, deltaSeconds);
    g_item_manager->Update(window, deltaSeconds);

    // check bullet
    for (int i = 0; i < g_bullet_manager->bullet_array.size(); i++) {
        Bullet* bullet = g_bullet_manager->bullet_array[i];
        g_tank_ptr->CheckGetHit(bullet);

        for (int j = 0; j < g_classmate_tank_array.size(); j++) {
            g_classmate_tank_array[j]->CheckGetHit(bullet);
        }
    }

    // eat item
    for (int i = 0; i < g_item_manager->item_array.size(); i++) {
        UpgradeItem* item = g_item_manager->item_array[i];
        g_tank_ptr->CheckEatItem(item);

        for (int j = 0; j < g_classmate_tank_array.size(); j++) {
            g_classmate_tank_array[j]->CheckEatItem(item);
        }
    }
}
#pragma endregion

// render the game scene
void Render(sf::RenderWindow& window) {
    g_map_ptr->Render(window);      // draw the map

    // draw other tank
    for (int i = 0; i < g_classmate_tank_array.size(); i++)
        g_classmate_tank_array[i]->Render(window);

    g_tank_ptr->Render(window);      // draw the tank

    g_item_manager->Render(window);

    g_bullet_manager->Render(window);

    g_viewManager->Render(window);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 960), "Tank Campionship"); // create a window
    window.setFramerateLimit(120);

    Init(window); // initialization

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0)); // clear the window with color(0,0,0)

        Update(window); // update game logic
        Render(window); // draw the game scene

        window.display(); // display the window
    }

    return 0;
}