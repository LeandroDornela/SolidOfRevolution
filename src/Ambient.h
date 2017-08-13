#include <iostream>
#include <GL/glui.h>
#include <GL/glut.h>
#include "BezierCurve.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int window;
int width = 1200;
int height = 600;

void changeWindowTitle(char *name)
{
	glutSetWindow(window); // Set main window as current
	glutSetWindowTitle(name); // change title
}

void drawScene()
{
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glutSolidCube(10.0);
	glPopMatrix();
}

void DesenhaEixos()
{
    glLineWidth(2);
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    // Eixo X
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-width/2, 0.01, 0.0);
        glVertex3f( width/2, 0.01, 0.0);
    // Eixo Y
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, -width/2, 0.0);
        glVertex3f(0.0, width/2, 0.0);
    // Eixo Z
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.01, -width/2);
        glVertex3f(0.0, 0.01, width/2);
    glEnd();
    glEnable(GL_LIGHTING);
}

void DesenhaGrade(bool is2d)
{
    glLineWidth(1);
    glDisable(GL_LIGHTING);
    //int quant = 10;
    //int n = 8;
    //glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
        //Linhas verticais
        for(int i=0; i*10<=width/2; i++){
            if(i % 10 == 0){
                glColor3f(1.0, 1.0, 1.0);
            } else{
                glColor3f(0.9, 0.9, 0.9);
            }
            if(is2d){
                glVertex3f(i*10, -height, 0);
                glVertex3f(i*10, height, 0);
                glVertex3f(-i*10, -height, 0);
                glVertex3f(-i*10, height, 0);
            } else{
                glVertex3f(i*10, 0, -height);
                glVertex3f(i*10, 0, height);
                glVertex3f(-i*10, 0, -height);
                glVertex3f(-i*10, 0, height);
            }
        }
        //Linhas horizontais
        for(int i=0; i*10<=height; i++){
            if(i % 10 == 0){
                glColor3f(1.0, 1.0, 1.0);
            } else{
                glColor3f(0.9, 0.9, 0.9);
            }
            if(is2d){
                glVertex3f(-width/2, i*10, 0);
                glVertex3f(width/2, i*10, 0);
                glVertex3f(-width/2, -i*10, 0);
                glVertex3f(width/2, -i*10, 0);
            } else{
                glVertex3f(-width/2, 0, i*10);
                glVertex3f(width/2, 0, i*10);
                glVertex3f(-width/2, 0, -i*10);
                glVertex3f(width/2, 0, -i*10);
            }
        }
    glEnd();
    glEnable(GL_LIGHTING);
}

void showMenu()
{
    printf("Commands\n");
	printf("---------------\n\n");

	printf("Mouse: \n\n");
	printf("3D View Side: \n");
	printf("* Left click and move horizontally to yaw (rotate over the y axis)\n");
	printf("* Left click and move vertically to pitch (rotate over the x axis)\n\n");

	printf("2D Edit Side: \n");
	printf("* Left click to create a control point\n");
	printf("* Left click in a point and move to movement the point\n");
	printf("* Right click in a point to remove it (curve's connect points can't be removed)\n\n");

	printf("Keyboard: \n\n");
	printf("3D View Side: \n");
	printf("* Press '+' or '-' to increase/decrease camera distance\n");
	printf("* Press 'y' to lock/unlock yaw movement\n");
	printf("* Press 'p' to lock/unlock pitch movement\n");
	printf("* Press 'a' to increase precision of surface\n");
	printf("* Press 'd' to decrease precision of surface\n");
	printf("* Press 'g' to show/hide the solid\n");
	printf("* Press 'w' to show/hide the wireframe mode\n");

	printf("\n2D Edit Side: \n");
	printf("* Press 'n' to start a new Bezier Curve\n");
	printf("* Press 'z' to show/hide labels of points\n");
	printf("* Press 'x' to show/hide control polygons\n");
	printf("* Press 'c' to show/hide the curves \n");
	printf("* Press 'v' to show/hide control points\n");
	printf("\n* Press 'ESC' or 'q' to quit\n\n");
}
