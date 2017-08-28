#include <iostream>
//#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
//using namepsace std;
#include "EnemyBot.h"
#define PI 3.14159265


EnemyBot::EnemyBot(Location& location, vector <Mountain>* mountain, vector <CraterBot>* craterbot, float s)
    : RenderableNPC(location, 1.2), c_loc(location), mount(mountain), crater(craterbot)
{
srand((unsigned)time(NULL));
bulletTimer = 0;
    xStart = loc.x;
    zStart = loc.z;
    isCollide = false;
    health = 2;
    speed = s;
    collide = false;
    direction = (rand() % 360);
     loadAmmo();
}

float EnemyBot::initialAngle(){
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


void EnemyBot::drawEnemyBot()
{
    glPushMatrix();
    glRotatef(180.0, 0, 1, 0);
     glRotatef(-initialAngle() , 0, 1, 0);
    glPushMatrix(); // eyes
    glColor3ub(128,0,0);
    glTranslatef(0.2,1.9,0.5);
    glutSolidCube(0.15);
    glPopMatrix();

    glPushMatrix();  // eyes
    glColor3ub(178,34,34);
    glTranslatef(-0.2,1.9,0.5);
    glutSolidCube(0.15);
    glPopMatrix();

    glPushMatrix();  // mouth
    glColor3ub(0,0,128);
    glScalef(1,0.2,1);
    glTranslatef(0,8,0.5);
    glutSolidCone(0.06, 0.3, 10, 2);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(128,128,128);
    glTranslatef(0,1.8,0);//head
    glutSolidCube(0.90);
    glPopMatrix();


    glPushMatrix();
    glColor3ub(165,42,42);
    glTranslatef(0,1.1,0);  //neck
    glScalef(0.5,1,0.5);
    glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0,0,0);
    glTranslatef(0,0.104,0);
    glScalef(4,4.4,2.5);      //body
     glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(47,79,79);
    glTranslatef(1.2,0.5,0);        //right arm
    glScalef(2.0,0.5,0.5);
    glutSolidCube(0.4);

    glTranslatef(0.2,-1,0);
    glScalef(0.3,4,0.5);
    glutSolidCube(0.6);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(85,107,47);
    glTranslatef(0.5,-0.4,0);
    glScalef(0.5,6.5,0.5);        //leg
     glutSolidCube(0.5);
    glPopMatrix();


    glPushMatrix();
    glColor3ub(85,107,47);
    glTranslatef(-0.5,-0.4,0);
    glScalef(0.5,6.5,0.5);            //leg
     glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(0,0,0);
    glTranslatef(-0.5,-1,0);
    glutSolidCube(0.10);
    glColor3f(0.0, 1.0, 0.0);
    glPopMatrix();

    glPushMatrix();
    glColor3ub(47,79,79);
    glTranslatef(-1.2,0.5,0);        //left arm
    glScalef(2.0,0.5,0.5);
    glutSolidCube(0.4);

    glTranslatef(-0.2,-1,0);
    glScalef(0.3,4,0.5);
    glutSolidCube(0.6);
    glPopMatrix();
    glPopMatrix();
}

bool EnemyBot::isCollisionEnemyBot(float tx, float ty, float tz, float tr)
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
//checks if there is a collision between an enemybot and a bullet
bool EnemyBot::isCollision(bullet a)
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

    if(distance < (radius1 + radius2))
        return true;

    return false;
}

bool EnemyBot::isCollisionMountain()
{
    for(int i=0; i< mount->size(); i++){
    float x1 = loc.x;
    float y1 = loc.y;
    float z1 = loc.z;

    float x2 = (*mount)[i].loc.x;
    float y2 = (*mount)[i].loc.y;
    float z2 = (*mount)[i].loc.z;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 - z2;

    float radius1 = getRadius();
    float radius2 = (*mount)[i].getRadius();

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2))
        return true;
    }
    return false;

}

bool EnemyBot::isCollisionCrater()
{
    for(int i=0; i< crater->size(); i++){
    float x1 = loc.x;
    float y1 = loc.y;
    float z1 = loc.z;

    float x2 = (*crater)[i].loc.x;
    float y2 = (*crater)[i].loc.y;
    float z2 = (*crater)[i].loc.z;

    float x = x1 - x2;
    float y = y1 - y2;
    float z = z1 - z2;

    float radius1 = getRadius();
    float radius2 = (*crater)[i].getRadius();

    float distance = sqrt((x * x) + (y * y) + (z * z));

    if(distance < (radius1 + radius2))
        return true;
    }
    return false;

}

void EnemyBot::render()
{
    update();
    glPushMatrix();
    glTranslated(loc.x, loc.y, loc.z); //moves bot around world

    //glRotated(angle, 0, 1, 0);
    //glutWireSphere(getRadius(), 10, 10);
    drawEnemyBot();

    glPopMatrix();
}

void EnemyBot::update(){

updateEnemyBot();

for(int i=0; i<ebullet.size(); i++){
    if(ebullet[i].finish())
        ebullet.erase(ebullet.begin() + i);
}
for(int i=0; i<ebullet.size(); i++){
    if(ebullet[i].shootBullet)
        ebullet[i].render();
}

}
void EnemyBot::fire(float anglex){
    // float RP = sqrt(((loc.x - x1) * (loc.x - x1)) + (loc.y * loc.y) + ((loc.z - z1) * (loc.z - z1)) );

    if(index >=0){
    ebullet[index].loc.x=loc.x;
    ebullet[index].loc.y=loc.y;
    ebullet[index].loc.z=loc.z;
    ebullet[index].directionX = anglex;
    ebullet[index].directionY = 0;
    ebullet[index].xStart = loc.x;
    ebullet[index].zStart =loc.z;
    ebullet[index].shootBullet =true;
    }
}
void EnemyBot::getPlayerPos(float x, float z){
    this->x1 = x;
    this->z1 = z;
}

void EnemyBot::loadAmmo() // loads 10 bullets for bot, when ammo is empty, this method will be called in the update to refill ammo.
{
    if(ebullet.size() == 0)
    {
        for(int i = 0; i < 1; i++)
        {
            Location loc = Location(loc.x, loc.y, loc.z);
            EnemyBullet b = EnemyBullet(0.2, loc, 0.0f,0.0f);
            ebullet.push_back(b);
        }
        index = ebullet.size()-1;
    }
}
void EnemyBot::updateEnemyBot()
{

loadAmmo();

    float RP = sqrt(((loc.x - x1) * (loc.x - x1)) + ((loc.z - z1) * (loc.z - z1)) );

    bulletTimer++;
    //cout << bulletTimer<<endl;

    if(bulletTimer >= 20 && RP < 30){
    bulletTimer = 0;
    fire(initialAngle());
    index--;
}

    //srand((unsigned)time(0));
    if(isCollide){
        xStart = loc.x;
        zStart = loc.z;
        direction = (rand() % 360);
        isCollide = false;
        distance = 0;
    }

   else if(collide || loc.x > 98 || loc.x < -98 || loc.z > 98 || loc.z < -98 || distance > 10 || isCollisionMountain()|| isCollisionCrater()){
            xStart = loc.x;
    zStart = loc.z;
        direction = (rand() % 360);
        distance = 0;
    }

        loc.z += sin(((direction + 25) / 180 * 3.141592654f) - 90) * speed;
        loc.x += cos(((direction + 25) / 180 * 3.141592654f) - 90) * speed;
         distance = sqrt(((loc.x - xStart) * (loc.x - xStart)) + ((loc.z - zStart) * (loc.z - zStart)));
}

EnemyBot::~EnemyBot(){
}


