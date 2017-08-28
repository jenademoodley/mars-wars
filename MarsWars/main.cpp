#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <vector>
#include <random>
#include <cstdlib>
#include <iterator>// for rand
#include <sstream> // for ostringstream
#include <algorithm> // for sort
#include <ctime>
//Other Classes
#include "World.h"
#include "CraterBot.h"
#include "EnemyBot.h"
#include "Mountain.h"
#include "HUD.h"
#include "HealthItem.h"
#include "WaveBuffer.h"
#include "PlayFile.h"
#include "ReadSoundFileNames.h"
#include "Sunlight.h"
#include "Fog.h"
#include "bullet.h"
#include "Player.h"
#include "HealthItem.h"
#include "Ammo.h"
#include "SideMission.h"
#include "boss.h"
#define PI 3.14159265
using namespace std;
default_random_engine generator;

//Object Vector Decl
vector<CraterBot> v_CraterBot;
vector<EnemyBot> v_EnemyBot;
vector<Mountain> v_Mountain;
vector <bullet> v_bullet;
vector <HealthItem> v_Health;
vector <Ammo> v_Ammo;
vector <SideMission> v_Side;
vector <boss> BOSS;
vector <string> v_SoundNames;
//Sound Var
WaveBuffer shoot("C:\\sounds\\shot.WAV");//Loads file into memory so it plays faster
string soundPath = "C:\\sounds";

//float variables
float xpos =95;
float ypos = 0;
float zpos = 95;
float xrot= 360;
float yrot= 180;
float MouseSpeed =  0.5;
float lastXValue;
float lastYValue = 0;
float xrotrad, yrotrad;
float tempx = xpos;
float tempz = zpos;
float previousx;
float previousz;
float movedx;
float movedz;
float worldSize = 100.0;

//bool variables
bool arr [200] [200];
bool shot = 0;//CrossHair Colour changer
bool playerDeath1  = true;
bool playerDeath2  = true;
bool playerDeath3  = true;
bool playerDeath4  = true;
bool level1  = true;
bool level2  = true;
bool level3  = true;
bool level4  = true;
bool level5  = true;
bool start = false;
bool endgame = false;
bool wingame = false;
// int variables
int levelNum = 0; //variable to track level number
int c = 0;
int score = 0;
int bulletTimer1 = 0;
int bulletTimer2 = 0;
 long endTime;
 long  startTime;
//Object Variables
World world ;//(Ground, Sky, World, Sun Speed)
HUD hud;
Sunlight sunlight;
extern Location l = Location(0,0,0);
extern Player player = Player(l);

//Method Decl
void mouseClick (int button, int state, int x, int y);
void mouseMovement(int x, int y);
void keyPressed(unsigned char key, int x, int y);
void keySpecial(int key, int x, int y);
void keyJoystick(unsigned int button, int x, int y, int z);
void camera (void);
void displayState();
void DrawTextXY(double x,double y,double z,double scale,char *s);
char* convertInt(int num);
void up();
void down();
void left();
void right();
void operations();
void upJoystick();
void downJoystick();
void leftJoystick();
void rightJoystick();
void displayStart();
void displayEnd();
void displayWin();
void startplay();
void gameplay();
void endplay();
void dying();
void initializeMountain(int s);
void initializeCrater(int s);
void initializeEnemy(int s, float speed);
void initializeHealth(int s);
void initializeAmmo(int s);
void initializeSideItem(int s);
void initializeBullet(int s);
void initializeBoss(int s);
void LevelUp(int numC, int numE, float speedE);
void collisions();
void bossCollisions();
void enemybotCollisions();
void craterbotCollisions();
void bulletCollisions();
float calculateRotation(float ex, float ez);
void display(void);
void reshape(int width, int height);
void Timer(int v);


void initializeMountain(int s){
    int counter = s;
     while(counter > 0){
            uniform_int_distribution<int> distribution(4,10);
            int size = distribution(generator);
            int x = (rand()%179-89);
            int z = (rand()%179-89);
            for(int i=(x - size)+100; i<(x + size)+100; i++){
                    for(int j=(z - size)+100;j<(z + size)+100; j++)
                            arr[i][j] = true;
            }
            Location loc = Location(x , -5 , z);
            Mountain temp = Mountain(size, loc);
            v_Mountain.push_back(temp);
            counter--;
        }
}

void initializeCrater(int s){
int counter = s;
    while(counter > 0)
    {
        bool found = false;
        int x = (rand()%191-95);
        int z = (rand()%191-95);
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++){
                if(arr[i][j]==true){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++)
                arr[i][j]=true;
        }
        Location loc = Location(x , 0 , z);
        CraterBot temp = CraterBot(loc);
        v_CraterBot.push_back(temp);
        counter--;
        }
    }
}

void initializeEnemy(int s, float speed){
int counter = s;
    while(counter > 0)
    {
        bool found = false;
        int x = (rand()%191-95);
        int z = (rand()%191-95);
        for(int i= (x-2)+100; i<(x+2)+100; i++){
            for(int j=(z-2)+100; j<(z+2)+100; j++){
                if(arr[i][j]==true){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++)
                arr[i][j]=true;
        }
        Location loc = Location(x , 0 , z);
        EnemyBot temp = EnemyBot(loc, &v_Mountain, &v_CraterBot, speed);
        v_EnemyBot.push_back(temp);
        counter--;
    }
    }
}

void initializeHealth(int s){
int counter = s;
    while(counter > 0)
    {
        bool found = false;
        int x = (rand()%191-95);
        int z = (rand()%191-95);
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++){
                if(arr[i][j]==true){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++)
                arr[i][j]=true;
        }
        Location loc = Location(x , 0 , z);
        HealthItem temp = HealthItem(loc);
        v_Health.push_back(temp);
        counter--;
    }
    }
}

void initializeAmmo(int s){
    int counter = s;
    while(counter > 0)
    {
        bool found = false;
        int x = (rand()%191-95);
        int z = (rand()%191-95);
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++){
                if(arr[i][j]==true){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++)
                arr[i][j]=true;
        }
        Location loc = Location(x , 0 , z);
        Ammo temp = Ammo(loc);
        v_Ammo.push_back(temp);
        counter--;
    }
    }
}

void initializeSideItem(int s){
int counter = s;
    while(counter > 0)
    {
        bool found = false;
        int x = (rand()%191-95);
        int z = (rand()%191-95);
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++){
                if(arr[i][j]==true){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
        for(int i= (x-1)+100; i<(x+1)+100; i++){
            for(int j=(z-1)+100; j<(z+1)+100; j++)
                arr[i][j]=true;
        }
        Location loc = Location(x , 0 , z);
        SideMission temp = SideMission(loc);
        v_Side.push_back(temp);
        counter--;
    }
    }
}

void initializeBullet(int s){
for(int i=0; i<s; i++)
    {
        Location loc = Location(xpos - 0.06,0,zpos - 5);
        bullet b = bullet(loc , 0.0f, 0.0f);
        v_bullet.push_back(b);
    }
    c = v_bullet.size()-1;
}

void initializeBoss(int s){
    int counter = s;
    while(counter > 0)
    {
        bool found = false;
        int x = (rand()%161-80);
        int z = (rand()%161-80);
        for(int i= (x-17)+100; i<(x+17)+100; i++){
            for(int j=(z-17)+100; j<(z+17)+100; j++){
                if(arr[i][j]==true){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
        for(int i= (x-17)+100; i<(x+17)+100; i++){
            for(int j=(z-17)+100; j<(z+17)+100; j++)
                arr[i][j]=true;
        }
        Location loc = Location(x , 7 , z);
        boss temp = boss(loc, &v_Mountain);\
        BOSS.push_back(temp);
        counter--;
    }
    }
}

void LevelUp(int numC, int numE, float speedE){
        xpos = 95;
        zpos = 95;
        yrot = 180;
        xrot = 0;

            for(int i=0; i < 200; i++){
                    for(int j=0; j< 200; j++)
                        arr[i][j]=false;
                }
       v_Mountain.clear();
       v_EnemyBot.clear();
       v_CraterBot.clear();
       v_Health.clear();
       v_Ammo.clear();
       v_Side.clear();
    ReadSoundFileNames SoundNames(soundPath);
    //SoundNames.shuffleNames();
    v_SoundNames = SoundNames.getNames();
    PlayFile("sounds\\"+v_SoundNames[4]);//Systems responding 4     3,6,7,9,10,11,12,13,14

    initializeMountain(36);
    initializeCrater(numC);
    initializeEnemy(numE, speedE);
    initializeHealth(12);
    initializeAmmo(12);
    initializeSideItem(10);

    Location loc = Location(xpos - 0.06, 0, zpos - 5+0.8);
    player =  Player(loc, &v_Mountain,&v_EnemyBot, &v_CraterBot, &BOSS, yrot, xrot);
    for(int i=0 ; i <v_EnemyBot.size(); i++){
        v_EnemyBot[i].x1 = player.loc.x;
        v_EnemyBot[i].z1 = player.loc.z;
    }
    world = World(-2, 40, worldSize, 0.05);


}

void bossLevel(int numB){
    xpos = 95;
        zpos = 95;
        yrot = 180;
        xrot = 0;

            for(int i=0; i < 200; i++){
                    for(int j=0; j< 200; j++)
                        arr[i][j]=false;
                }
       v_Mountain.clear();
       v_EnemyBot.clear();
       v_CraterBot.clear();
       v_Health.clear();
       v_Ammo.clear();
       v_Side.clear();
       ReadSoundFileNames SoundNames(soundPath);
    //SoundNames.shuffleNames();
    v_SoundNames = SoundNames.getNames();
    PlayFile("sounds\\"+v_SoundNames[4]);//Systems responding 4     3,6,7,9,10,11,12,13,14

    initializeMountain(36);
    initializeBoss(numB);
    initializeHealth(12);
    initializeAmmo(12);
    initializeSideItem(10);

    Location loc = Location(xpos - 0.06, 0, zpos - 5+0.8);
    player =  Player(loc, &v_Mountain,&v_EnemyBot, &v_CraterBot, &BOSS, yrot, xrot);
    for(int i=0; i<BOSS.size(); i++){
        BOSS[i].getPlayerPos(player.loc.x, player.loc.z);
    }
    world = World(-2, 40, worldSize, 0.05);
}

void initGL(){
 glutWarpPointer(359, 359);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMovement);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyPressed);
    glutSpecialFunc(keySpecial);
    glutJoystickFunc(keyJoystick, 0);
    srand((unsigned)time(NULL));
 glutTimerFunc(0,Timer,0);

 glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Des black background, need to add white stars somehow
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHTING); // turns on the lighting model in OpenGL
    glEnable(GL_LIGHT0);  // enables light 0
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST); // turns on hidden surface removal so that objects behind other objects do not get displayed

    //Init Sound
    ReadSoundFileNames SoundNames(soundPath);
    //SoundNames.shuffleNames();
    v_SoundNames = SoundNames.getNames();
    PlayFile("sounds\\"+v_SoundNames[4]);//Systems responding 4     3,6,7,9,10,11,12,13,14


    initializeMountain(36);
    initializeCrater(5);
    initializeEnemy(5 , 0.05);
    initializeHealth(12);
    initializeAmmo(12);
    initializeSideItem(10);
    initializeBullet(100);
Location loc = Location(xpos - 0.06, 0, zpos - 5+0.8);
     player =  Player(loc, &v_Mountain,&v_EnemyBot, &v_CraterBot,&BOSS, yrot, xrot);
    for(int i=0 ; i <v_EnemyBot.size(); i++){
        v_EnemyBot[i].x1 = player.loc.x;
        v_EnemyBot[i].z1 = player.loc.z;
    }
    world = World(-2, 40, worldSize, 0.05);
    levelNum++;
}



void display(void)
{
    glEnable(GL_BLEND);//helps us with transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if(start && !(endgame||wingame))
    camera();
}

void reshape(int width, int height) //this method takes the width and height of the window at the point in time
{
    glViewport(0,0,(GLsizei)width,(GLsizei)height);//set our viewport to the size of our window
    glMatrixMode(GL_PROJECTION);//switch to matrix mode so we can manipulate how our scene is viewed
    glLoadIdentity();//We reset the projection matrix to the identity matrix to avoid artifacts
    gluPerspective(60,(GLfloat)width/(GLfloat)height,1.0,280.0);//60 = our field of view //(GLfloat)width/(GLfloat)height = our aspect ratio //1.0 = near plane //280 = far plane
    glMatrixMode(GL_MODELVIEW);//Now we need to switch back to the model view matrix
}

void startplay(){
    glTranslatef(0.0f, 0.0f,5.0f);//push everything back 5 units || VERY IMPORTANT DONT TOUCH
    world.render();
    sunlight.render(world.sunX, world.sunY, world.sunZ);
    for (int i = 0;i < v_Mountain.size(); i++)
        v_Mountain[i].render();
    player.render();
    displayStart();
    glutSwapBuffers();
}

void gameplay(){

endTime = time(0);
   // const long double sysTimeMS = sysTime * 1000;
   // cout << startTime << endl;
     glTranslatef(0.0f, 0.0f,5.0f);//push everything back 5 units || VERY IMPORTANT DONT TOUCH
world.render();
    sunlight.render(world.sunX, world.sunY, world.sunZ);


       for (int i = 0;i < v_CraterBot.size(); i++)
        v_CraterBot[i].render();

     for (int i = 0;i < v_EnemyBot.size(); i++){
        v_EnemyBot[i].render();
     }

    for (int i = 0;i < v_Mountain.size(); i++)
        v_Mountain[i].render();

        for(int i=0; i<BOSS.size(); i++)
        BOSS[i].render();

   for(int i=0; i<v_bullet.size(); i++)
     {
        if(v_bullet[i].shootBullet) {  //draw bullet if fired{
            v_bullet[i].render();
        }
     }
     glPushMatrix();
     for(int i=0; i < v_Health.size(); i++)
       v_Health[i].render();

    for(int i=0; i < v_Ammo.size(); i++)
       v_Ammo[i].render();

    for(int i=0; i < v_Side.size(); i++)
       v_Side[i].render();
    glPopMatrix();

player.render();
    hud.render(shot);
    Fog(player.health);
    displayState();
    glutSwapBuffers(); //glFlush(); replaced with because i changed to a double buffer in main
}


void endplay(){
    xpos = 0;
    zpos = 0;

//cout << endTime << endl;
//cout << endTime - startTime <<endl;
    gluLookAt(0, 0, 0,
               0, 0,  10,
              0 , 1 , 0);
    glTranslatef(0.0f, 0.0f,5.0f);//push everything back 5 units || VERY IMPORTANT DONT TOUCH

    world.render();
    sunlight.render(world.sunX, world.sunY, world.sunZ);
    for (int i = 0;i < v_Mountain.size(); i++)
        v_Mountain[i].render();
    player.render();
    if(endgame)
    displayEnd();

    else if(wingame)
        displayWin();

    glutSwapBuffers();
}

void bossCollisions(){
    for(int j=0; j<BOSS.size(); j++){
                for(int k=0; k<BOSS.size(); k++){

                if(j!= k && BOSS[j].isCollisionBoss(BOSS[k].loc.x, BOSS[k].loc.y ,BOSS[k].loc.z ,BOSS[k].getRadius())){
                    BOSS[j].collide = false;
                    BOSS[k].collide = false;
                }
            }

            for(int k=0; k<BOSS[j].ebullet.size(); k++){
                    if(BOSS[j].ebullet[k].isCollision(&(player.loc.x), &(player.loc.y), &(player.loc.z), player.getRadius())) {
                  BOSS[j].ebullet.erase(BOSS[j].ebullet.begin() + k);
               player.setHealth(100);
                    }

            for(int i =0; i< v_Mountain.size(); i++){
                        if(BOSS[j].ebullet[k].isCollision((&v_Mountain[i].loc.x), (&v_Mountain[i].loc.y+5), (&v_Mountain[i].loc.z), v_Mountain[i].getRadius())) {
                  BOSS[j].ebullet.erase(BOSS[j].ebullet.begin() + k);
                  v_Mountain.erase(v_Mountain.begin() + i);
                        }
            }
            }
            }
}

void enemybotCollisions(){
    for(int j=0; j< v_EnemyBot.size(); j++) //enemybot collision
            {
                for(int k=0; k< v_EnemyBot.size(); k++){//enemybot bullets collision

                if(j!= k && v_EnemyBot[j].isCollisionEnemyBot(v_EnemyBot[k].loc.x,  v_EnemyBot[k].loc.y  ,v_EnemyBot[k].loc.z  ,v_EnemyBot[k].getRadius())){
                    v_EnemyBot[j].collide = false;
                    v_EnemyBot[k].collide = false;
                }
            }

               for(int k=0; k<v_EnemyBot[j].ebullet.size(); k++){
                    if(v_EnemyBot[j].ebullet[k].isCollision(&(player.loc.x), &(player.loc.y), &(player.loc.z), player.getRadius())) {
                  v_EnemyBot[j].ebullet.erase(v_EnemyBot[j].ebullet.begin() + k);
               player.setHealth(10);
                    }

                    for(int i =0; i< v_Mountain.size(); i++){
                        if(v_EnemyBot[j].ebullet[k].isCollision((&v_Mountain[i].loc.x), (&v_Mountain[i].loc.y+5), (&v_Mountain[i].loc.z), v_Mountain[i].getRadius())) {
                  v_EnemyBot[j].ebullet.erase(v_EnemyBot[j].ebullet.begin() + k);
                    }
               }
               for(int i =0; i< v_CraterBot.size(); i++){
                        if(v_EnemyBot[j].ebullet[k].isCollision((&v_CraterBot[i].loc.x), (&v_CraterBot[i].loc.y+5), (&v_CraterBot[i].loc.z), v_CraterBot[i].getRadius())) {
                  v_EnemyBot[j].ebullet.erase(v_EnemyBot[j].ebullet.begin() + k);
                    }
               }
            }
            }
}

void craterbotCollisions(){
           for(int j=0; j< v_CraterBot.size(); j++)    //craterbots bullet collision
            {
               for(int k=0; k<v_CraterBot[j].botAmmo.size(); k++){
                    if(v_CraterBot[j].botAmmo[k].isCollision(&(player.loc.x), &(player.loc.y), &(player.loc.z), player.getRadius())){
                  v_CraterBot[j].botAmmo.erase(v_CraterBot[j].botAmmo.begin() + k);
                    player.health-=10;
                    }

                    for(int i =0; i< v_Mountain.size(); i++){
                        if(v_CraterBot[j].botAmmo[k].isCollision((&v_Mountain[i].loc.x), (&v_Mountain[i].loc.y+5), (&v_Mountain[i].loc.z), v_Mountain[i].getRadius())) {
                  v_CraterBot[j].botAmmo.erase(v_CraterBot[j].botAmmo.begin() + k);
                    }
               }

               for(int i =0; i< v_EnemyBot.size(); i++){
                        if(v_CraterBot[j].botAmmo[k].isCollision((&v_EnemyBot[i].loc.x), (&v_EnemyBot[i].loc.y), (&v_EnemyBot[i].loc.z), v_EnemyBot[i].getRadius())) {
                  v_CraterBot[j].botAmmo.erase(v_CraterBot[j].botAmmo.begin() + k);
                    }
               }
               }

            }
}

void bulletCollisions(){
    for(int i=0; i<v_bullet.size(); i++)    //player bullet collisions
    {
        if(v_bullet[i].shootBullet)
        {
            for(int j=0; j< v_EnemyBot.size(); j++)
            {
               for(int k=0; k<v_EnemyBot[j].ebullet.size(); k++){
                if(v_EnemyBot[j].ebullet[k].isCollision(&(v_bullet[i]).loc.x, &(v_bullet[i]).loc.y, &(v_bullet[i]).loc.z, v_bullet[i].getRadius())){
                  v_EnemyBot[j].ebullet.erase(v_EnemyBot[j].ebullet.begin() + k);
                   v_bullet.erase(v_bullet.end());
                }
               }

                if(v_EnemyBot[j].isCollision(v_bullet[i]))
                {
                    v_EnemyBot[j].health-=2;
                   v_bullet.erase(v_bullet.end());
                    if(v_EnemyBot[j].health <= 0){
                    v_EnemyBot.erase(v_EnemyBot.begin() + j);
                     score+=500;
                    PlayFile("sounds\\"+v_SoundNames[3 + j]);
                    }
                }
            }
            for(int j=0; j< v_CraterBot.size(); j++)
            {
                for(int k=0; k<v_CraterBot[j].botAmmo.size(); k++){
                if(v_CraterBot[j].botAmmo[k].isCollision(&(v_bullet[i]).loc.x, &(v_bullet[i]).loc.y, &(v_bullet[i]).loc.z, v_bullet[i].getRadius())){
                  v_CraterBot[j].botAmmo.erase(v_CraterBot[j].botAmmo.begin() + k);
                   v_bullet.erase(v_bullet.end());
                }
                }

                if(v_CraterBot[j].isCollision(v_bullet[i]))
                {
                    v_bullet.erase(v_bullet.end());
                    v_CraterBot[j].hit++;
                    if(v_CraterBot[j].hit >= 2){
                    v_CraterBot.erase(v_CraterBot.begin() + j);
                     score+=250;

                    PlayFile("sounds\\"+v_SoundNames[13 + j]);
                    }
                }
            }
            for(int j=0; j< v_Mountain.size(); j++)
            {
                if(v_Mountain[j].isCollision(v_bullet[i]))
                {
                    v_bullet.erase(v_bullet.end());
                    PlayFile("sounds\\hit.WAV");
                }
            }

            for(int j=0; j< BOSS.size(); j++)
            {
               for(int k=0; k<BOSS[j].ebullet.size(); k++){
                if(BOSS[j].ebullet[k].isCollision(&(v_bullet[i]).loc.x, &(v_bullet[i]).loc.y, &(v_bullet[i]).loc.z, v_bullet[i].getRadius())){
                 v_bullet.erase(v_bullet.end());
                 BOSS[j].ebullet[k].hits--;
                 if(BOSS[j].ebullet[k].hits==0)
                  BOSS[j].ebullet.erase(BOSS[j].ebullet.begin() + k);
                }
               }

                if(BOSS[j].isCollision(v_bullet[i]))
                {
                    BOSS[j].health-=10;
                   v_bullet.erase(v_bullet.end());
                    if(BOSS[j].health <= 0){
                    BOSS.erase(BOSS.begin() + j);
                     score+=10000;
                    PlayFile("sounds\\"+v_SoundNames[3 + j]);
                    }
                }
            }
        }
        if(v_bullet[i].finish())
            v_bullet.erase(v_bullet.end());
    }
    }

void collisions(){
    if(start){
    bossCollisions();
    enemybotCollisions();
    craterbotCollisions();
    bulletCollisions();
    }
}

void dying(){
    if (player.health < 800 && playerDeath1)
    {
        PlayFile("sounds\\death.WAV");
        playerDeath1 = false;
    }
    if (player.health < 600 && playerDeath2)
    {
        PlayFile("sounds\\death.WAV");
        playerDeath2 = false;
    }
    if (player.health < 400 && playerDeath3)
    {
        PlayFile("sounds\\death.WAV");
        playerDeath3 = false;
    }
    if (player.health < 200 && playerDeath4)
    {
        PlayFile("sounds\\death.WAV");
        playerDeath4 = false;
    }

    if(player.health <= 0){

endgame = true;
    }
}


void Timer(int v)
{
    if(!start)
   startplay();

else if(start && (endgame || wingame))
  endplay();

else if (start && !(endgame || wingame))
gameplay();

     player.updatePlayer(xpos , zpos - 5, yrot, xrot);

    dying();
glPushMatrix();
        if(v_EnemyBot.size()<= 0 && v_CraterBot.size() <= 0 && level1 && levelNum == 1){
            level1 = false;
            levelNum++;
            LevelUp(7, 8, 0.08);

        }

        else if(v_EnemyBot.size()<= 0 && v_CraterBot.size() <= 0 && level2 && levelNum == 2){
            level2 = false;
            levelNum++;
            LevelUp(10, 10, 0.1);
        }

       else if(v_EnemyBot.size()<= 0 && v_CraterBot.size() <= 0 && level3 && levelNum == 3){
            level3 = false;
            levelNum++;
            LevelUp(15, 15, 0.12);
        }

        else if(v_EnemyBot.size()<= 0 && v_CraterBot.size() <= 0 && level4 && levelNum == 4){
            level4 = false;
            levelNum++;
            bossLevel(1);
        }

        else if(BOSS.size() == 0 && level5 && levelNum==5)
            wingame = true;

glPopMatrix();
collisions();

    glutTimerFunc(1,Timer,0);
    glutPostRedisplay();
}

int main(int argc, char **argv)//argc and argv allow us to add command line arguments
{
    int m = MessageBox(NULL, "Do you want to run MarsWars In Fullscreen Mode?", "MarsWars", MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON1);
    if (m == 6)
    {
        try
        {
            glutInit(&argc, argv); //initialize GLUT
            glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); //set the display to Double buffer, with depth
            glutGameModeString("1366×768:32@60");
            glutEnterGameMode();
            initGL();
            glutMainLoop();
        }
        catch (exception e)
        {
            int m1 = MessageBox(NULL, e.what(), "MarsWars", MB_ICONERROR);
        }
    }

    else if (m == 7)
    {
        glutInit(&argc, argv); //initialize GLUT
        glutInitWindowSize(1024,768); //Sets width and Height of our GLUT window
        glutInitWindowPosition(0,0); //Sets the position of the GLUT window on our screen
        glutCreateWindow("Mars Wars!!"); //Set title for window
        initGL();
        glutMainLoop();
    }

    else if (m  == 2)
    {
        exit (0);
    }
}

void keyJoystick(unsigned int button, int x, int y, int z)
{
    if (x == -1000)
        yrot -= 0.5;

    if (x == 1000)
        yrot += 0.5;

    if (y == -1000){

            float txr = xrot + 0.5;
        if(txr >=270 && txr <=360)
        xrot +=0.5;
    }

    if (y == 1000){
            float txr = xrot - 0.5;
        if(txr >=270 && txr <=360)
        xrot -=0.5;
    }

    if (button & 0x01)//button1
        upJoystick();

    if (button & 0x02)//button2
        rightJoystick();

    if (button & 0x04)//button3
       downJoystick();

    if (button & 0x08)//button4
        leftJoystick();

    if (button & 0x10)//button5
        mouseClick (GLUT_RIGHT_BUTTON, GLUT_DOWN, 0, 0);

    if (button & 0x20)//button6
    {
       bulletTimer1++;
       if(bulletTimer1 == 5) {
   mouseClick (GLUT_LEFT_BUTTON, GLUT_DOWN, 0, 0);
   bulletTimer1 = 0;
       }
    }


    if (button & 0x40)//button7
        mouseClick (GLUT_RIGHT_BUTTON, GLUT_DOWN, 0, 0);

    if (button & 0x80)//button8
       bulletTimer1++;
       if(bulletTimer1 == 5) {
   mouseClick (GLUT_LEFT_BUTTON, GLUT_DOWN, 0, 0);
   bulletTimer1 = 0;
       }

    if (button & 0x100)//button9
        mouseClick (GLUT_MIDDLE_BUTTON, GLUT_DOWN, 0, 0);

    if (button & 0x200)//button10
        keyPressed(13, 0, 0);
}

void mouseMovement(int x, int y)
{
    glutSetCursor(GLUT_CURSOR_NONE);
    int differenceX = x- lastXValue; //check the difference between the current x and the last x position
    int differenceY = y - lastYValue;
    lastXValue = x; //set lastx to the current x position
    lastYValue = y;

    float txr =  xrot - (float) differenceY/4;
        if(txr >= 270 && txr <=360)
    xrot -= (float) differenceY/4;

    yrot += (float) differenceX;
}

void mouseClick (int button, int state, int x, int y)
{
        //Left Click
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
           // PlayFile ("sounds\\shot.WAV");//Loads file then plays it
            ////Plays file already in RAM
           if (c >= 0 && start){
            v_bullet[c].loc.x=xpos - 0.06;
            v_bullet[c].loc.y=ypos;
            v_bullet[c].loc.z=zpos - 5;
            v_bullet[c].directionX = yrot;
            v_bullet[c].directionY = xrot;
            v_bullet[c].xStart = xpos - 0.06;
            v_bullet[c].zStart = zpos - 5;
                    v_bullet[c].shootBullet =true;
                     shoot.play(0);
                    std::cout << "Pew Pew Pew\n";
                    cout << "Mountains: " << v_Mountain.size() << endl;
                    cout << "Bullets: " << v_bullet.size() << endl;
                    cout << "EnemyBots: " << v_EnemyBot.size()<< endl;
                    cout << "CraterBots: " << v_CraterBot.size()<< endl;
                    cout << "Player X: " << player.loc.x << endl;
                    cout << "Player Z: "  << player.loc.z << endl;
                    cout << player.health << endl;
                    cout << c <<endl;
                    c--;
                    shot = 1;
                }
            glutPostRedisplay();
        }
        if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        {
            if(start){
            std::cout << "No Pew Pew Pew\n";
            shot = 0;
            }
        }
        //Right Click
        if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
            std::cout << "Reload\n";

        if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
        {
        }
        //Middle Click
        if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
            std::cout << "Weapon Changed\n";

        if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP)
        {
        }
}

void up(){
            yrotrad = (yrot / 180 * 3.141592654f);//angle at which you have rotated left or right
            xrotrad = (xrot / 180 * 3.141592654f);//angle at which you have rotated up or down
            tempx = xpos + float(sin(yrotrad));
            //*********This applies to all cases for the movement*********************
            //Check collision detection between the temporary x and z values of the player class. Use
            //temporary values as, if there is a collision, we are still able to move the player and camera
            //as the original values of x and z will only change if there is no collision
            if(tempx + 2 < 99 && tempx - 2 > -99  && !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz))){
            previousx = xpos;
            xpos += float(sin(yrotrad)) ;//calculate pos on x axis
            movedx = xpos;
            }

            tempz = zpos - float(cos(yrotrad)) ;
            if(tempz + 2 < 99 && tempz - 2 > -99 && !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
            //calculate pos on y axis
            {
                previousz = zpos;
                zpos -= float(cos(yrotrad)) ;
                movedz = zpos;
            }

}

void upJoystick(){
     yrotrad = (yrot / 180 * 3.141592654f);//angle at which you have rotated left or right
            xrotrad = (xrot / 180 * 3.141592654f);//angle at which you have rotated up or down
            tempx = xpos + float(sin(yrotrad));
            //*********This applies to all cases for the movement*********************
            //Check collision detection between the temporary x and z values of the player class. Use
            //temporary values as, if there is a collision, we are still able to move the player and camera
            //as the original values of x and z will only change if there is no collision
            if(tempx + 2 < 99 && tempx - 2 > -99  && !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz))){
                    previousx = xpos;
            xpos += float(sin(yrotrad))/4 ;//calculate pos on x axis
            movedx = xpos;
            }

            tempz = zpos - float(cos(yrotrad)) ;
            if(tempz + 2 < 99 && tempz - 2 > -99 && !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
            //calculate pos on y axis
            {
                previousz = zpos;
                zpos -= float(cos(yrotrad))/4 ;
                movedz = zpos;
            }
            operations();
}

void down(){
     yrotrad = (yrot / 180 * 3.141592654f);
            xrotrad = (xrot / 180 * 3.141592654f);

            tempx = xpos - float(sin(yrotrad));
            if(tempx + 2 < 99 && tempx - 2 > -99  && !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz))){
                    previousx = xpos;
            xpos -= float(sin(yrotrad)) ;//calculate pos on x axis
            movedx = xpos;
            }

            tempz = zpos + float(cos(yrotrad)) ;
            if(tempz + 2 < 99 && tempz - 2 > -99&& !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
            {
                previousz = zpos;
                zpos += float(cos(yrotrad)) ;
                movedz = zpos;
            }

}

void downJoystick(){
     yrotrad = (yrot / 180 * 3.141592654f);
            xrotrad = (xrot / 180 * 3.141592654f);

            tempx = xpos - float(sin(yrotrad));
            if(tempx + 2 < 99 && tempx - 2 > -99  && !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz))){
                    previousx = xpos;
            xpos -= float(sin(yrotrad)) /4;//calculate pos on x axis
            movedx = xpos;
            }

            tempz = zpos + float(cos(yrotrad)) ;
            if(tempz + 2 < 99 && tempz - 2 > -99&& !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))

            {
                previousz = zpos;
                zpos += float(cos(yrotrad))/4 ;
                movedz = zpos;
            }


            operations();
}

void left(){
    yrotrad = (yrot / 180 * 3.141592654f);
            tempx = xpos - float(cos(yrotrad));
            if(tempx + 2 < 99 && tempx - 2 > -99&& !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
            {
                    previousx = xpos;
            xpos -= float(cos(yrotrad)) * 0.3;//calculate pos on x axis
            movedx = xpos;
            }

            tempz = zpos - float(sin(yrotrad)) ;
            if(tempz + 2 < 99 && tempz - 2 > -99&& !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))

            {
                previousz = zpos;
                zpos -= float(sin(yrotrad)) * 0.3;
                movedz = zpos;
            }
}

void leftJoystick(){
    yrotrad = (yrot / 180 * 3.141592654f);
            tempx = xpos - float(cos(yrotrad));
            if(tempx + 2 < 99 && tempx - 2 > -99&& !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
            {
            previousx = xpos;
            xpos -= float(cos(yrotrad)) * 0.15;//calculate pos on x axis
            movedx = xpos;
            }

            tempz = zpos - float(sin(yrotrad)) ;
            if(tempz + 2 < 99 && tempz - 2 > -99&& !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
            {
                previousz = zpos;
                zpos -= float(sin(yrotrad)) * 0.15;
                movedz = zpos;
            }
            operations();
}

void right(){
     yrotrad = (yrot / 180 * 3.141592654f);
            tempx = xpos + float(cos(yrotrad));
            if(tempx + 2 < 99 && tempx - 2 > -99&& !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
            {
            previousx = xpos;
            xpos += float(cos(yrotrad)) * 0.3;//calculate pos on x axis
            movedx = xpos;
            }
            tempz = zpos + float(sin(yrotrad)) ;
            if(tempz + 2 < 99 && tempz - 2 > -99 && !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))

             {
                previousz = zpos;
               zpos += float(sin(yrotrad)) * 0.3;
                movedz = zpos;
            }
}

void rightJoystick(){
     yrotrad = (yrot / 180 * 3.141592654f);
            tempx = xpos + float(cos(yrotrad));
            if(tempx + 2 < 99 && tempx - 2 > -99&& !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
            {
            previousx = xpos;
            xpos += float(cos(yrotrad)) * 0.15;//calculate pos on x axis
            movedx = xpos;
            }

            tempz = zpos + float(sin(yrotrad)) ;
            if(tempz + 2 < 99 && tempz - 2 > -99 && !(player.isCollisionWorld(tempx, tempz)) && !(player.isCollisionNPC(tempx, tempz)))
           {
                previousz = zpos;
               zpos += float(sin(yrotrad)) * 0.15;
                movedz = zpos;
            }

            operations;
}

void operations(){
for(int i=0; i<BOSS.size(); i++)
BOSS[i].getPlayerPos(player.loc.x, player.loc.z);

     for (int i = 0;i < v_CraterBot.size(); i++)
        v_CraterBot[i].getPlayerPos(player.loc.x, player.loc.z); //allows Craterbots to obtain players position for targeting system

     for (int i = 0;i < v_EnemyBot.size(); i++)
        v_EnemyBot[i].getPlayerPos(player.loc.x, player.loc.z);//allows Enemy bots to obtain players position for targeting system

        for(int i=0; i<v_Health.size(); i++){
            if(player.isCollision(v_Health[i].loc.x,v_Health[i].loc.y,v_Health[i].loc.z,v_Health[i].getRadius(), tempx, tempz)){
                if(player.health+300 <=1000)
                    player.health+=300;
                    else
                        player.health = 1000;
                v_Health.erase(v_Health.begin()+i);
            }
        }

        for(int i=0; i<v_Side.size(); i++){
            if(player.isCollision(v_Side[i].loc.x,v_Side[i].loc.y,v_Side[i].loc.z,v_Side[i].getRadius(), tempx, tempz)){
                score+=1000;
                v_Side.erase(v_Side.begin()+i);
            }
        }

            for(int i=0; i<v_Ammo.size(); i++){
                if(player.isCollision(v_Ammo[i].loc.x,v_Ammo[i].loc.y,v_Ammo[i].loc.z,v_Ammo[i].getRadius(), tempx, tempz)){
                        v_Ammo.erase(v_Ammo.begin() + i);
                        v_bullet.clear();
                        initializeBullet(100);
            }
        }
}

void keyPressed(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: //escape
            exit (0);
            break;

        case 119://w
           up();
            break;

        case 115://s
           down();
            break;

        case 100://d
            right();
            break;

        case 97://a
            left();
            break;

        case 13:
            if(!start){
            start = true;
             startTime = time(0);
             cout << startTime<<endl;;
            }
            break;

        case 32:
            mouseClick (GLUT_LEFT_BUTTON, GLUT_DOWN, 0, 0);
            break;
    }

   operations();

}

void keySpecial(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            up();
            break;

        case GLUT_KEY_DOWN:
            down();
            break;

        case GLUT_KEY_RIGHT:
            right();
            break;

        case GLUT_KEY_LEFT:
            left();
            break;
    }

    operations();
    }

void camera (void)
{
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (up and down)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (left and right)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
}

void DrawTextXY(double x,double y,double z,double scale,char *s)
{
   int i;

   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(scale,scale,scale);
   for (i=0;i < strlen(s);i++)
      glutStrokeCharacter(GLUT_STROKE_ROMAN,s[i]);
   glPopMatrix();
}

char* convertInt(int num) //converts integer to char*
{
    stringstream ss;
    ss<<num;
    string str =ss.str();
    char *char1= new char[str.size() + 1];
    strcpy(char1, str.c_str());
    return char1;
}

void displayState()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(1, 800, 0, 600, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(6,0.3,0.08);
    DrawTextXY(25,550,0,0.2,"Health: ");
   DrawTextXY(110,550,0,0.2,convertInt(player.health)); //change in health

    DrawTextXY(600,550,0,0.2,"Wave: ");
    DrawTextXY(670,550,0,0.2,convertInt(levelNum));

    DrawTextXY(300,550,0,0.2,"Score: ");
    DrawTextXY(380,550,0,0.2,convertInt(score));

    if(levelNum == 5){
     DrawTextXY(300,25,0,0.2,"Boss: ");
    DrawTextXY(380,25,0,0.2,convertInt(BOSS[0].health));
    }

    DrawTextXY(600,480,0,0.2,"Enemies: ");
    DrawTextXY(710,480,0,0.2,convertInt(v_EnemyBot.size() + v_CraterBot.size() + BOSS.size()));

    DrawTextXY(25,10,0,0.2,"Ammo: ");
    DrawTextXY(115,10,0,0.2,convertInt(c+1));

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void displayStart()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(1, 800, 0, 600, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(6,0.3,0.08);
    DrawTextXY(350,380,0,0.2,"Mars Wars");
    DrawTextXY(250,300,0,0.2,"Push Enter to start Game");

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}

void displayEnd()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(1, 800, 0, 600, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(6,0.3,0.08);

    DrawTextXY(350,380,0,0.2,"Game Over");
    DrawTextXY(300,340,0,0.2,"Score :");
    DrawTextXY(450,340,0,0.2,convertInt(score));

    DrawTextXY(300,300,0,0.2,"Time :");
    DrawTextXY(450,300,0,0.2,convertInt(endTime - startTime));


    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void displayWin()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(1, 800, 0, 600, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(6,0.3,0.08);

    DrawTextXY(350,380,0,0.2,"You Win!!!");
 DrawTextXY(300,340,0,0.2,"Score :");
    DrawTextXY(450,340,0,0.2,convertInt(score));

    DrawTextXY(300,300,0,0.2,"Time :");
    DrawTextXY(450,300,0,0.2,convertInt(endTime - startTime));


    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
