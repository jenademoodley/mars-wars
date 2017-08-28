
#include "bullet.h"
#include <GL/glut.h>
#include <iostream>
#include<math.h>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

bullet::bullet(Location& location)
: RenderableObject(location, 0), c_loc(location), obj("C:\\Users\\Jenade Moodley\\Desktop\\bullet.obj")
{

}

bullet::bullet(Location& location, float dirx, float diry)
: RenderableObject(location, 0.2), c_loc(location), obj("bullet.obj")
{
    xStart = loc.x;
    zStart = loc.z;
    this->bulletDist = 0;
    this->directionX = dirx;
    this->directionY = diry;
    this->shootBullet = false;
}

bool bullet::finish(){
    if(bulletDist > 50)
        return true;
    return false;
}


void bullet::objBullet(){

obj.Load("C:\\Users\\Jenade Moodley\\Desktop\\bullet.obj");
    obj.render();

}
void bullet::render()
{
    update();
    glPushMatrix();
    glColor3ub(0,0,255);
    glTranslatef(loc.x, loc.y, loc.z);
   // glTranslatef(bulletx + sin(((direction) / 180 * 3.141592654f)), 0,bulletz + cos((((direction) / 180 * 3.141592654f))));
    if(shootBullet && bulletDist > 3)
      //  objBullet();
    glutSolidSphere(getRadius(), 10, 10);
    glPopMatrix();
}

void bullet::update()
{
    if(shootBullet == true)
    {
        loc.z += sin(((directionX + 25) / 180 * 3.141592654f) - 90) * 0.5;
        loc.x += cos(((directionX + 25) / 180 * 3.141592654f) - 90) * 0.5;
        loc.y -= sin((directionY - 0.01) * 3.141592654f / 180) * 0.5;
        bulletDist = sqrt(((loc.x - xStart) * (loc.x - xStart)) + (loc.y * loc.y) + ((loc.z - zStart) * (loc.z - zStart)));
        //cout<< bulletDist <<endl;

    }
}



