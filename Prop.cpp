#include <raylib.h>
#include <raymath.h>
#include "Prop.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    worldPos(pos),
    texture(tex)
{

}

void Prop::RenderProp(Vector2 knightPos)
{
    //worldPos + mapPos, since it has to move along the map, so -> worldPos + mapPos = worldPos - knightPos
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};
    DrawTextureEx(texture, screenPos, 0, scale, WHITE);
}

Rectangle Prop::getCollisionRec(Vector2 knightPos)
{
    Vector2 screenPos{Vector2Subtract(worldPos, knightPos)};

    return Rectangle{screenPos.x, screenPos.y, (float)texture.width * scale, (float)texture.height * scale};
}