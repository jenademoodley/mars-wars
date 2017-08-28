#ifndef PLAYER_H
#define PLAYER_H
#include "objLoader.h"
#include "RenderableObject.h"
#include "Mountain.h"
#include "EnemyBot.h"
#include "CraterBot.h"
#include "boss.h"
#include <vector>
class Player: public RenderableObject
{
private:
    float x;
    float z;
    string o ;
    void drawGun();

public:
    Location c_loc;
    int health;
    int score = 0;
    float directionX;
    float directionY;
    float dirX;
    float dirY;
    objLoader obj = objLoader(o);
    vector <Mountain>* mountain;
    vector  <EnemyBot>* enemy;
    vector  <CraterBot>* crater;
    vector <boss>* vboss;
    Player(Location& location);
    Player(Location& location, vector <Mountain>* mountain , vector <EnemyBot>* enemy, vector <CraterBot>* crater, vector <boss>* vboss,float dirX, float dirY);
    void render();
    void update();
    void setHealth(int h);
    void updatePlayer(float x, float z, float directionX, float directionY);
    bool isCollisionWorld(float x2, float z2);
    bool isCollisionNPC(float x2, float z2);
    bool isCollision(float x1, float y1, float z1, float radius, float x2, float z2);
    void increaseScore(int points);


};

#endif





