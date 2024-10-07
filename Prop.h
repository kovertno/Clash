#include <raylib.h>

class Prop
{
    private:
        Texture2D texture{};
        Vector2 worldPos{};
        const float scale{6.0};
    public:
        Prop(Vector2 pos, Texture2D tex);
        void RenderProp(Vector2 knightPos);
        Rectangle getCollisionRec(Vector2 knightPos);
};