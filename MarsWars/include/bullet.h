
#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include <vector>
#include "RenderableObject.h"
#include "objLoader.h"

using namespace std;

class bullet: public RenderableObject
{
    public:
        objLoader obj;
        Location c_loc;
        float xStart;
        float zStart;
        float bulletDist;
        float directionX =0;
        float directionY = 0;
        bool shootBullet;        //has the bullet been fired
        bullet(Location& location);
        bullet(Location& location, float dx, float dy);   //pass the gun coordinates
        void render();
        void update();
       bool finish();
    private:
        void objBullet();

};

#endif

