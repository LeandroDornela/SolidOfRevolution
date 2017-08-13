#include "GameManager.h"

GameManager::GameManager()
{
    //ctor
}

GameManager::~GameManager()
{
    //dtor
}

void GameManager::Start(int width, int height)
{
    this->Setwidth(width);
    this->Setheight(height);
    this->ball = new Ball(width/2, height/2, 0, 8);
    this->ball->SetspeedX(0.0);
    this->ball->SetspeedY(0.0);
    float color[3] = {1.0, 0.5, 0.0};
    this->p1 = new Player(0, 70, this->Getwidth(), this->Getheight(), color);
    this->p1->SetspeedX(1);
    this->p1->SetspeedY(1);
    this->p2 = new Player(1, 70, this->Getwidth(), this->Getheight(), color);
    this->table = new Table();
    this->interface = new Interface();
    this->SetgameStatus(1);//1-menu, 2-single player, 3-multi player
}

void GameManager::Update()
{
    switch(this->GetgameStatus())
    {
        case 1:
        break;
        case 2:
            this->p2->ComputerMovement(this->ball);
            this->ball->Move();
            this->ball->PlayerCollision(this->p1);
            this->ball->PlayerCollision(this->p2);
            this->interface->InGameUpdate(this->p1->Getscore(), this->p2->Getscore());
            this->VerifyWin();
        break;
        case 3:
            this->p2->Movement(this->Getwidth(), this->Getheight());
            this->ball->Move();
            this->ball->PlayerCollision(this->p1);
            this->ball->PlayerCollision(this->p2);
            this->interface->InGameUpdate(this->p1->Getscore(), this->p2->Getscore());
            this->VerifyWin();
        break;
    }

}

void GameManager::VerifyWin()
{
    int Wcollision = this->ball->WallCollision(this->Getwidth(), this->Getheight());

    if(this->p1->Getside() == Wcollision)
    {
        this->p2->Setscore(this->p2->Getscore() + 1);
        Sleep(1000);
        this->Reset();
        if(this->p2->Getscore() >= 3)
        {
            this->p1->Setscore(0);
            this->p2->Setscore(0);
            this->SetgameStatus(1);
        }
    }

    if(this->p2->Getside() == Wcollision)
    {
        this->p1->Setscore(this->p1->Getscore() + 1);
        Sleep(1000);
        this->Reset();
        if(this->p1->Getscore() >= 3)
        {
            this->p1->Setscore(0);
            this->p2->Setscore(0);
            this->SetgameStatus(1);
        }
    }
}

void GameManager::MousePassiveControls(int x, int y)
{
    //y = this->Getheight() - y;
    if(this->GetgameStatus() != 1)
    {
        this->p1->MouseMovement(x, y, this->Getwidth(), this->Getheight());
    }
}

void GameManager::KeyboardControls(unsigned char key, bool state)
{
    this->p2->KeyboardMovement(key, state);
}

void GameManager::MouseClick(int x, int y)
{
    if(this->GetgameStatus() == 1)
        this->SetgameStatus(this->interface->MainMenuUpdate(x, y));
    else
    {
        if((this->ball->GetspeedX() == 0) && (this->ball->GetspeedY() == 0))
        {
            this->ball->SetspeedX(5.0);
            this->ball->SetspeedY(5.0);
        }
    }
}

void GameManager::Draw()
{
    switch(this->GetgameStatus())
    {
        case 1:
            this->interface->DrawMainMenu();
        break;
        case 2:
            this->table->Draw();
            this->ball->Draw();
            this->p1->Draw();
            this->p2->Draw();
            this->interface->DrawInGame();
        break;
        case 3:
            this->table->Draw();
            this->ball->Draw();
            this->p1->Draw();
            this->p2->Draw();
            this->interface->DrawInGame();
        break;
    }
}

void GameManager::Reset()
{
    this->ball->SetspeedX(0.0);
    this->ball->SetspeedY(0.0);
    this->ball->SetpositionX(width/2);
    this->ball->SetpositionY(height/2);
    this->p1->SetpositionY(height/2);
    this->p2->SetpositionY(height/2);
}
