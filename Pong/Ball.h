#ifndef BALL_H
#define BALL_H

#define CIRCLE_PRECISION 360
#include <GL/glut.h>
#include <math.h>
#include "GameObject.h"
#include "Player.h"

//Evitando referência cruzada
class Player;

class Ball : public GameObject
{
    public:
        Ball(float x, float y, float z, float r);
        virtual ~Ball();
        float Getradius() { return radius; }
        void Setradius(float val) { radius = val; }
        float GetspeedX() { return speedX; }
        void SetspeedX(float val) { speedX = val; }
        float GetspeedY() { return speedY; }
        void SetspeedY(float val) { speedY = val; }
        float GetspeedZ() { return speedZ; }
        void SetspeedZ(float val) { speedZ = val; }
        void Draw();
        void Move();
        int WallCollision(int width, int height);
        bool PlayerCollision(Player* obj);
        float dotProduct(float x1, float y1, float x2, float y2);
    protected:
    private:
        float radius;
        float speedX;
        float speedY;
        float speedZ;
};

#endif // BALL_H
