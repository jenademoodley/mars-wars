
#ifndef HEALTHITEM_H
#define HEALTHITEM_H
#include "RenderableObject.h"
class HealthItem: public RenderableObject
{
private:
    float ang;
    void drawHealthSign();

public:
    Location c_loc;
    HealthItem(Location& location);
    void render();
    void update();
    bool isCollisionPlayer(float x, float y, float z, float r);
};

#endif
