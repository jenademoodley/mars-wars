#ifndef CRATERBOT_H
#define CRATERBOT_H

#include "RenderableNPC.h"
#include "EnemyBullet.h"

class CraterBot : public RenderableNPC
{
     public:
         Location c_loc;
         float x1;
         float z1;
         int index;
         int health;
         bool collide;
         float angleAlpha; // rotation angle of bot
        CraterBot(Location& location);
         int hit;
         void update();
        void render();
        bool isCollision(bullet a);
    void getPlayerPos(float x, float z);
    vector<EnemyBullet> botAmmo;
    void loadAmmo();
        void fire(float anglex);
    private:
         // central position
    void drawCraterBot();
    void updateCraterbot();

};
#endif
