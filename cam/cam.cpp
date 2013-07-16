#include "cam.h"

float camX = 0.0, camY = 1.0, camZ = 0.0;
float camYaw = 0.0, camPitch = 0.0;

void lockCam(void)
{
	/* -90 <= pitch <= 90 */
	if(camPitch > 90.0)
		camPitch = 90.0;

	if(camPitch < -90.0)
		camPitch = -90.0;

	/* 0 <= yaw <= 360 */
	if(camY < 0.0)
		camY += 360.0;

	if(camYaw > 360.0)
		camYaw -= 360;
}

void moveCam(float dist, float dir)
{
	float rad = (camYaw + dir) * M_PI / 180.0;	/* fok -> rad*/

	camX -= sin(rad) * dist;
	camZ -= cos(rad) * dist;
}

void moveCamUp(float dist, float dir)
{
	float rad = (camPitch + dir) * M_PI / 180.0;	/* fok -> rad*/

	camY += sin(rad) * dist;
}

void camControl(float moveVel, float mouseVel,unsigned char key, int mX, int mY)
{
	int midX = 600 / 2;
	int midY = 600 / 2;

	glutSetCursor(GLUT_CURSOR_NONE); 	/* egér elrejtése */

	camYaw += mouseVel * (midX - mX);
	camPitch += mouseVel * (midY - mY);

	lockCam();

	glutWarpPointer(midX, midY);

	switch(key)
	{
		case 'w':
			if(camPitch != 90.0 && camPitch != -90.0)
				moveCam(moveVel, 0.0);

			moveCamUp(moveVel, 0.0);
			break;

		case 's':
			if(camPitch != 90.0 && camPitch != -90.0)
				moveCam(moveVel, 180.0);

			moveCamUp(moveVel, 180.0);
			break;

		case 'a':
			moveCam(moveVel, 90.0);
			break;

		case 'd':
			moveCam(moveVel, 270.0);
			break;
	}


	glRotatef(-camPitch, 1.0, 0.0, 0.0);
	glRotatef(-camYaw, 0.0, 1.0, 0.0);
}

void updateCam(void)
{
	glTranslatef(-camX, -camY, -camZ);
}
