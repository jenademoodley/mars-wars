#include "Fog.h"
#include <GL/glut.h>

Fog::~Fog()
{
    //dtor
}

Fog::Fog(float health)
{
    GLfloat density = 0.004;
    GLfloat fogColor[4] = {5 - health/200 , 0.0, 0.0, 1.0}; //set the fog colour
    glEnable (GL_FOG); //enable the fog
    glFogf (GL_FOG_START, 100);
    glFogf (GL_FOG_END, 11);
    glFogi (GL_FOG_MODE, GL_EXP2); //set the fog mode to GL_EXP2
    glFogfv (GL_FOG_COLOR, fogColor); //set the fog color to our colour chosen above
    glFogf (GL_FOG_DENSITY, density); //set the density to the value above
    glHint (GL_FOG_HINT, GL_NICEST);
}
