#include <raylib.h>
#include <raymath.h>
#include "Prop.h"
#include "Enemy.h"
#include <string>
#include <stdio.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    const int windowWidth = 648;
    const int windowHeight = 550;
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map{LoadTexture("textures/map.png")};
    Vector2 mapPos{0.0, 0.0};
    const int mapScale = 3.0;

    Prop props[2]
    {
        Prop{Vector2{600, 800}, LoadTexture("textures/Classy+Clash+Sprites/nature_tileset/Rock.png")},
        Prop{Vector2{900, 1500}, LoadTexture("textures/Classy+Clash+Sprites/nature_tileset/Log.png")}
    };
    
    Character knight{windowWidth, windowHeight};

    Enemy goblin1{Vector2{(float)(rand()%((mapScale * map.width+100) - 100)), (float)(rand()%(mapScale * map.height+100) - 100)}, LoadTexture("textures/Classy+Clash+Sprites/characters/goblin_idle_spritesheet.png"), LoadTexture("textures/Classy+Clash+Sprites/characters/goblin_run_spritesheet.png")};
    Enemy goblin2{Vector2{(float)(rand()%(mapScale * map.width+100) - 100), (float)(rand()%(mapScale * map.height+100) - 100)}, LoadTexture("textures/Classy+Clash+Sprites/characters/goblin_idle_spritesheet.png"), LoadTexture("textures/Classy+Clash+Sprites/characters/goblin_run_spritesheet.png")};
    Enemy goblin3{Vector2{(float)(rand()%(mapScale * map.width+100) - 100), (float)(rand()%(mapScale * map.height+100) - 100)}, LoadTexture("textures/Classy+Clash+Sprites/characters/goblin_idle_spritesheet.png"), LoadTexture("textures/Classy+Clash+Sprites/characters/goblin_run_spritesheet.png")};
    Enemy slime1{Vector2{(float)(rand()%(mapScale * map.width+100) - 100), (float)(rand()%(mapScale * map.height+100) - 100)}, LoadTexture("textures/Classy+Clash+Sprites/characters/slime_idle_spritesheet.png"), LoadTexture("textures/Classy+Clash+Sprites/characters/slime_run_spritesheet.png")};
    Enemy slime2{Vector2{(float)(rand()%(mapScale * map.width+100) - 100), (float)(rand()%(mapScale * map.height+100) - 100)}, LoadTexture("textures/Classy+Clash+Sprites/characters/slime_idle_spritesheet.png"), LoadTexture("textures/Classy+Clash+Sprites/characters/slime_run_spritesheet.png")};
    Enemy slime3{Vector2{(float)(rand()%(mapScale * map.width+100) - 100), (float)(rand()%(mapScale * map.height+100) - 100)}, LoadTexture("textures/Classy+Clash+Sprites/characters/slime_idle_spritesheet.png"), LoadTexture("textures/Classy+Clash+Sprites/characters/slime_run_spritesheet.png")};

    int numOfEnemies{6}, counter{};

    Enemy* enemies[]
    {
        &goblin1,
        &goblin2,
        &goblin3,
        &slime1,
        &slime2,
        &slime3
    };

    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while(!WindowShouldClose()) 
    {
        const float dT{GetFrameTime()};

        //begin drawing
        BeginDrawing();
        ClearBackground(WHITE);

        //to move the map in the correct direction, we have to move it in the opposite direction that we move our character
        mapPos = Vector2Scale(knight.GetWorldPos(), -1.f);
        //drawing a map
        DrawTextureEx(map, mapPos, 0.f, mapScale, WHITE);

        for(auto prop : props)
        {
            prop.RenderProp(knight.GetWorldPos());
        }

        if(!knight.Alive())
        {
            DrawText("GAME OVER!", knight.GetScreenPos().x-50, knight.GetScreenPos().y, 30, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knighstHealth = "Health: ";
            knighstHealth.append(std::to_string(knight.getHealth()));
            DrawText(knighstHealth.c_str(), 55, 45, 40, RED);
        }

        if(counter == numOfEnemies)
        {
            DrawText("YOU WIN!", knight.GetScreenPos().x-40, knight.GetScreenPos().y+10, 40, RED);
            EndDrawing();
            continue;
        }

        for(auto enemy : enemies)
        {
            enemy->Tick(dT);
        }

        knight.Tick(dT);

        //check map bounds
        if(knight.GetWorldPos().x < 0 ||
           knight.GetWorldPos().y < 0 ||
           knight.GetWorldPos().x + windowWidth > map.width * mapScale ||
           knight.GetWorldPos().y + windowHeight+60 > map.height * mapScale)
        {
            knight.UndoMovement();
        }

        //collision
        for(auto prop : props)
        {
            if(CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.GetWorldPos())))
                knight.UndoMovement();
        }

        //end drawing
        EndDrawing();

        for(auto enemy : enemies)
        {
            if(CheckCollisionRecs(knight.getCollisionRec(), enemy->getCollisionRec()))
            {
                knight.takeDMG(enemy->getDMG(), dT);
            }

            if(IsKeyPressed(KEY_ENTER))
            {
                if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                    counter++;
                }
            }
        }
    }
    UnloadTexture(map);
    CloseWindow();

    return 0;
}