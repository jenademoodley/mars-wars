
#include "RenderableNPC.h"

RenderableNPC::RenderableNPC(const Location& location, float radius)
// initalise location, otherwise the default constructor will be called
   : loc(location) // This would not be necessary if this was a pointer or if Location was a struct
{

    this->radius = radius;
    this->loc.x = location.x;
    this->loc.y = location.y;
    this->loc.z = location.z;

}

RenderableNPC::~RenderableNPC()
{
    //dtor
}
