#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

#include "HealthItem.h"

HealthItem::HealthItem(Location& location) : RenderableObject(location, 0.8), c_loc(location){
    ang = 0;
}


void HealthItem::drawHealthSign(){

glPushMatrix();
     glColor3f(1,0,0);
     glBegin(GL_POLYGON);
     glVertex3f(loc.x+0.25,loc.y+0.25,loc.z);//p1
     glVertex3f(loc.x+0.5,loc.y+0.25,loc.z);//p2
     glVertex3f(loc.x+0.5,loc.y-0.25,loc.z);//p3
     glVertex3f(loc.x+0.25,loc.y-0.25,loc.z);//p4
     glVertex3f(loc.x+0.25,loc.y-0.5,loc.z);//p5
     glVertex3f(loc.x-0.25,loc.y-0.5,loc.z);//p6
     glVertex3f(loc.x-0.25,loc.y-0.25,loc.z);//p7
     glVertex3f(loc.x-0.5,loc.y-0.25,loc.z);//p8
     glVertex3f(loc.x-0.5,loc.y+0.25,loc.z);//p9
     glVertex3f(loc.x-0.25,loc.y+0.25,loc.z);//p10
     glVertex3f(loc.x-0.25,loc.y+0.5,loc.z);//p11
     glVertex3f(loc.x+0.25,loc.y+0.5,loc.z);//p12
     glVertex3f(loc.x+0.25,loc.y+0.25,loc.z);//back to p1
     glEnd();
     glPopMatrix();

 }

 bool HealthItem::isCollisionPlayer(float x0, float y0, float z0, float r)
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

   void HealthItem::render(){
    drawHealthSign();
    update();
    glPushMatrix();
    glColor4f(0.31,0.65,0.76,0.3);
    glTranslated(loc.x, loc.y, loc.z); // move to this position
    glRotatef(ang,0, 1, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
   }

   void HealthItem::update(){
      ang+=0.5;
        }
