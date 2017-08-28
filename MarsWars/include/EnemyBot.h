#ifndef ENEMYBOT_H
#define ENEMYBOT_H
#include "RenderableNPC.h"
#include "EnemyBullet.h"
#include "CraterBot.h"
#include "Mountain.h"
class EnemyBot : public RenderableNPC
{
     public:
         vector <CraterBot>* crater;
        vector <Mountain>* mount;
        vector <EnemyBullet> ebullet;
         Location c_loc;
         float x1;
         float z1;
         int index;
         int health;
         float bulletTimer;
         bool isCollide;
         bool collide;
        EnemyBot(Location& location, vector <Mountain>* mountain, vector <CraterBot>* craterbot, float s);
        virtual ~EnemyBot();
        void update();
        void render();
        void loadAmmo();
        void fire(float anglex);
        bool isCollision(bullet a);
        bool isCollisionEnemyBot(float x, float y, float z, float r);
    void getPlayerPos(float x, float z);
    private:

        float speed;
        float xStart;
        float zStart;
    float direction;
    float distance;
    float initialAngle();
    void drawEnemyBot();
    void updateEnemyBot();
    bool isCollisionMountain();
    bool isCollisionCrater();
};
#endif
