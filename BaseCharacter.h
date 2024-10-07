#include <raylib.h>

#ifndef BASE_CHARACTER_H   
#define BASE_CHARACTER_H 

class BaseCharacter
{
    protected:
        Texture2D texture{LoadTexture("textures/Classy+Clash+Sprites/characters/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("textures/Classy+Clash+Sprites/characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("textures/Classy+Clash+Sprites/characters/knight_run_spritesheet.png")};
        Vector2 worldPos{};
        //saving last coordinates for map boundries
        Vector2 worldPosLastFrame{};
         //knight animation variables
        float runningTime{};
        const float updateTime{1.0/15.0};
        int frames{};
        const int maxFrames{6};
        //right : 1, left : -1
        float rightLeft{1};
        float speed{3.0};
        float width{};
        float height{};
        const float scale{6.0};
        Vector2 velocity{};
    public:
        BaseCharacter();
        Vector2 GetWorldPos() const
        {
            return worldPos;
        }
        virtual Vector2 GetScreenPos() = 0;
        void UndoMovement();
        virtual void Tick(float deltaTime);
        bool Alive() const 
        {
            return alive;
        }
        void setAlive(bool isAlive)
        {
            alive = isAlive;
        }
        Rectangle getCollisionRec(); 
    private:
        bool alive{true};
};

#endif