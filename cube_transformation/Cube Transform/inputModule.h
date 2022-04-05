//
//  inputModule.h
//  CubeViewer
//
//  Created by Renato Pajarola.
//
//

#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <vmmlib/matrix.hpp>

using namespace vmml;

#define OFFSET -5.0
#define ANGLE_X  25
#define ANGLE_Y -25

// this must be packed/padded accordingly for a uniform shader block
typedef struct {
  GLuint wire;
} RenderSettings;


#ifdef __cplusplus
extern "C" {
#endif
  
  void readKeyboard(GLFWwindow* window, unsigned int keyUTF32);
  //void readSpecialKeys(int key, int x, int y); // key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  void mouseButtHandler(GLFWwindow* window, int button,
						int action, int mods);
  void mouseMoveHandler(GLFWwindow * window, double xpos, double ypos);
  void transformObject(mat4f &viewMatrix);
  void animate();

#ifdef __cplusplus
}
#endif

#endif /* defined(INPUTMODULE_H) */









