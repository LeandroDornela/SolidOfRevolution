#include <iostream>
#include <GL/glui.h>
#include <GL/glut.h>
#include "BezierCurve.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "BezierFunctions.h"
#include "Vertex3d.h"

int wireframe = -1;

void setMaterial(void)
{
    // Material do objeto. Parametros em RGBA
    GLfloat objeto_ambient[]   = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat objeto_difusa[]    = { 0.0, 0.3, 0.8, 1.0 };
    GLfloat objeto_especular[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat objeto_brilho[]    = { 100.0f };

    // Define os parametros da superficie a ser iluminada
    glMaterialfv(GL_FRONT, GL_AMBIENT, objeto_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, objeto_difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, objeto_especular);
    glMaterialfv(GL_FRONT, GL_SHININESS, objeto_brilho);
}

float modulo(float x, float y, float z)
{
    float mod = sqrt((x*x)+(y*y)+(z*z));
    return mod;
}

Vertex3d CalculateSurfaceNormal (Vertex3d p1, Vertex3d p2, Vertex3d p3){
  Vertex3d n1, n2, n3;

  n1.SetX(p2.GetX() - p1.GetX());
  n1.SetY(p2.GetY() - p1.GetY());
  n1.SetZ(p2.GetZ() - p1.GetZ());

  n2.SetX(p3.GetX() - p1.GetX());
  n2.SetY(p3.GetY() - p1.GetY());
  n2.SetZ(p3.GetZ() - p1.GetZ());

  n3.SetX(n1.GetY()*n2.GetZ() - n1.GetZ()*n2.GetY());
  n3.SetY(n1.GetZ()*n2.GetX() - n1.GetX()*n2.GetZ());
  n3.SetZ(n1.GetX()*n2.GetY() - n1.GetY()*n2.GetX());

  return n3;
}


//Gera uma superficie a partir de duas curvas utilizando quadrados
void geraMalha(std::list <Vertex3d> bezier1, std::list <Vertex3d> bezier2)
{
    std::list<Vertex3d>::iterator iter1 = bezier1.begin();
    std::list<Vertex3d>::iterator iter2 = bezier2.begin();
    std::list<Vertex3d>::iterator listEnd = bezier1.end();
    Vertex3d temp1 = *iter1;
    Vertex3d temp2 = *iter2;
    Vertex3d temp3;
    Vertex3d temp4;
    Vertex3d normal;
    listEnd--;
    float mod;

    //Desenha wireframe
    if(wireframe == 1)
    {
        for( ; iter1 != listEnd; iter1++, iter2++)
        {
            glColor3f(0.0, 0.0, 0.0);
            glLineWidth(1);
            glDisable(GL_LIGHTING);
            glBegin(GL_LINE_LOOP);
                glVertex3f(temp1.GetX(), temp1.GetY(), temp1.GetZ());
                glVertex3f(temp2.GetX(), temp2.GetY(), temp2.GetZ());
                iter1++;
                iter2++;
                temp1 = *iter1;
                temp2 = *iter2;
                glVertex3f(temp2.GetX(), temp2.GetY(), temp2.GetZ());
                glVertex3f(temp1.GetX(), temp1.GetY(), temp1.GetZ());
                iter1--;
                iter2--;
            glEnd();
            glEnable(GL_LIGHTING);
        }

    }
    else
    {
        //Desenha uma superficie
        for( ; iter1 != listEnd; iter1++, iter2++)
        {
            setMaterial();
            GLfloat posicao_luz[] = { 100.0, 250.0, 100.0, 1.0};
            glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz);
            glBegin(GL_QUADS);

                iter1++;
                iter2++;
                temp4 = *iter1;
                temp3 = *iter2;

                normal = CalculateSurfaceNormal(temp1, temp2, temp3);

                //mod = modulo(temp1.GetX(), temp1.GetY(), temp1.GetZ());
                glNormal3f(normal.GetX(), normal.GetY(), normal.GetZ());
                glVertex3f(temp1.GetX(), temp1.GetY(), temp1.GetZ());

                //mod = modulo(temp2.GetX(), temp2.GetY(), temp2.GetZ());
                glNormal3f(normal.GetX(), normal.GetY(), normal.GetZ());
                glVertex3f(temp2.GetX(), temp2.GetY(), temp2.GetZ());

                //mod = modulo(temp2.GetX(), temp2.GetY(), temp2.GetZ());
                glNormal3f(normal.GetX(), normal.GetY(), normal.GetZ());
                glVertex3f(temp3.GetX(), temp3.GetY(), temp3.GetZ());

                //mod = modulo(temp1.GetX(), temp1.GetY(), temp1.GetZ());
                glNormal3f(normal.GetX(), normal.GetY(), normal.GetZ());
                glVertex3f(temp4.GetX(), temp4.GetY(), temp4.GetZ());

                iter1--;
                iter2--;

                temp1 = temp4;
                temp2 = temp3;
            glEnd();
        }
    }
}

//Rotaciona uma curva e retorna a curva rotacionada
std::list <Vertex3d> rotaciona(std::list <Vertex3d> bezier, float ang)
{
    std::list<Vertex3d> bezier2;
    std::list<Vertex3d>::iterator iter = bezier.begin();
    ang = -ang;
    for( ; iter != bezier.end(); iter++)
    {
        Vertex3d temp = *iter;
        float x_old = temp.GetX();
        float z_old = temp.GetZ();
        temp.SetX(x_old*cos(ang) - z_old*sin(ang));
        temp.SetZ(x_old*sin(ang) + z_old*cos(ang));
        bezier2.insert(bezier2.end(), temp);
    }
    return bezier2;
}

//Dado uma curva inicial, faz rotacoes com o angulo obtido a partir do numero
//de segmentos e gera a malha para cada curva rotacionada
void solidoRevolucao(BezierObj *bezierObj, float seg)
{
    std::list<Vertex3d> bezier1 = bezierObj->GetcurvesPoints();

    float ang = 2*M_PI/(4*seg);
    for(int i=0; i<4*seg; i++)
    {
        std::list<Vertex3d> bezier2 = rotaciona(bezier1, ang);
        geraMalha(bezier1, bezier2);
        bezier1 = bezier2;
    }
}
