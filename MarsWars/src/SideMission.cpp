#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

#include "SideMission.h"

SideMission::SideMission(Location& location) : RenderableObject(location, 1.5), c_loc(location){
    ang = 0;
}
void SideMission::drawSideMission(){
    glPushMatrix();
        glColor4f(0.5,0,0.5,0.4);
        glutSolidOctahedron();
        glPopMatrix();
   }

   bool SideMission::isCollisionPlayer(float x0, float y0, float z0, float r)
{
    float x1 = loc.x;
    float y1 = loc.y;
    float z1 = loc.z;

    float x2 = x0;
    float y2 = y0;
    float z2 = z0;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 - z2;

    float radius1 = getRadius();
    float radius2 = r;

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2))
        return true;

    return false;
}

   void SideMission::render(){
       update();
    glPushMatrix();
    glTranslated(loc.x, loc.y, loc.z); // move to this position
    glRotatef(ang,0, 1, 0);
    drawSideMission();
    glPopMatrix();
   }

   void SideMission::update(){
      ang+=0.5;
        }


