#include <stdlib.h>


#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <freeglut.h>
#include "Level.h"
#include "Level1.h"

bool left, right, up, down;
Level1* level1;
Level* l1;
Player player;



/*draw the image - it is already in the format openGL requires for glDrawPixels*/
void display_image(void)
{

	glPushMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(45.0, 1.5, 0.1, 50);
	gluLookAt(player.x - 10, player.y + 12, player.z, player.x, player.y, player.z, 0, 1, 0);

	player.draw();
	l1->draw(1,1,1,1);
	glColor3f(0, 0, 0);

	glFlush();

	glPopMatrix();
}//display_image()

/*glut keyboard function*/
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 0x1B:
	case'q':
	case 'Q':
		exit(0);
		break;
	case's':
	case'S':
		printf("SAVING IMAGE: backup.tif\n");
		break;
	case 't':
	case 'T':

		break;
	case'f':
	case'F':
		printf("%f, %f, %f \n", player.x, player.y, player.z);
		break;
	}
}//keyboard

void specialUp(int key, int x, int y)
{
	switch (key)
	{
	case 0x1B:
	case GLUT_KEY_LEFT:
		left = false;
		break;
	case GLUT_KEY_RIGHT:
		right = false;
		break;
	case GLUT_KEY_UP:
		up = false;
		break;
	case GLUT_KEY_DOWN:
		down = false;
		break;
	case 32:
		
		break;
	}
}//keyboard

void special(int key, int x, int y)
{
	switch (key)
	{
	case 0x1B:
	case GLUT_KEY_LEFT:
		left = true;
		//p.moveL();
		break;
	case GLUT_KEY_RIGHT:
		right = true;
		break;
	case GLUT_KEY_UP:
		up = true;
		break;
	case GLUT_KEY_DOWN:
		down = true;
		break;
	}
}//keyboard

void moveTimer(int i) {
	glutPostRedisplay();

	double factor = 360*(player.s + player.a)/4;

	l1->gravity();
	if (l1->canMove != false){
		if (left){
			l1->collision(0, 0, -1);
			player.xAngle -= factor;
			player.rotMatrix[0] = 1;
			player.rotMatrix[2] = 0;
		}
		else if (right){
			l1->collision(0, 0, 1);
			player.xAngle += factor;
			player.rotMatrix[0] = 1;
			player.rotMatrix[2] = 0;
		}
		else if (up){
			l1->collision(1, 0, 0);
			player.xAngle -= factor;
			player.rotMatrix[0] = 0;
			player.rotMatrix[2] = 1;
		}
		else if (down){
			l1->collision(-1, 0, 0);
			player.xAngle += factor;
			player.rotMatrix[0] = 0;
			player.rotMatrix[2] = 1;
		}
		else{
			player.decelerate();
		}
	}
	else{
		player.decelerate();
	}

	glutTimerFunc(24, moveTimer, 0);
}

void init(){
	l1 = level1 = new Level1();
	l1->setPlayer(player);
}


int main(int argc, char** argv)
{
	init();
	printf("Q:quit\nF:filter\nT:triangle\nS:save\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize(600, 400);
	glutCreateWindow("SIMPLE DISPLAY");
	glShadeModel(GL_SMOOTH);
	glutDisplayFunc(display_image);
	glClearColor(1, 1, 1, 0.0);

	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);
	glutTimerFunc(16.6667, moveTimer, 0);
	//glutPassiveMotionFunc(mouseMovement);
	//glutFullScreen();
	//glutSetCursor(GLUT_CURSOR_NONE);


	glutKeyboardFunc(keyboard);
	//glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, 1.5, 0.1, 50);
	gluLookAt(-10, 8, 0, 0, 0, 0, 0, 1, 0);

	glutMainLoop();

	return 0;
}