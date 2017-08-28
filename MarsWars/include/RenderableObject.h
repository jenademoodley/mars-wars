

#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H
#include "Location.h"

class RenderableObject
{
    public:
        RenderableObject(const Location& location, float radius);
        ~RenderableObject();
        Location getLocation() { return loc; }
        float getRadius(){ return radius; }
        virtual void render()=0; // =0 make this pure virtual and the class abstract
        virtual void update()=0;
        Location loc;
    protected:

        float radius;
         // radius of sphere from location, which forms the footprint for this object




};

#endif // RENDERABLEOBJECT_H
