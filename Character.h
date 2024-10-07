#include <raylib.h>
#include "BaseCharacter.h"

#ifndef CHARARTER_H
#define CHARACTER_H

class Character : public BaseCharacter
{
    private:
        int windowWidth{};
        int windowHeight{};
        Texture2D weapon{LoadTexture("textures/Classy+Clash+Sprites/characters/weapon_sword.png")};
        Rectangle weaponCollisionRec{};
        int health{100};
    public:
        Character(int winWidth, int winHeight);
        virtual void Tick(float deltaTime) override;
        virtual Vector2 GetScreenPos() override;
        Rectangle getWeaponCollisionRec() const 
        {
            return weaponCollisionRec;
        }
        int getHealth() const
        {
            return health;
        }
        void takeDMG(int DMG, float dT);
};
#endif