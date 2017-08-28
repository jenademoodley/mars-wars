
#include "EnemyBullet.h"
#include <GL/glut.h>
#include <iostream>
#include<math.h>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

EnemyBullet::EnemyBullet(Location& location)
: RenderableObject(location, 0), c_loc(location)
{

}

EnemyBullet::EnemyBullet(float size, Location& location, float dirx, float diry)
: RenderableObject(location, size), c_loc(location)
{
    xStart = loc.x;
    zStart = loc.z;
    hits = 3;
    stop = 30;
    this->bulletDist = 0;
    this->directionX = dirx;
    this->directionY = diry;
    this->shootBullet = false;
}

bool EnemyBullet::finish(){
    if(bulletDist > stop)
        return true;
    return false;
}

void EnemyBullet::render()
{
    update();
    glPushMatrix();
    glColor3ub(255,0,0);
    glTranslatef(loc.x, loc.y, loc.z);
   // glTranslatef(bulletx + sin(((direction) / 180 * 3.141592654f)), 0,bulletz + cos((((direction) / 180 * 3.141592654f))));
    if(shootBullet)
      //  objBullet();
    glutSolidSphere(getRadius(), 10, 10);
    glPopMatrix();
}

void EnemyBullet::update()
{
    if(shootBullet == true)
    {
        loc.z += sin(((directionX + 25) / 180 * 3.141592654f) - 90) * 0.2;
        loc.x += cos(((directionX + 25) / 180 * 3.141592654f) - 90) * 0.2;
        loc.y -= sin(((-directionY) / 180 * 3.141592654f)) * 0.2;
        bulletDist = sqrt(((loc.x - xStart) * (loc.x - xStart)) + (loc.y * loc.y) + ((loc.z - zStart) * (loc.z - zStart)));
    }
}

bool EnemyBullet::isCollision(float* x1, float* y1, float* z1, float rad1){
    float x = loc.x - *x1;
    float y = loc.y - *y1;
    float z = loc.z - *z1;

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (rad1 + getRadius()))
        return true;

    return false;

}





