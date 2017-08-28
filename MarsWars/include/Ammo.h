
#ifndef AMMO_H
#define AMMO_H
#include "RenderableObject.h"
class Ammo: public RenderableObject
{
private:
    float ang;
    void drawAmmoSign();

public:
    Location c_loc;
   Ammo(Location& location);
    void render();
    void update();
    bool isCollisionPlayer(float x, float y, float z, float r);
};

#endif
