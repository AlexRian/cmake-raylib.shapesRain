#include <stdio.h>
#include <vector>
#include <thread>
#include "raylib.h"
#include "./engine/headers/debug.hpp"
#include "./engine/headers/physics.hpp"
#include "./settings.hpp"
#include "./entities.hpp"

int main(void)
{
    InitWindow(Settings::screenWidth, Settings::screenHeight, "Game");
    SetTargetFPS(Settings::fps);

    Debug debug{ 0, 0, false };
    Physics physics{ b2Vec2{0.f, 9.8f} };

    std::vector<Block*> boxes;

    Ground bottom{ 
        Settings::screenWidth / 2, Settings::screenHeight - 200, 180,
        physics.getBody("Ground", Settings::screenWidth / 2, Settings::screenHeight - 200, 180, 200, 30, false, Box, {0.1f, 0.1f, 0.1f})
    };

    Wall leftWall{
        Settings::screenWidth / 2 - 100, Settings::screenHeight - 300, 90,
        physics.getBody("Wall", Settings::screenWidth / 2 - 100, Settings::screenHeight - 300, 180, 30, 200, false, Box, {0.1f, 0.1f, 0.1f})
    };

    Wall rightWall{
        Settings::screenWidth / 2 + 100, Settings::screenHeight - 300, 90,
        physics.getBody("Wall", Settings::screenWidth / 2 + 100, Settings::screenHeight - 300, 180, 30, 200, false, Box, {0.1f, 0.1f, 0.1f})
    };

    while (!WindowShouldClose())
    {
        if (boxes.size() < 300) {
            Block* box = new Block{
                Settings::screenWidth / 2, 90, 90,
                physics.getBody("Block", Settings::screenWidth / 2, 0, 90, 10, 10, true, Box, {.5f, 0.3f, 0})
            };

            boxes.push_back(box);
        }

        physics.makeWorldStep();

        for each (Block* box in boxes)
        {
            box->applyPhysicsPosition();
        }

        bottom.applyPhysicsPosition();
        leftWall.applyPhysicsPosition();
        rightWall.applyPhysicsPosition();

        if (boxes.size() > 299) {
            bottom.makeOpenAnimationStep();
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            for each (Block * box in boxes)
            {
                box->draw();
            }
            bottom.draw();
            leftWall.draw();
            rightWall.draw();
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