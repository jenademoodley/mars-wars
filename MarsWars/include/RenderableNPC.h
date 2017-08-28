#ifndef RENDERABLENPC_H
#define RENDERABLENPC_H
#include "Location.h"
#include "bullet.h"
class RenderableNPC
{
    public:
        RenderableNPC(const Location& location, float radius);
        ~RenderableNPC();
        Location getLocation() { return loc; }
        float getRadius(){ return radius; }
        virtual void render()=0; // =0 make this pure virtual and the class abstract
        virtual void update()=0;
       // virtual bool isCollisionPlayer(float x, float y, float z, float r) = 0;
        virtual bool isCollision(bullet a) = 0;
        virtual void getPlayerPos(float x, float z) = 0;
        Location loc;
    protected:

        float radius;
         // radius of sphere from location, which forms the footprint for this object




};

#endif // RENDERABLEOBJECT_H
