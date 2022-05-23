#include "GLExample.h"
#include "Cube.h"
#include <chrono>
#include <iostream>
#include <thread>

namespace cgCourse {
GLExample::GLExample(glm::uvec2 _windowSize, std::string _title)
    : GLApp(_windowSize, _title, false) {
  mvpMatrix = glm::mat4();
}

bool GLExample::init() {
  // Framebuffer size and window size may be different in high-DPI displays
  glm::uvec2 fbSize = getFramebufferSize();
  glViewport(0, 0, int(fbSize.x), int(fbSize.y));

  programForCube =
      std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Cube");
  programForTorus =
      std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Torus");
  programForTorusNormals =
      std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Normals");

  // Init models
  cube = std::make_shared<Cube>();
  bool constructed = cube->createVertexArray(0, 1, 2);
  if (!constructed)
    return constructed;

  cube->setPosition(glm::vec3(-2.0, 0.0, 1.0));
  cube->setScaling(glm::vec3(1.0, 1.0, 3.0));

  torus = std::make_shared<Torus>();
  constructed = torus->createVertexArray(0, 1, 2);
  torus->setPosition(glm::vec3(1.0, 0.0, 0.0));

  // Init multiline field for normals of objects
  normalsTorus =
      std::make_shared<MultiLine>(torus->getPositions(), torus->getNormals());
  constructed = normalsTorus->createVertexArray(0, 1, 2);
  normalsTorus->setPosition(glm::vec3(1.0, 0.0, 0.0));

  return constructed;
}

bool GLExample::update() {
  // let the thread sleep for consistent rendering
  // using namespace std::chrono_literals;
  // std::this_thread::sleep_for(100ms);

  /*
   *  TODO: update the cube and the torus with rotations, translations and
   * scalings
   */

  // cube->setPosition({3.f, 2.f, 1.f});
  // cube->setRotation(45.f, {0.0, 0.0, 1.0});
  // cube->setRotation(30.f, {0.0, 0.0, 1.0});
  cube->setRotation(.1f, {0.0, 0.0, 1.0});
  // cube->setScaling({0.5, 0.5, 0.5});
  // cube->setScaling({2.0, 2.0, 2.0});
  // torus->setRotation(.2f, {0.f, 1.f, 0.0});
  // torus->setScaling({0.5, 0.5, 0.5});

  // TODO End
  return true;
}

bool GLExample::render() {
  glEnable(GL_DEPTH_TEST);

  // Clear the color and depth buffers
  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  // compute view and projection matrix for the camera (static for our case)
  viewProjectionMatrix = computeViewProjectionMatrix();

  // call update function to have real time change to the shapes
  update();

  renderCube();
  renderTorus();
  return true;
}

void GLExample::renderCube() {
  programForCube->bind();
  mvpMatrix = viewProjectionMatrix * cube->getModelMatrix();
  glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  cube->draw();
  programForCube->unbind();
}

void GLExample::renderTorus() {
  programForTorus->bind();
  mvpMatrix = viewProjectionMatrix * torus->getModelMatrix();

  /* TODO: add the normal matrix. */

  glm::mat4 normalMatrix = glm::transpose(glm::inverse(mvpMatrix));
  glUniformMatrix4fv(programForTorus->getUniformLocation("normMatrix"), 1,
                     GL_FALSE, &normalMatrix[0][0]);

  // TODO End

  glUniformMatrix4fv(programForTorus->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  torus->draw();
  programForTorus->unbind();

  /*
   *  TODO: render the line object with the normals of the torus. Use the
   *  shaderprogram in "programForTorusNormals" for this.
   */

  programForTorusNormals->bind();
  mvpMatrix = viewProjectionMatrix * normalsTorus->getModelMatrix();

  glUniformMatrix4fv(programForTorusNormals->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  normalsTorus->draw();
  programForTorusNormals->unbind();

  // TODO End
}

bool GLExample::end() {
  programForCube->deleteShaderProgramFromGPU();
  programForTorus->deleteShaderProgramFromGPU();
  programForTorusNormals->deleteShaderProgramFromGPU();
  return true;
}

glm::mat4 GLExample::computeViewProjectionMatrix() const {
  // Camera matrix
  glm::mat4 view = glm::lookAt(
      glm::vec3(3, 3, -3), // Camera is at (0,0,-3), in World Space
      glm::vec3(0, 0, 0),  // and looks at the origin
      glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
  );

  // Projection matrix
  float fieldOfView = 45.0f;
  float nearPlane = 0.1;
  float farPlane = 50.0;
  glm::uvec2 fbSize = getFramebufferSize();
  float aspect = float(fbSize.x) / float(fbSize.y);

  glm::mat4 projection =
      glm::perspective(fieldOfView, aspect, nearPlane, farPlane);

  return projection * view;
}
} // namespace cgCourse
