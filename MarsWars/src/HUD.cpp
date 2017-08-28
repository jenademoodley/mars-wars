#include "HUD.h"
#include <GL/glut.h>

HUD::HUD()
{
    //ctor
}

HUD::~HUD()
{
    //dtor
}

void HUD::render(bool shot)
{
    this->shot = shot;
    HUD::drawHUD();
}

void HUD::drawHUD()
{
    enable2D();

    glLineWidth(4);
    glDisable(GL_DEPTH_TEST);
    glBegin(GL_LINES );

    if (shot)
    {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(-0.02,0);
        glVertex2f(-0.005,0);
        glVertex2f(0.005,0);
        glVertex2f(0.02,0);
        glVertex2f(0,-0.03);
        glVertex2f(0,-0.01);
        glVertex2f(0,0.01);
        glVertex2f(0,0.03);
    }
    else
    {
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(-0.04,0);
        glVertex2f(-0.005,0);
        glVertex2f(0.005,0);
        glVertex2f(0.04,0);
        glVertex2f(0,-0.07);
        glVertex2f(0,-0.01);
        glVertex2f(0,0.01);
        glVertex2f(0,0.07);
    }
    glEnd();
    disable2D();
    glEnable(GL_DEPTH_TEST);
}

void HUD::enable2D()
{//this method is called whenever we need to draw 2D images on our HUD the cross hair may be included in the HUD, which we can make another class later on
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void HUD::disable2D()
{//method gets called once we are done drawing our 2D stuff BUT NB glEnable(GL_DEPTH_TEST) must b called immediately after this method otherwise objects in 3D wont function properly
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}
