#include <raylib.h>
#include "Character.h"
#include <raymath.h>

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width/maxFrames;
    height = texture.height;
}

Vector2 Character::GetScreenPos()
{
    return Vector2{(float)windowWidth/2 - scale * width/2, (float)windowHeight/2 - scale * height/2};
}

void Character::Tick(float deltaTime)
{
    if(Alive())
    {
        BaseCharacter::Tick(deltaTime);
        //movement
        if(IsKeyDown(KEY_A))
        {            
            velocity.x -= 1.0;
        }
        if(IsKeyDown(KEY_W))
            velocity.y -= 1.0;
        if(IsKeyDown(KEY_D))
        {
            velocity.x += 1.0;
        }
        if(IsKeyDown(KEY_S))
            velocity.y += 1.0;

        Vector2 origin{};
        Vector2 offgrid{};
        float rotation{};
        if(rightLeft > 0)
        {
            origin = {0, weapon.height * scale};
            offgrid = {59, 80};
            weaponCollisionRec = 
            {
                GetScreenPos().x + offgrid.x,
                GetScreenPos().y + offgrid.y - weapon.height * scale,
                weapon.width * scale,
                weapon.height * scale
            };
            rotation = IsKeyDown(KEY_ENTER) ? 35 : 0;
        }
        else
        {
            origin = {weapon.width * scale, weapon.height * scale};
            offgrid = {37, 80};
            weaponCollisionRec = 
            {
                GetScreenPos().x - weapon.width * scale + offgrid.x,
                GetScreenPos().y - weapon.height * scale + offgrid.y,
                weapon.width * scale,
                weapon.height * scale
            };
            rotation = IsKeyDown(KEY_ENTER) ? -35 : 0;
        }

        Rectangle weaponSource{0, 0, (float)weapon.width * rightLeft, (float)weapon.height};
        Rectangle weaponDest{GetScreenPos().x + offgrid.x, GetScreenPos().y + offgrid.y, weapon.width * scale, weapon.height * scale};
        DrawTexturePro(weapon, weaponSource, weaponDest, origin, rotation, WHITE);
        //DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
    }
}

void Character::takeDMG(int DMG, float dT)
{
    health -= DMG * dT;
    if(health <= 0)
    {
        setAlive(false);
    }
}

