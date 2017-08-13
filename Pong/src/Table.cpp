#include "Table.h"

Table::Table()
{
    //ctor
}

Table::~Table()
{
    //dtor
}

Table::Draw()
{
    glLineWidth(1);
    glColor3f(0.02, 0.115, 0.2);
	glBegin(GL_POLYGON);
        glVertex2f(50, 50);
        glVertex2f(50, 490);
        glVertex2f(910, 490);
        glVertex2f(910, 50);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
        glVertex2f(50, 50);
        glVertex2f(50, 490);
        glVertex2f(910, 490);
        glVertex2f(910, 50);
	glEnd();
	glBegin(GL_LINES);
        glVertex2f(480, 50);
        glVertex2f(480, 490);
	glEnd();
	glutPostRedisplay();
}
