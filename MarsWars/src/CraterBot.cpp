#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//using namespace std;

#include "CraterBot.h"

#define PI 3.14159265

CraterBot::CraterBot(Location& location)
    : RenderableNPC(location, 1), c_loc(location)
{
    hit = 0;
    collide = false;
angleAlpha = 0;
    health = 0;
     loadAmmo(); // loads bots ammo
}

/*void CraterBot::setHit(bool h){
    hit = h;
}

bool CraterBot::getHit(){
    return hit;
}*/

void CraterBot::drawCraterBot()
{
    glPushMatrix();

    //Draw Body
    glTranslatef(0.0, -0.25, 0.0);
    glColor3f(0.0, 0.3, 0.0);
    glutSolidSphere(0.75, 20, 20);

    //Draw Head
    glTranslatef(0.0, 0.95, 0.0);
    glColor3f(0.0, 0.3, 0.0);
    glutSolidCube(0.25);

    //Draw Eyes
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0.1, 0.1, -0.2);
    glutSolidSphere(0.05, 10, 10);
    glTranslatef(-0.2, 0.0, 0.0);
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();

    glPopMatrix();
}

//checks if there is a collision between a craterbot and a bullet
bool CraterBot::isCollision(bullet a)
{
    float x1 = loc.x;
    float y1 = loc.y;
    float z1 = loc.z;

    float x2 = a.loc.x;
    float y2 = a.loc.y;
    float z2 = a.loc.z;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 - z2;

    float radius1 = getRadius();
    float radius2 = a.getRadius();

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2)){
        return true;
    }
    return false;
}


void CraterBot::render()
{
    update();

    glPushMatrix();
    glTranslated(loc.x, loc.y, loc.z); //moves bot around world
    glRotated(angleAlpha, 0, 1, 0); // rotatates bot to face player

    drawCraterBot();


    glPopMatrix();
}

void CraterBot::update(){

updateCraterbot();

for(int i=0; i<botAmmo.size(); i++){
    if(botAmmo[i].finish())
        botAmmo.erase(botAmmo.begin() + i);
}
for(int i=0; i<botAmmo.size(); i++){
    if(botAmmo[i].shootBullet)
        botAmmo[i].render();
}

}
void CraterBot::fire(float anglex){
    float RP = sqrt(((loc.x - x1) * (loc.x - x1)) + ((loc.z - z1) * (loc.z - z1)) );
    if(index >=0){
    botAmmo[index].loc.x=loc.x;
    botAmmo[index].loc.y=loc.y;
    botAmmo[index].loc.z=loc.z;
    botAmmo[index].directionX =-anglex;
    botAmmo[index].directionY = 0;
    botAmmo[index].xStart = loc.x;
    botAmmo[index].zStart =loc.z;
    botAmmo[index].shootBullet =true;
    index--;
    }
}
void CraterBot::getPlayerPos(float x, float z){
    this->x1 = x;
    this->z1 = z;
}

void CraterBot::loadAmmo() // loads 10 bullets for bot, when ammo is empty, this method will be called in the update to refill ammo.
{
    if(botAmmo.size() == 0)
    {
        for(int i = 0; i < 15; i++)
        {
            Location loc = Location(loc.x, loc.y, loc.z);
            EnemyBullet b = EnemyBullet(0.2, loc, 0.0f,0.0f);
            b.stop = 20;
            botAmmo.push_back(b);
        }
        index = botAmmo.size()-1;
    }
}
void CraterBot::updateCraterbot()
{

loadAmmo();


    double dx = loc.x - x1;
    double dz = loc.z - z1;

    double distSqr = (dx * dx) + (dz * dz); //square of distance distance between bot and player

    double dist = sqrt(distSqr);

    if(dist <= 20) // tells bot to roatate only if player is close enough
    {
        angleAlpha+=20; // when the player is 20 world units or less away, the bot will spin to start shooting randomly
        fire(angleAlpha);
    }

    glutPostRedisplay(); //tells glut to update display
}


