/*
  Authors:     Hemerson Tacon; Leandro Dornela
  Date:        09/06/2016
  Description: Interactive Curves to make a Revolution Surface in OpenGL
*/
/** Fontes:
https://pt.wikipedia.org/wiki/Curva_de_B%C3%A9zier
http://www.somatematica.com.br/emedio/binomio/binomio.php
https://pomax.github.io/bezierinfo/
**/

#ifdef WIN32
#include <windows.h>
#endif
#include <iostream>
#include <GL/glui.h>
#include <GL/glut.h>
#include "BezierCurve.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "Camera.h"
#include "solidoRevolucao.h"


char title[128] = "Trabalho de implementação 2";
int geraSolido = 1;
std::string light = "GL_LIGHT0";
GLenum a = GL_LIGHT0;

void init(void)
{
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(a);
    glEnable(GL_LIGHTING);                 // Habilita luz
    glEnable(GL_DEPTH_TEST);               // Habilita Z-buffer
    //glEnable(GL_CULL_FACE);              // Habilita Backface-Culling
    glEnable(GL_NORMALIZE);

    // Cor da fonte de luz (RGBA)
    GLfloat cor_luz[]     = { 1.0, 1.0, 1.0, 1.0};
    // Posicao da fonte de luz. Ultimo parametro define se a luz sera direcional (0.0) ou tera uma posicional (1.0)
    GLfloat posicao_luz[] = { 100.0, 250.0, 100.0, 1.0};

    // Define parametros da luz
    glLightfv(a, GL_AMBIENT, cor_luz);
    glLightfv(a, GL_DIFFUSE, cor_luz);
    glLightfv(a, GL_SPECULAR, cor_luz);
    glLightfv(a, GL_POSITION, posicao_luz);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Projecao ortogonal
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width/6, 0, height/3, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, width/2, height);

    bezierView();
    DesenhaEixos();
    DesenhaGrade(true);

    //Linha entre as projecoes
    glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(width/2, 0);
        glVertex2f(width/2, height);
    glEnd();
    glEnable(GL_LIGHTING);

	//Projecao com perspectiva
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, (GLfloat)(width/2)/(GLfloat)height, 1.0, 1100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(width/2, 0, width/2, height);
    RotateCamera();
    gluLookAt(eye[0], eye[1], eye[2], foc[0], foc[1], foc[2], up[0],  up[1],   up[2]);

    //Esfera representando a luz
    glColor3f(1.0, 1.0, 1.0);
    glDisable(GL_LIGHTING);
    glPushMatrix();
        glTranslatef(100.0, 250.0, 100.0);
        glutSolidSphere(5, 8, 8);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    if(geraSolido == 1)
    {
        solidoRevolucao(bezier, prec);
    }
    DesenhaEixos();
    DesenhaGrade(false);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    width = w;
    height = h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

void idle()
{
    glutPostRedisplay();
}

void motion(int x, int y)
{
    cameraMotion(x, y);
    y = height - y;
    bezierMotion(x/3, y/3);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    y = height - y;
    //std::cout<<"Mouse click ["<<x<<", "<<y<<"]"<<std::endl;
    bezierMouse(button, state, x/3, y/3);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
   switch(tolower(key)){
       case '+':
            dist++;
            if(dist>200) dist=200;
            EyeInitial[0]=EyeInitial[1]=EyeInitial[2]=dist;
            sprintf(title, "Camera Rotation - Camera Distance: %.2f", dist);
            changeWindowTitle(title);
        break;
        case '-':
            dist--;
            if(dist<20) dist=20;
            EyeInitial[0]=EyeInitial[1]=EyeInitial[2]=dist;
            sprintf(title, "Camera Rotation - Camera Distance: %.2f", dist);
			changeWindowTitle(title);
        break;
        case 'y':
			if(yawLock){
                yawLock = false;
                changeWindowTitle("Camera Rotation - Unlocking Yaw");
			}else{
				yawLock = true;
				changeWindowTitle("Camera Rotation - Locking Yaw");
			}
        break;
        case 'p' :
			if(pitchLock){
                pitchLock = false;
				changeWindowTitle("Camera Rotation - Unlocking Pitch");
			} else{
				pitchLock = true;
				changeWindowTitle("Camera Rotation - Locking Pitch");
			}
        break;
        case 'a':
            prec++;
            bezier->Setprecision(prec);
            if(prec > 90) prec = 90;
            sprintf(title, "Precision Modified - Angle: %.2d", (360/(4*prec)));
            changeWindowTitle(title);
            break;
        case 'd':
            prec--;
            bezier->Setprecision(prec);
            if(prec < 1) prec = 1;
            sprintf(title, "Precision Modified - Angle: %.2d", (360/(4*prec)));
            changeWindowTitle(title);
            break;
        case 'z':
          label = !label;
          break;
        case 'c':
           curve = !curve;
           break;
        case 'x':
           polygon = !polygon;
           break;
        case 'v':
           vertex = !vertex;
           break;
        case 'n':
            bezier->add_curve();
            break;
        case 'r':
            bezier->clear_obj();
            break;
        case 'g':
            geraSolido = -geraSolido;
        break;
        case 'w':
            wireframe = -wireframe;
        break;
        case 27:
        case 'q':
          exit(0);
          break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   showMenu();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(width, height);
   glutInitWindowPosition(145, 85);
   window = glutCreateWindow(title);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutIdleFunc(idle);
   glutMotionFunc(motion);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   //glutFullScreen();
   glutMainLoop();
   return 0;
}
