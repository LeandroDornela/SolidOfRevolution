#ifndef INTERFACE_H
#define INTERFACE_H

//#include <GamObject.h>
#include "glcText.h"
#include <time.h>
#include <stdio.h>

//class GameObject;

class Interface //: public GamObject
{
    public:
        Interface();
        virtual ~Interface();
        int MainMenuUpdate(int x, int y);
        void InGameUpdate(int scoreP1, int scoreP2);
        void DrawMainMenu();
        void DrawInGame();
        int GetstartTime() { return startTime; }
        void SetstartTime(int val) { startTime = val; }
        void GameOverMenu();
        void DrawGameOverMenu();
    protected:

    private:
        glcText *score;
        glcText *timeElapsed;
        glcText *singlePlayer;
        glcText *multiPlayer;
        int startTime;
};

#endif // INTERFACE_H
