#include "Interface.h"

Interface::Interface()
{
    this->score = new glcText();
    this->score->setType(5);
    this->score->setPos(480 - 30, 15);
    this->score->setString("Score");
    this->timeElapsed = new glcText();
    this->timeElapsed->setType(5);
    this->timeElapsed->setPos(480 - 30, 30);
    this->timeElapsed->setString("00:00");
    this->singlePlayer = new glcText();
    this->singlePlayer->setType(5);
    this->singlePlayer->setPos(480 - 50, 250);
    this->singlePlayer->setString("Single Player");
    this->multiPlayer = new glcText();
    this->multiPlayer->setType(5);
    this->multiPlayer->setPos(480 - 50, 270);
    this->multiPlayer->setString("Multiplayer");
    this->SetstartTime(time(NULL));
}

Interface::~Interface()
{
    //dtor
}

int Interface::MainMenuUpdate(int x, int y)
{
    if((x <= 500) && (x >= 430) && (y <= 250) && (y >= 240))
    {
        this->SetstartTime(time(NULL));
        return 2;
    }
    else
    {
        if((x <= 500) && (x >= 430) && (y <= 270) && (y >= 260))
        {
            this->SetstartTime(time(NULL));
            return 3;
        }
        else
        {
            return 1;
        }
    }
}

void Interface::InGameUpdate(int scoreP1, int scoreP2)
{
    char temp[6];
    snprintf(temp, 6, "%i X %i", scoreP1, scoreP2);
    this->score->setString(temp);
    int sec = time(NULL) - this->GetstartTime();
    int minutes = sec /60;
    sec = sec % 60;
    temp[4] = 0; //Limpando o elemento que não será sobreposto
    snprintf(temp, 6, "%i:%i", minutes, sec);
    if(sec < 10){
        temp[3] = temp[2];
        temp[2] = '0';
    }
    this->timeElapsed->setString(temp);
}

void Interface::DrawMainMenu()
{
    this->singlePlayer->setColor(0.9, 0.9, 0.9);
    this->singlePlayer->render();
    this->multiPlayer->setColor(0.9, 0.9, 0.9);
    this->multiPlayer->render();
}

void Interface::DrawInGame()
{
    this->score->setColor(0.9, 0.9, 0.9);
    this->score->render();
    this->timeElapsed->setColor(0.9, 0.9, 0.9);
    this->timeElapsed->render();
}
