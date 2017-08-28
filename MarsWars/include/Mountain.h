#ifndef MOUNTAIN_H
#define MOUNTAIN_H
#include "RenderableObject.h"
#include "bullet.h"
#include "EnemyBullet.h"
class Mountain :public RenderableObject
{
    public:
        double size = 0;
        Location c_loc;
        Mountain(Location& location);
        Mountain(int, Location& location);
        void render();
        void update();
        bool isCollision(bullet a);
        bool isCollisionBullet(EnemyBullet a);

    private:
        void drawMountain();
};

#endif // MOUNTAIN_H
