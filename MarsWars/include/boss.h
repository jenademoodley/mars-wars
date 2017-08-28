#ifndef BOSS_H
#define BOSS_H

#include <ctime>
#include <cstdlib>
#include "objLoader.h"
#include "RenderableNPC.h"
#include "bullet.h"
#include "Mountain.h"
#include "EnemyBullet.h"
class boss : public RenderableNPC
{
     public:
        vector <EnemyBullet> ebullet;
        vector <Mountain>* mount;
         Location c_loc;
         float x1;
         float z1;
         int index;
         int health;
         int bulletTimer;
         int burstTimer;
         float burst;
         bool isCollide;
         bool collide;
         boss(Location& location);
        boss(Location& location, vector <Mountain>* mountain);
        void update();
        void render();
        void loadAmmo();
        void fire(float anglex);
        void fireBurst(float anglex);
    bool isCollisionMountain(float x, float y, float z, float r);
     bool isCollisionBoss(float x, float y, float z, float r);
        bool isCollision(bullet a);
    void getPlayerPos(float x, float z);

    private:
        string o;
    objLoader obj1 = objLoader(o);
        float xStart;
        float zStart;
    float direction;
    float distance;
    void drawBoss();
    void updateBoss();
    float initialAngle();
};
#endif



