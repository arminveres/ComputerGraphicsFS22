//
//  inputModule.cpp
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

#include "inputModule.h"

extern int animateFlag;

static int motionMode = 0;
static int startX, deltax = 0;
static int startY, deltay = 0;
static float angleX = 0;   /* in degrees */
static float angleY = 0;    /* in degrees */

static float current_pos[] = {0.0, 0.0, 0.0};

RenderSettings settings = {0};

void cleanup(int sig);
void reshape(GLFWwindow* window, int width, int height);


void readKeyboard(GLFWwindow* window, unsigned int keyUTF32)
{
  switch(keyUTF32){
	case 'h':
	case 'H':
	  printf("\tpress q/Q for quit\n");
	  printf("\tpress w to togle wire frame rendering\n");
	  printf("\tpress r/R to revert to initial viewpoint / and rendering\n");
	  break;
	case  0x1B:
	case  'q':
	case  'Q':
	  //kill(getpid(), SIGHUP); 
	  cleanup(0);
	  break;
	case 'w':
	  settings.wire = !settings.wire;
	  break;
	case 'R':
	  // reset rendering parameters
	  settings.wire = 0;
	case 'r':
	  // reset initial view parameters
	  animateFlag = 0;
	  angleY = angleX = 0;
	  current_pos[0] = current_pos[1] = current_pos[2] = 0.0;
	  break;
	default:
	  break;
  }
}


void mouseButtHandler(GLFWwindow* window, int button,
					  int action, int mods)
{
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  int x = (int) round(xpos);
  int y = (int) round(ypos);

  if (action == GLFW_PRESS) {
	switch (button) {
	  case GLFW_MOUSE_BUTTON_LEFT :
		if (motionMode == 0)
		  motionMode = 1;		// Rotate object
		else if (motionMode == 3)
		  motionMode = 2;		// Translate object
		  break;
	  case GLFW_MOUSE_BUTTON_MIDDLE :
		motionMode = 2;		// Translate object
		break;
	  case GLFW_MOUSE_BUTTON_RIGHT :
		if (motionMode == 0)
		  motionMode = 3;		// Zoom
		else if (motionMode == 1)
		  motionMode = 2;		// Translate object
		  break;
	}
	startX = x;
	startY = y;
	deltax = deltay = 0;  
	animateFlag = 0;
  } else {
	motionMode = 0;
	if (abs(deltax) + abs(deltay) > 2)
	  animateFlag = 1;
  }
}


void mouseMoveHandler(GLFWwindow * window, double xpos, double ypos)
{
  int x = (int) round(xpos);
  int y = (int) round(ypos);
  
  // No mouse button is pressed... return 
  switch(motionMode){
	case 0:
	  return;
	  break;
	  
	case 1: // Calculate the rotations
	  deltax = x - startX;
	  deltay = y - startY;
	  angleX = angleX + deltay;
	  angleY = angleY + deltax;
	  break;
	  
	case 2:
	  current_pos[0] = current_pos[0] - (x - startX)/100.0;
	  current_pos[1] = current_pos[1] - (y - startY)/100.0;
	  break;
	  
	case 3:
	  current_pos[2] = current_pos[2] - (y - startY)/10.0;
	  break;
  }
  startX = x;
  startY = y;
}


void transformObject(mat4f &viewMatrix)
{
  mat4f transform = mat4f::IDENTITY;

  transform.set_translation(-current_pos[0], current_pos[1], -current_pos[2]);
  transform.rotate_x(angleX/180.0*M_PI);
  transform.rotate_y(angleY/180.0*M_PI);
  
  viewMatrix *= transform;
}


void animate()
{
  angleX = angleX + 0.1*deltay;
  angleY = angleY + 0.1*deltax;
}
