#include <iostream>
#include <GL/glui.h>
#include <GL/glut.h>
#include "BezierCurve.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "Ambient.h"

float rotationX = 0.0;
float rotationY = 0.0;
int last_x;
int last_y;
float m_yaw;
float m_pitch;
float dist = 120.0f;
bool yawLock = false;
bool pitchLock = false;
// Initial Position
float EyeInitial[3] = {dist, dist, dist};
float upInitial[3]  = {0.0f, 1.0f, 0.0f};
float foc[3]        = {0.0f, 30.0f, 0.0f};
// Rotated Position
float eye[3];
float up[3];

void fixAngle(float *angle)
{
    if(*angle > 360) *angle = 1.0f;
    if(*angle < 0)   *angle = 359.0f;
}

void RotatePoint(float *in, float *out, float pitch, float yaw)
{
	float xt = in[0], yt = in[1], zt = in[2];
	float x, y, z;

	// Rotation in 'y' axis
    x = zt * sin(yaw) + xt * cos(yaw);
	y = yt;
	z = zt * cos(yaw) - xt * sin(yaw);

	// Rotation in 'x' axis
    out[0] = x;
    out[1] = y * cos(pitch) - z * sin(pitch);
    out[2] = y * sin(pitch) + z * cos(pitch);
}

void RotateCamera()
{
    float r_pitch = M_PI * m_pitch / 180;
    float r_yaw   = M_PI * m_yaw / 180;

	// Rotate eye vector
	RotatePoint(EyeInitial, eye, r_pitch, r_yaw);

	// Rotate up vector
	RotatePoint(upInitial, up, r_pitch, r_yaw);
}

void cameraMotion(int x, int y)
{
    if(x >= width/2)
    {
        if(!yawLock) 	rotationX += (float) (x - last_x);
        if(!pitchLock)	rotationY += (float) (y - last_y);

        last_x = x;
        last_y = y;

        fixAngle(&rotationX);
        fixAngle(&rotationY);

        m_yaw   = rotationX;
        m_pitch = rotationY;
    }
}
