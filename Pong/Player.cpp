#include "Player.h"
#include <stdio.h>
/**
    Valores 0, 1, 2, 3 indicam repectivamente lados esquerdo, direito, cima, baixo
**/
Player::Player(int side, float r, int width, int height, float color[])
{
    this->Setside(side);
    this->Setradius(r);
    this->Setscore(0);
    this->SetspeedX(0);
    this->SetspeedY(0);
    this->Setcolor(color);

    switch(this->Getside()){
        case 0:
            this->SetpositionX(-this->Getradius() * cos(M_PI_4) + 50);
            this->SetpositionY(height/2);
            break;
        case 1:
            this->SetpositionX(width + this->Getradius() * cos(M_PI_4) - 50);
            this->SetpositionY(height/2);
            break;
        case 2:
            this->SetpositionX(width/2);
            this->SetpositionY(-this->Getradius() * sin(M_PI_4));
            break;
        case 3:
            this->SetpositionX(width/2);
            this->SetpositionY(height + this->Getradius() * sin(M_PI_4));
            break;
    }

}

void Player::Draw()
{
    glLineWidth(1);
    glColor3fv (this->Getcolor());
    float theta = M_PI_2 / float(CIRCLE_PRECISION-1);
	float tangetial_factor = tanf(theta);//calculate the tangential factor
	float radial_factor = cosf(theta);//calculate the radial factor
	float x, y;//we start in a different angle depending on side
    switch(this->Getside()){
        case 0:
            x = Getradius() * cos(M_PI_4);
            y = - Getradius() * sin(M_PI_4);
            break;
        case 1:
            x = - Getradius() * cos(M_PI_4);
            y = Getradius() * sin(M_PI_4);
            break;
        case 2:
            x = Getradius() * cos(M_PI_4);
            y = Getradius() * sin(M_PI_4);
            break;
        case 3:
            x = - Getradius() * cos(M_PI_4);
            y = - Getradius() * sin(M_PI_4);
            break;
    }

	glBegin(GL_POLYGON);
        for(int i = 0; i < CIRCLE_PRECISION; i++)
        {
            glVertex2f(x + this->GetpositionX(), y + this->GetpositionY());//output vertex
            //calculate the tangential vector
            //remember, the radial vector is (x, y)
            //to get the tangential vector we flip those coordinates and negate one of them
            float tx = -y;
            float ty = x;
            //add the tangential vector
            x += tx * tangetial_factor;
            y += ty * tangetial_factor;
            //correct using the radial factor
            x *= radial_factor;
            y *= radial_factor;
        }
	glEnd();
	glutPostRedisplay();
}

void Player::MouseMovement(int x, int y, int width, int height)
{
   switch(this->Getside())
   {
        case 0:
        case 1:
            this->SetpositionY(this->GetpositionY() - (this->GetpositionY() - y)/this->GetspeedY());
            if(this->GetpositionY() < this->Getradius() * sin(M_PI_4)){
                this->SetpositionY(this->Getradius() * sin(M_PI_4));
            }
            else if(this->GetpositionY() > height - this->Getradius() * sin(M_PI_4)){
                this->SetpositionY(height - this->Getradius() * sin(M_PI_4));
            }
            break;
        case 2:
        case 3:
            this->SetpositionX(this->GetpositionX() - (this->GetpositionX() - x)/this->GetspeedX());
            if(this->GetpositionX() < this->Getradius() * cos(M_PI_4)){
                this->SetpositionX(this->Getradius() * cos(M_PI_4));
            }
            else if(this->GetpositionX() > width - this->Getradius() * cos(M_PI_4)){
                this->SetpositionX(width - this->Getradius() * cos(M_PI_4));
            }
            break;
   }


}

void Player::ComputerMovement(Ball* ball)
{
    if((ball->GetpositionX() > 850) && (ball->GetspeedX() > 0))
    {
        if(ball->GetpositionY() < this->GetpositionY()-10)
        {
            if(this->GetpositionY() > 50)
                this->SetpositionY(this->GetpositionY() - 8);
        }
        else if(ball->GetpositionY() > this->GetpositionY()+10)
        {
            if(this->GetpositionY() < 490)
                this->SetpositionY(this->GetpositionY() + 8);
        }
        else
        {
            this->SetpositionY(this->GetpositionY());
        }
    }
}

void Player::KeyboardMovement(unsigned char key, bool state)
{

    switch(key)
    {
        case 'w':
        case 'W':
            if(this->Getside() == 0 || this->Getside() == 1)
            {
                if(state)
                {
                    this->SetspeedY(-2);
                }
                else
                {
                    this->SetspeedY(0);
                }
            }
            break;
        case 's':
        case 'S':
            if(this->Getside() == 0 || this->Getside() == 1)
            {
                if(state)
                {
                    this->SetspeedY(2);
                }
                else
                {
                    this->SetspeedY(0);
                }
            }
            break;
        case 'a':
        case 'A':
            if(this->Getside() == 2 || this->Getside() == 3)
            {
                if(state)
                {
                    this->SetspeedX(-2);
                }
                else
                {
                    this->SetspeedX(0);
                }
            }
            break;
        case 'd':
        case 'D':
            if(this->Getside() == 2 || this->Getside() == 3)
            {
                if(state)
                {
                    this->SetspeedX(2);
                }
                else
                {
                    this->SetspeedX(0);
                }
            }
            break;
    }
}

void Player::Movement(int width, int height)
{
    if(this->Getside() == 0 || this->Getside() == 1)
    {
        this->SetpositionY(this->GetpositionY() + this->GetspeedY());
        if(this->GetpositionY() < this->Getradius() * sin(M_PI_4))
        {
            this->SetpositionY(this->Getradius() * sin(M_PI_4));
        }
        else if(this->GetpositionY() > height - this->Getradius() * sin(M_PI_4))
        {
            this->SetpositionY(height - this->Getradius() * sin(M_PI_4));
        }
    }

    if(this->Getside() == 2 || this->Getside() == 3)
    {
        this->SetpositionX(this->GetpositionX() + this->GetspeedX());
        if(this->GetpositionX() < this->Getradius() * cos(M_PI_4))
        {
            this->SetpositionX(this->Getradius() * cos(M_PI_4));
        }
        else if(this->GetpositionX() > width - this->Getradius() * cos(M_PI_4))
        {
            this->SetpositionX(width - this->Getradius() * cos(M_PI_4));
        }
    }

}

Player::~Player()
{
    //dtor
}
