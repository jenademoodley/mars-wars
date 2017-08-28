#include "World.h"
#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <GL/gl.h>
#include "Texture.h"

World::World()// Default Constructor
{
        //World Dimensions
        World::GroundHeight = -2;
        World::SkyHeight = 20.0;
        World::WorldSize = 100.0;
        this->sunSpeed = sunSpeed;
        this->sunX = WorldSize - 5;
        this->sunY = SkyHeight - 10;
        this->sunZ = WorldSize - 5;
}

World::World(float GroundHeight, float SkyHeight, float WorldSize, float sunSpeed)// Para Constructor
{
        this->GroundHeight = GroundHeight;
        this->SkyHeight = SkyHeight;
        this->WorldSize = WorldSize;
        this->sunSpeed = sunSpeed;
        this->sunX = WorldSize - 5;
        this->sunY = SkyHeight - 10;
        this->sunZ = WorldSize - 5;
}

World::~World() //Destructor
{
}

void World::render()
{
        t->texture = t->LoadTexture( "C:\\heightfield.raw", 256, 256 ); //loadthe texture
        glEnable( GL_TEXTURE_2D ); //enable 2D texturing
        glEnable(GL_TEXTURE_GEN_S); //enable texture coordinategeneration



        World::drawGround();
        t->FreeTexture( t->texture );

        glColor3f(0, 0, 0);
        World::drawSky();
        glPointSize(1.0);
        World::drawLeft();
        World::drawRight();
        World::drawBack();
        World::drawFront();
        World::drawSun();
        World::drawStarsSky();
        World::drawStarsLeft();
        World::drawStarsRight();
        World::drawStarsBack();
        World::drawStarsFront();
        World::UpdateSun();
}

void World::drawGround()
{
        glColor3ub (207, 83, 30);
        glBindTexture( GL_TEXTURE_2D, t->texture ); //bind the texture
        glBegin(GL_QUADS);
        /*glVertex3f(-WorldSize, GroundHeight, -WorldSize);
        glVertex3f(-WorldSize, GroundHeight, WorldSize);
        glVertex3f(WorldSize, GroundHeight, WorldSize);
        glVertex3f(WorldSize, GroundHeight, -WorldSize);*/

        glVertex3f(WorldSize, GroundHeight, WorldSize);

         glVertex3f(WorldSize, GroundHeight, -WorldSize);

          glVertex3f(-WorldSize, GroundHeight, -WorldSize);

          glVertex3f(-WorldSize, GroundHeight, WorldSize);
        glEnd();
}

void World::drawSun()
{
    glPushMatrix();
    glColor3ub (200, 200, 0);
    glTranslated(sunX,sunY,sunZ);
    glutSolidSphere(10,50,50);
    glPopMatrix();
}

void World::UpdateSun()
{
    if (sunMovementR)
    {
        sunX -= sunSpeed;
        if ( sunX < -WorldSize)
        {
            sunMovementR = false;
            sunMovementF = true;
        }
    }
    else if (sunMovementF)
    {
        sunZ -= sunSpeed;
        if (sunZ < - WorldSize)
        {
            sunMovementF = false;
            sunMovementL = true;
        }
    }
    else if (sunMovementL)
    {
        sunX += sunSpeed;
        if (sunX >  WorldSize)
        {
            sunMovementL = false;
            sunMovementB = true;
        }
    }
    else if(sunMovementB)
    {
        sunZ += sunSpeed;
        if (sunZ >  WorldSize)
        {
            sunMovementB = false;
            sunMovementR = true;
        }
    }
}

void World::drawSky()
{
        glBegin(GL_QUADS);
        glVertex3f(-WorldSize, SkyHeight, -WorldSize);
        glVertex3f(-WorldSize, SkyHeight, WorldSize);
        glVertex3f(WorldSize, SkyHeight, WorldSize);
        glVertex3f(WorldSize, SkyHeight, -WorldSize);
        glEnd();
}

void World::drawStarsSky()
{
    glColor3f (1, 1, 1);
    glBegin(GL_POINTS);
    for (int i = -WorldSize; i <= WorldSize; i += 10)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 10)
        {
            glVertex3f (i * 3, SkyHeight, j * 2);
        }
    }
    glEnd();
}

void World::drawLeft()
{
        glBegin(GL_QUADS);
        glVertex3f(-WorldSize, GroundHeight, -WorldSize);
        glVertex3f(-WorldSize, SkyHeight, -WorldSize);
        glVertex3f(-WorldSize, SkyHeight, WorldSize);
        glVertex3f(-WorldSize, GroundHeight, WorldSize);
        glEnd();
}

void World::drawStarsLeft()
{
    glColor3f (1, 1, 1);
    glBegin(GL_POINTS);
    for (int i = 0; i <= SkyHeight; i += 5)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 3)
        {
            glVertex3f (j * 5, i  * 3, WorldSize);
        }
    }

    for (int i = 0; i <= SkyHeight; i += 5)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 3)
        {
            glVertex3f (j * 7, i  * 2, WorldSize);
        }
    }
    glEnd();
}

void World::drawRight()
{
        glBegin(GL_QUADS);
        glVertex3f(WorldSize, GroundHeight, -WorldSize);
        glVertex3f(WorldSize, SkyHeight, -WorldSize);
        glVertex3f(WorldSize, SkyHeight, WorldSize);
        glVertex3f(WorldSize, GroundHeight, WorldSize);
        glEnd();
}

void World::drawStarsRight()
{
    glColor3f (1, 1, 1);
    glBegin(GL_POINTS);
    for (int i = 0; i <= SkyHeight; i += 5)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 3)
        {
             glVertex3f (j * 2, i  * 1.5, -WorldSize);
        }
    }

    for (int i = 0; i <= SkyHeight; i += 5)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 3)
        {
             glVertex3f (j * 5, i  * 7, -WorldSize);
        }
    }
    glEnd();
}

void World::drawBack()
{
        glBegin(GL_QUADS);
        glVertex3f(-WorldSize, GroundHeight, WorldSize);
        glVertex3f(-WorldSize, SkyHeight, WorldSize);
        glVertex3f(WorldSize, SkyHeight, WorldSize);
        glVertex3f(WorldSize, GroundHeight, WorldSize);
        glEnd();
}

void World::drawStarsBack()
{
    glColor3f (1, 1, 1);
    glBegin(GL_POINTS);
    for (int i = 0; i <= SkyHeight; i += 5)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 3)
        {
            glVertex3f (WorldSize, i  * 6.5, j * 2 );
        }
    }

    for (int i = 0; i <= SkyHeight; i += 5)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 3)
        {
            glVertex3f (WorldSize, i  * 3, j * 7 );
        }
    }
    glEnd();
}

void World::drawFront()
{
        glBegin(GL_QUADS);
        glVertex3f(-WorldSize, GroundHeight, -WorldSize);
        glVertex3f(-WorldSize, SkyHeight, -WorldSize);
        glVertex3f(WorldSize, SkyHeight, -WorldSize);
        glVertex3f(WorldSize, GroundHeight, -WorldSize);
        glEnd();
}

void World::drawStarsFront()
{
    glColor3f (1, 1, 1);
    glBegin(GL_POINTS);
    for (int i = 0; i <= SkyHeight; i += 5)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 3)
        {
            glVertex3f (-WorldSize, i  * 3, j * 2 );
        }
    }

    for (int i = 0; i <= SkyHeight; i += 5)
    {
        for (int j = -WorldSize; j <= WorldSize; j += 3)
        {
            glVertex3f (-WorldSize, i  * 5, j * 3 );
        }
    }
    glEnd();
}

void World::drawSpaceThings()
{
}


