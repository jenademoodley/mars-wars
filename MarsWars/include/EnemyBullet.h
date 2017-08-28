
#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#include <iostream>
#include <vector>
#include "RenderableObject.h"

using namespace std;

class EnemyBullet: public RenderableObject
{
    public:
        //Location l;
        float size = 0;
        Location c_loc;
        float xStart;
        float zStart;
        int hits = 0;
        float bulletDist;
        float directionX = 0;
        float directionY = 0;
        int stop = 0;
        bool shootBullet;        //has the bullet been fired
        EnemyBullet(Location& location);
        EnemyBullet(float, Location& location, float dx, float dy);   //pass the gun coordinates
        void render();
        void update();
        bool isCollision(float* x, float* y, float* z, float rad);
       bool finish();
    private:


};

#endif

