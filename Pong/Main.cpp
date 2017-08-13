#include <GL/glut.h>
#include <iostream>
#include <stdio.h>

#include "GameManager.h"
#define WIDTH 960
#define HEIGHT 540

void display(void);
void init(void);
void idle();
void motion(int x, int y);
void passiveMotion(int x, int y);
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
GameManager *GM = new GameManager();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH|GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pong");
    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passiveMotion);
    glutMouseFunc(mouse);
    glutIgnoreKeyRepeat(0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();
    return 0;
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (float) WIDTH, (float) HEIGHT, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GM->Start(WIDTH, HEIGHT);
}

void idle()
{
    GM->Update();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    GM->Draw();
    glutSwapBuffers();
}

void motion(int x, int y)
{

}

void passiveMotion(int x, int y)
{
    /** Movimento passivo do mouse pra controlar o rebatedor **/
    GM->MousePassiveControls(x, y);
}

void mouse(int button, int state, int x, int y)
{
    //y = windowSizeY - y;
	if ( button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			GM->MouseClick(x, y);
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key){
        case 27:
        case 'q':
        case 'Q':
            exit(0);
            break;
    }
    /** Jogador2 inicia o movimento do rebatedor **/
    GM->KeyboardControls(key, true);
    //Função acima não será chamada caso seja single player
}

void keyboardUp(unsigned char key, int x, int y)
{
    /** Jogador para de mover o rebatedor **/
    GM->KeyboardControls(key, false);
    //Função acima não será chamada caso seja single player
}




