/* GLUT tutorial - FPS camera
 * 2013, g0mb4 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <cmath>

#include "cam.h"

int width = 600, height = 600;
bool mouseIn = false;
unsigned char key = 0;
int mx, my;

void drawSnowMan(void)
{
    	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	glColor3f(1.0f, 0.5f , 0.5f);
	glRotatef(0.0f,1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void changeSize(int w, int h)
{
	if(h == 0)
		h = 1;

	float ratio = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    	glLoadIdentity();

    	camControl(0.05, 0.02, key, mx, my);
    	updateCam();

	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

	for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
                		glTranslatef(i * 10.0, 0, j * 10.0);
                		drawSnowMan();
			glPopMatrix();
		}

	glutSwapBuffers();

	key = 0;
}

void processNormalKeys(unsigned char pressedKey, int x, int y)
{
	if (pressedKey == 27)
		exit(0);

	if(pressedKey == 'w' || pressedKey == 'a' || pressedKey == 's' || pressedKey == 'd')
		key = pressedKey;
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
	}
}

void mouseMove(int xx, int yy)
{
	mx = xx;
	my = yy;
}



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Cam");

    	glutDisplayFunc(renderScene);
    	glutReshapeFunc(changeSize);
    	glutIdleFunc(renderScene);

    	glutKeyboardFunc(processNormalKeys);

	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mouseMove);

    	glEnable(GL_DEPTH_TEST);

    	glutMainLoop();

    	return EXIT_SUCCESS;
}
