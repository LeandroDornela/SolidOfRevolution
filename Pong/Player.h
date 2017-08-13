#ifndef PLAYER_H
#define PLAYER_H

#include <math.h>
#define CIRCLE_PRECISION 90
#include <GL/glut.h>
#include "GameObject.h"
#include "Ball.h"

//Evitando referência cruzada
class Ball;

class Player : public GameObject
{
    public:
        Player(int side, float r, int width, int height, float color[]);
        virtual ~Player();
        float Getradius() { return radius; }
        void Setradius(float val) { radius = val; }
        float GetspeedX() { return speedX; }
        void SetspeedX(float val) { speedX = val; }
        float GetspeedY() { return speedY; }
        void SetspeedY(float val) { speedY = val; }
        float GetspeedZ() { return speedZ; }
        void SetspeedZ(float val) { speedZ = val; }
        int Getside() { return side; }
        void Setside(int val) { side = val%4; }
        int Getscore() { return score; }
        void Setscore(int val) { score = val; }
        float* Getcolor() { return color; }
        void Setcolor(float val[]) { color[0] = val[0]; color[1] = val[1]; color[2] = val[2];}
        void Draw();
        void MouseMovement(int x, int y, int width, int height);
        void KeyboardMovement(unsigned char key, bool state);
        void Movement(int width, int height);
        void ComputerMovement(Ball *ball);
    protected:
    private:
        float radius;
        float speedX;
        float speedY;
        float speedZ;
        int side;
        int score;
        float color[3];
};

#endif // PLAYER_H
