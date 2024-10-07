#include <raylib.h>
#include <raymath.h>
#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::UndoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{GetScreenPos().x, GetScreenPos().y, width * scale, height * scale};
}
 
void BaseCharacter::Tick(float deltaTime)
{
    if(Alive())
    {
        worldPosLastFrame = worldPos;

        //updating enemy animation
        runningTime += deltaTime;
        if(runningTime >= updateTime)
        {
            runningTime = 0;
            frames++;
            if(frames >= maxFrames)
                frames = 0;
        }

        if(Vector2Length(velocity) != 0.0)
        {
            //set worldPos = worldPos + direction;
            (velocity.x > 0) ? rightLeft = 1 : rightLeft = -1;
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
            texture = run;
        }
        else
            texture = idle;

        velocity = {};  

        //drawing an enemy
        //character sprite parameters (width*-1 if going in the opposite direction)
        Rectangle enemySource{frames * width, 0.f, rightLeft * width, height};
        //where the character is destined to be placed on the screen
        Rectangle enemyDest{GetScreenPos().x, GetScreenPos().y, scale * width, scale * height};
        DrawTexturePro(texture, enemySource, enemyDest, Vector2{}, 0.0f, WHITE);
    }
}
