#include <raylib.h>
#include <raymath.h>
#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture)
{
    worldPos = pos;  
    texture = idleTexture;
    idle = idleTexture;
    run = runTexture;
    width = texture.width/maxFrames;
    height = texture.height;
    speed = 2;
}

void Enemy::Tick(float deltaTime)
{   
    if(Alive())
    {
        velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());
        if(Vector2Length(velocity) < radius)
        {
            velocity = {};
        }

        BaseCharacter::Tick(deltaTime);
    }
    else
    {
        worldPos = {0, 0};
    }
}

Vector2 Enemy::GetScreenPos()
{
    return Vector2{Vector2Subtract(worldPos, target->GetWorldPos())};
}


void Enemy::setTarget(Character* character)
{
    target = character;
}