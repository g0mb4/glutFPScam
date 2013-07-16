#ifndef CAM_H
#define CAM_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include <cstdio>

#ifndef M_PI
#define M_PI	3.1415926535
#endif

void lockCam(void);
void moveCam(float dist, float dir);
void moveCamUp(float dist, float dir);
void camControl(float moveVel, float mouseVel, unsigned char key, int mX, int mY);
void updateCam(void);

#endif
