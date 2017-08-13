#include "Ball.h"
#include <stdio.h>


Ball::Ball(float x, float y, float z, float r)
{
    this->SetpositionX(x);
    this->SetpositionY(y);
    this->SetpositionZ(z);
    this->Setradius(r);
    this->SetspeedX(0);
    this->SetspeedY(0);
    this->SetspeedZ(0);
}

Ball::~Ball()
{
    //dtor
}
/**
    Método efeciente para desenho do círculo foi baseado no código desta página:
    http://slabode.exofire.net/circle_draw.shtml
    Acessado em 14/05/2016
**/

void Ball::Draw()
{
    glLineWidth(1);
    glColor3f (1.0, 0.5, 0.0);

    float theta = 2 * 3.1415926 / float(CIRCLE_PRECISION);
	float tangetial_factor = tanf(theta);//calculate the tangential factor

	float radial_factor = cosf(theta);//calculate the radial factor

	float x = this->Getradius();//we start at angle = 0

	float y = 0;

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

    /*
    glBegin(GL_LINE_LOOP);
        for (float i=0; i <= 360; i+=(360/CIRCLE_PRECISION))
        {
            float degInRad = i*M_PI/180;
            glVertex2f(GetpositionX() + cosf(degInRad)*radius, GetpositionY() + sinf(degInRad)*radius);
        }
    glEnd();
    */
    glutPostRedisplay();
}

void Ball::Move()
{
    this->SetpositionX(this->GetpositionX() + this->GetspeedX());
    this->SetpositionY(this->GetpositionY() + this->GetspeedY());
    this->SetpositionZ(this->GetpositionZ() + this->GetspeedZ());
}

int Ball::WallCollision(int width, int height)
{
    if((this->GetpositionX() - this->Getradius()) < 0 +50){
        /** Colidiu com a lateral esquerda **/
        this->SetspeedX(-this->GetspeedX());
        this->SetpositionX(this->Getradius()+50);
        return 0;
    }
    if((this->GetpositionX() + this->Getradius()) > width -50){
        /** Colidiu com a lateral direita **/
        this->SetspeedX(-this->GetspeedX());
        this->SetpositionX(width - this->Getradius()-50);
        return 1;
    }
    if((this->GetpositionY() + this->Getradius()) > height -50){
        /** Bateu na parte de cima **/
        this->SetspeedY(-this->GetspeedY());
        this->SetpositionY(height - this->Getradius()-50);
        return 2;
    }
    if((this->GetpositionY() - this->Getradius()) < 0 +50){
        /** Bateu na parte de baixo **/
        this->SetspeedY(-this->GetspeedY());
        this->SetpositionY(this->Getradius()+50);
        return 3;
    }
    return -1;
}

float Ball::dotProduct(float x1, float y1, float x2, float y2)
{
    return (x1*x2 + y1*y2)/sqrt(x2*x2 + y2*y2);
}
/** Circular bouncing
https://sinepost.wordpress.com/2012/08/30/bouncing-off-the-walls-more-productively/
**/
bool Ball::PlayerCollision(Player* obj)
{
    float Nx, Ny, mag, normalParProj, normalPerpProj;
    float distance =  sqrt( pow(this->GetpositionX() - obj->GetpositionX(), 2) + pow(this->GetpositionY() - obj->GetpositionY(), 2));
    /** Detectando a colisão **/
    if( distance <= this->Getradius() + obj->Getradius())
    {

        /** Calculando a normal relativa ao ponto de colisão **/
        Nx = this->GetpositionX() - (this->GetpositionX() * obj->Getradius() + obj->GetpositionX() * this->Getradius())/(this->Getradius() + obj->Getradius());
        Ny = this->GetpositionY() - (this->GetpositionY() * obj->Getradius() + obj->GetpositionY() * this->Getradius())/(this->Getradius() + obj->Getradius());

        /** Normalizando a normal **/
        mag = sqrt(Nx*Nx + Ny*Ny);
        Nx = Nx/mag;
        Ny = Ny/mag;

        /** Retirando a bola de dentro do player **/
        this->SetpositionX(this->GetpositionX() + Nx*(this->Getradius() + obj->Getradius() - distance));
        this->SetpositionY(this->GetpositionY() + Ny*(this->Getradius() + obj->Getradius() - distance));

        /** Projeções da velocidade em relação aos vetores paralelo e perpendicular a normal **/
        normalParProj = dotProduct(this->GetspeedX(), this->GetspeedY(), Nx, Ny);
        normalPerpProj = dotProduct(this->GetspeedX(), this->GetspeedY(), Ny, -Nx);
        /** Refletindo a componente paralela a normal **/
        normalParProj = -normalParProj;

        /** Novas velocidades **/
        this->SetspeedX(normalPerpProj*Ny + normalParProj*Nx);
        this->SetspeedY(normalPerpProj*(-Nx) + normalParProj*Ny);

        return true;
    }
    return false;
}
