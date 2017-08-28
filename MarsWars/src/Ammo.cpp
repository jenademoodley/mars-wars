#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

#include "Ammo.h"

Ammo::Ammo(Location& location) : RenderableObject(location, 1.5), c_loc(location){
    ang = 0;
}

void Ammo::drawAmmoSign(){

        glLineWidth(5);
       glColor3f(0.93,0.93,0);
     glBegin(GL_LINE_LOOP);
     glVertex3f(loc.x-0.125,loc.y-0.3,loc.z);//p1
     glVertex3f(loc.x-0.475,loc.y-0.3,loc.z);//p2
     glVertex3f(loc.x,loc.y+0.5,loc.z);//p3
     glVertex3f(loc.x+0.475,loc.y-0.3,loc.z);//p4
     glVertex3f(loc.x+0.125,loc.y-0.3,loc.z);//p5
     glVertex3f(loc.x+0.06,loc.y-0.125,loc.z);//p6
     glVertex3f(loc.x-0.06,loc.y-0.125,loc.z);//p7
     glVertex3f(loc.x-0.125,loc.y-0.3,loc.z);//p1 again
     glEnd();

      glBegin(GL_LINE_LOOP);
     glVertex3f(loc.x-0.06,loc.y,loc.z);//p1
     glVertex3f(loc.x+0.06,loc.y,loc.z);//p2
     glVertex3f(loc.x,loc.y+0.125,loc.z);//p3
     glVertex3f(loc.x-0.06,loc.y,loc.z);//p1 again

     glEnd();
   }

   bool Ammo::isCollisionPlayer(float x0, float y0, float z0, float r)
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

   void Ammo::render(){
       update();
    drawAmmoSign();
    glPushMatrix();
    glColor4f(0.4,0.4,0.4,0.4);
    glTranslated(loc.x, loc.y, loc.z); // move to this position

    glRotatef(ang,0, 1, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
   }

   void Ammo::update(){
       ang+=0.5;
   }
