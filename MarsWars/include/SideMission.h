
#ifndef SIDEMISSION_H
#define SIDEMISSION_H
#include "RenderableObject.h"
class SideMission: public RenderableObject
{
private:
    float ang;
    void drawSideMission();

public:
    Location c_loc;
   SideMission(Location& location);
    void render();
    void update();
    bool isCollisionPlayer(float x, float y, float z, float r);
};

#endif

