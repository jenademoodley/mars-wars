
#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

#include "Player.h"

Player::Player(Location& location)
: RenderableObject(location, 0), c_loc(location){
}

Player::Player(Location& location, vector<Mountain>* vmountain, vector<EnemyBot>* venemy, vector<CraterBot>* vcrater, vector<boss>* vBOSS,float dirX, float dirY)
: RenderableObject(location, 1.5), c_loc(location), mountain(vmountain), enemy(venemy), crater(vcrater), vboss(vBOSS)
{
      health = 1000;
      directionX = dirX;
      directionY = dirY;
     o  = "C:\\Halo-shotgun.obj";
      obj = objLoader(o);
      obj.Load(o);
   obj.calculateNormal(&loc.x, &loc.y, &loc.z);
}

void Player::drawGun(){
    glPushMatrix();
    glTranslatef(0.0, 0.25, 0.0);
    glColor3f(0.0, 0.3, 0.0);
   // glScalef(0.02,0.02,0.02);
   obj.render();
    glPopMatrix();
}

void Player::render(){
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    update();
    glTranslatef(loc.x, loc.y, loc.z);
glRotatef(-directionX, 0, 1, 0);
glRotatef(-directionY, 1, 0, 0);
drawGun();
    glPushMatrix();
    glutWireCube(0);
    glPopMatrix();

}

//method for collision detection between the player and a single other sphere
bool Player::isCollision(float x1, float y1, float z1, float radius1, float newX2, float newZ2)
{

    float x2 = newX2;
    float y2 = 0;
    float z2 = newZ2;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 + 5 - z2;

    float radius2 = getRadius();

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2))
        return true;

    return false;
}

//checks all cases of collision detections between the player and the mountains. Have seperate method
//to check between NPC's as we are going to implement other functions as well such as loss of health, not just
//hindering of movement
bool Player::isCollisionWorld(float x2, float z2){
    for(int i=0; i<mountain->size();i++){
        if(isCollision((*mountain)[i].loc.x, (*mountain)[i].loc.y + 5, (*mountain)[i].loc.z, (*mountain)[i].getRadius() * 0.7, x2, z2)){
            return true;
        }
    }
    return false;
}

bool Player::isCollisionNPC(float x2, float z2){
    for(int i=0; i<enemy->size(); i++){
        if(isCollision((*enemy)[i].loc.x, (*enemy)[i].loc.y,(*enemy)[i].loc.z, (*enemy)[i].getRadius(), x2, z2)){
                health-=10;
                (*enemy)[i].isCollide = true;
            return true;
        }
    }

    for(int i=0; i<enemy->size(); i++){
        if(isCollision((*enemy)[i].loc.x, (*enemy)[i].loc.y,(*enemy)[i].loc.z, (*enemy)[i].getRadius(), x2, z2)){
                health-=10;
                (*enemy)[i].isCollide = true;
            return true;
        }
    }

    for(int i=0; i<vboss->size(); i++){
        if(isCollision((*vboss)[i].loc.x, (*vboss)[i].loc.y,(*vboss)[i].loc.z, (*vboss)[i].getRadius(), x2, z2)){
                health-=20;
                (*vboss)[i].isCollide = true;
            return true;
        }
    }

    for(int i=0; i<crater->size(); i++){
        if(isCollision((*crater)[i].loc.x, (*crater)[i].loc.y,(*crater)[i].loc.z, (*crater)[i].getRadius(), x2, z2)){
                health-=10;
            return true;
        }
    }
    return false;
}

void Player::updatePlayer(float x, float z, float dirX, float dirY){
    this->x = x;
    this->z = z;
    this->dirX = dirX;
    this->dirY = dirY;
}


void Player::update(){
loc.x = x;
loc.z = z;
directionX = dirX;
directionY = dirY;

}

void Player::setHealth(int h){
    health-=h;
}
