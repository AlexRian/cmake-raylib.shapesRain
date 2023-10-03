#include <stdio.h>
#include <vector>
#include <thread>
#include "raylib.h"
#include "./engine/headers/debug.hpp"
#include "./engine/headers/physics.hpp"
#include "./settings.hpp"
#include "./entities.hpp"

void generateBoxes(Physics* physics, std::vector<Block*>* boxes)
{
    for (size_t i = 0; i < 100; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (!physics->getWorld()->IsLocked()) {
            Block* box = new Block{
                Settings::screenWidth / 2, 90, 90,
                physics->getBody("Block", Settings::screenWidth / 2, 200.0f, 90, 20, 20, true, Box, {.5f, 0.3f, 0})
            };

            boxes->push_back(box);
        }
    }
}

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Game");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    Physics physics{ b2Vec2{0.f, 9.8f} };

    std::vector<Block*> boxes;

    Ground ground{ 
        Settings::screenWidth / 2, Settings::screenHeight, 180,
        physics.getBody("Ground", Settings::screenWidth / 2, Settings::screenHeight, 180, Settings::screenWidth, 60, false, Box, {0.1f, 0.1f, 0.1f})
    };

    std::thread boxesGeneratorThread(generateBoxes, &physics, &boxes);

    while (!WindowShouldClose())
    {
        physics.makeWorldStep();

        for each (Block* box in boxes)
        {
            box->applyPhysicsPosition();
        }

        ground.applyPhysicsPosition();

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for each (Block * box in boxes)
            {
                box->draw();
            }
            ground.draw();
            debug.draw();
        EndDrawing();
    }

    for each (Block* box in boxes)
    {
        delete box;
    }

    CloseWindow();

    return 0;
}