#ifndef WORLD_H
#define WORLD_H
#include "Texture.h"
class World
{
    public:
        World();
        World(float, float, float, float);
        void UpdateSun();
        float GroundHeight = 0;
        float SkyHeight = 0;
        float WorldSize = 0;
        float sunX = 0;
        float sunY = 0;
        float sunZ = 0;
        float sunSpeed = 0;
        bool sunMovementR = true;
        bool sunMovementL = false;
        bool sunMovementF = false;
        bool sunMovementB = false;
        void render();
        Texture *t = new Texture();

        virtual ~World();

    private:
        void drawGround();
        void drawSky();
        void drawLeft();
        void drawRight();
        void drawBack();
        void drawFront();
        void drawSun();
        void drawStarsSky();
        void drawStarsLeft();
        void drawStarsRight();
        void drawStarsBack();
        void drawStarsFront();
        void drawSpaceThings();
};
#endif // WORLD_H
