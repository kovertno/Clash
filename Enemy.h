#include <raylib.h>
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
    private:
        Character* target{};
        int DMG{8};
        int radius{35};
    public:
        void setTarget(Character *character);
        Enemy(Vector2 pos, Texture2D idleTexture, Texture2D runTexture);
        virtual void Tick(float deltaTime) override;
        virtual Vector2 GetScreenPos() override;
        int getDMG() const
        {
            return DMG;
        }
};