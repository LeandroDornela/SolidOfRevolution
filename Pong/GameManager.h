#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Ball.h"
#include "Player.h"
#include "Table.h"
#include <time.h>
#include <stdio.h>
#include "Interface.h"

class GameManager
{
    public:
        GameManager();
        virtual ~GameManager();
        void Start(int width, int height);
        int Getwidth() { return width; }
        void Setwidth(int val) { width = val; }
        int Getheight() { return height; }
        void Setheight(int val) { height = val; }
        int GetgameStatus() { return gameStatus; }
        void SetgameStatus(int val) { gameStatus = val; }
        void Update();
        void Draw();
        void VerifyWin();
        void MousePassiveControls(int x, int y);
        void KeyboardControls(unsigned char key, bool state);
        void MouseClick(int x, int y);
        void Reset();
    protected:
    private:
        int width;
        int height;
        Ball *ball;
        Player *p1, *p2;
        Interface *interface;
        Table *table;
        int gameStatus;
};

#endif // GAMEMANAGER_H
