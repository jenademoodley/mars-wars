#include "Sunlight.h"
#include <GL/glut.h>

Sunlight::Sunlight()
{
    //ctor
    glEnable(GL_LIGHTING); // turns on the lighting model in OpenGL
    glEnable(GL_LIGHT0);  // enables light 0
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader

    GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; //set thelight specular to white
    GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; //set thediffuse light to white
    GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; //set the diffuse light to white
    GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; //set the light ambient to black
    GLfloat mat_shininess[] = { 1.0 };

    GLfloat light_position[] = {0, 0, 0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    float light_direction[] = { 2,0,2};
    float light_angle[] ={50};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blankMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

Sunlight::~Sunlight()
{
    //dtor
}

void Sunlight::render(float x, float y, float z)
{
    GLfloat light_position[] = {x, y, z, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}
