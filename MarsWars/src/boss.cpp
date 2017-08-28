#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
//using namepsace std;
#include "boss.h"
#define PI 3.14159265

boss::boss(Location& location): RenderableNPC(location, 1), c_loc(location){


}
boss::boss(Location& location, vector <Mountain>* mountain)
    : RenderableNPC(location, 17.0), c_loc(location), mount(mountain)
{

direction = 72;
    xStart = loc.x;
    zStart = loc.z;
    x1 = 0;
    z1 = 0;
    isCollide = false;
    collide = false;
    bulletTimer = 0;
    health = 1000;
   o  = "C:\\ED-209.obj";
      obj1 = objLoader(o);
      obj1.Load(o);
   obj1.calculateNormal(&loc.x, &loc.y, &loc.z);
   loadAmmo();

}

float boss::initialAngle(){
   // cout << loc.x << endl;
    float tx = loc.x;
    float tz = (loc.z + 10);
    float RP = sqrt(((loc.x - x1) * (loc.x - x1)) + ((loc.z - z1) * (loc.z - z1)) );
    float TP = sqrt(((tx - x1) * (tx - x1)) + ((tz - z1) * (tz - z1)) );
    float RT = sqrt(((loc.x - tx) * (loc.x - tx)) + ((loc.z - tz) * (loc.z - tz)) );


float arg1 = (TP * TP) - (RP * RP) - (RT * RT);
float arg2 = 2 * RP * RT;

    float R = acos(arg1 / arg2 )  *  (180.0 / PI);
    if(loc.x> x1 && loc.z >z1)
        return -R;
    if(loc.x> x1 && loc.z <z1)
        return -R;
        if(loc.x< x1 && loc.z >z1)
        return R;
        if(loc.x< x1 && loc.z <z1)
        return R;
    //angle = -R;
    return R;
}


void boss::drawBoss()
{
     glPushMatrix();
   // glRotatef(180.0, 0, 1, 0);
     glRotatef(-initialAngle() , 0, 1, 0);
    // glutWireSphere(getRadius(), 10, 10);
    glColor3f(0.0, 0.3, 0.0);
    glScalef(0.6,0.6,0.6);
    glTranslated(7 , 5.5 , 33);
   obj1.render();

    glPopMatrix();
}

//checks if there is a collision between an enemybot and a bullet
bool boss::isCollision(bullet a)
{ float x1 = loc.x;
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

    if(distance < (radius1 + radius2))
        return true;

    return false;
}

bool boss::isCollisionBoss(float tx, float ty, float tz, float tr)
{
    float x1 = loc.x;
    float y1 = loc.y;
    float z1 = loc.z;

    float x2 = tx;
    float y2 = ty;
    float z2 = tz;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 - z2;

    float radius1 = getRadius();
    float radius2 = tr;

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2)){
            collide = true;
        return true;
    }
    return false;
}


bool boss::isCollisionMountain(float tx, float ty, float tz, float tr)
{
    float x1 = loc.x;
    float y1 = loc.y;
    float z1 = loc.z;

    float x2 = tx;
    float y2 = ty;
    float z2 = tz;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 - z2;

    float radius1 = getRadius();
    float radius2 = tr;

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2))
        return true;

    return false;
}


void boss::render()
{
    update();
    glPushMatrix();
    glTranslated(loc.x, loc.y, loc.z); //moves bot around world
    drawBoss();
    glPopMatrix();
}

void boss::update(){
updateBoss();
for(int i=0; i<ebullet.size(); i++){
    if(ebullet[i].finish())
        ebullet.erase(ebullet.begin() + i);
}
for(int i=0; i<ebullet.size(); i++){
    if(ebullet[i].shootBullet)
        ebullet[i].render();
}
}

void boss::getPlayerPos(float x, float z){
    this->x1 = x;
    this->z1 = z;
}

void boss::fire(float anglex){
     float RP = sqrt(((loc.x - x1) * (loc.x - x1)) + ((loc.z - z1) * (loc.z - z1)) );

    if(index >=0){
    ebullet[index].loc.x=loc.x;
    ebullet[index].loc.y=0;
    ebullet[index].loc.z=loc.z;
    ebullet[index].directionX =anglex;
    ebullet[index].directionY = acos(17/RP);
    ebullet[index].xStart = loc.x;
    ebullet[index].zStart =loc.z;
    ebullet[index].shootBullet =true;
    index--;
    ebullet[index].loc.x=loc.x+2;
    ebullet[index].loc.y=4;
    ebullet[index].loc.z=loc.z+2;
    ebullet[index].directionX =anglex;
    ebullet[index].directionY = acos(17/RP);
    ebullet[index].xStart = loc.x;
    ebullet[index].zStart =loc.z;
    ebullet[index].shootBullet =true;
    index--;
    }
}

void boss::fireBurst(float anglex){
     float RP = sqrt(((loc.x - x1) * (loc.x - x1)) + ((loc.z - z1) * (loc.z - z1)) );

    if(index >=0){
    ebullet[index].loc.x=loc.x;
    ebullet[index].loc.y=loc.y;
    ebullet[index].loc.z=loc.z;
    ebullet[index].directionX =-anglex;
    ebullet[index].directionY = 0;
    ebullet[index].xStart = loc.x;
    ebullet[index].zStart =loc.z;
    ebullet[index].shootBullet =true;
    index--;
    }
}

void boss::updateBoss()
{

    loadAmmo();

    float RP = sqrt(((loc.x - x1) * (loc.x - x1)) + ((loc.z - z1) * (loc.z - z1)) );

    bulletTimer++;
    burstTimer++;
    if(bulletTimer >= 20 && RP < 100){
    bulletTimer = 0;
    fire(initialAngle());
}

    //srand((unsigned)time(0));
    if(isCollide){
        direction += 50;
        isCollide = false;
    }

    if(distance >= 200){
        xStart = loc.x;
        zStart = loc.z;
        direction =0;
    }

    if(burstTimer >= 100){
        burst+=30;
        fireBurst(burst);
        burstTimer =0;
    }


   if(loc.x >= 90 || loc.z >= 90 || loc.x <=-90|| loc.z<=-90){
    direction +=72 ;
    distance = 0;
   }

        loc.z += sin((270 - direction) * PI / 180.0) *0.5;
        loc.x += cos((270 - direction)* PI / 180.0) *0.5;
        distance = sqrt(((loc.x - xStart) * (loc.x - xStart)) + ((loc.z - zStart) * (loc.z - zStart)));

        for(int i=0; i<mount->size(); i++){
            if(isCollisionMountain((*mount)[i].loc.x , (*mount)[i].loc.y , (*mount)[i].loc.z , (*mount)[i].getRadius()))
                (*mount).erase((*mount).begin() + i);
        }

}


void boss::loadAmmo() // loads 10 bullets for bot, when ammo is empty, this method will be called in the update to refill ammo.
{
    if(ebullet.size() == 0)
    {
        for(int i = 0; i < 10; i++)
        {
            Location loc = Location(loc.x, loc.y, loc.z);
            EnemyBullet b = EnemyBullet(2.0, loc, 0.0f,0.0f);
            b.stop = 100;
            ebullet.push_back(b);
        }
        index = ebullet.size()-1;
    }
}
