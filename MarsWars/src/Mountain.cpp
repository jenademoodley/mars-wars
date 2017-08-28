#include "Mountain.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
Mountain::Mountain(Location& location): RenderableObject(location, 0), c_loc(location)// Default Constructor
{

}

Mountain::Mountain(int size, Location& location)
    : RenderableObject(location, size), c_loc(location)// Default Constructor
{
    this->size = size;
}

void Mountain::drawMountain()
{
     glColor3ub (240, 200, 200);
    glutSolidCone(size, size, 6, 10);
}

bool Mountain::isCollision(bullet a)
{
    float x1 = loc.x;
    float y1 = loc.y;
    float z1 = loc.z;

    float x2 = a.loc.x;
    float y2 = a.loc.y;
    float z2 = a.loc.z;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 - z2;

    float radius1 = getRadius();
    float radius2 = a.getRadius();

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2))
        return true;

    return false;
}

bool Mountain::isCollisionBullet(EnemyBullet a)
{
    float x1 = loc.x;
    float y1 = loc.y;
    float z1 = loc.z;

    float x2 = a.loc.x;
    float y2 = a.loc.y;
    float z2 = a.loc.z;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 - z2;

    float radius1 = getRadius();
    float radius2 = a.getRadius();

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2))
        return true;

    return false;
}
void Mountain::render()
{
    glPushMatrix();
    glTranslated(loc.x, loc.y, loc.z);
    glRotatef(270, 1.0, 0.0, 0.0);

    drawMountain();
    glPopMatrix();
}

void Mountain::update(){
}
