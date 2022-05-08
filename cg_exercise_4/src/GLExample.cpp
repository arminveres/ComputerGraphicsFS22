#include "GLExample.h"
#include "Cube.h"
#include <iostream>

namespace cgCourse {
GLExample::GLExample(glm::uvec2 _windowSize, std::string _title)
    : GLApp(_windowSize, _title, false) {
  mvpMatrix = glm::mat4(1);
  animation = 0.0;
  animationDir = Forward;
  drawTorusNormals =
      false; // just in case somebody wants to activate the normals
}

bool GLExample::init() {
  // Framebuffer size and window size may be different in high-DPI displays
  // setup camera with standard view (static for our case)
  cam.create(getFramebufferSize(), glm::vec3(3, 3, -3), glm::vec3(0, 0, 0),
             glm::vec3(0, 1, 0));

  programForCube =
      std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Cube");
  programForTorus =
      std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Torus");
  programForTorusNormals =
      std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Normals");
  programForLightBox =
      std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Lightbox");

  // create box for light position
  lightbox = std::make_shared<Cube>();
  if (!lightbox->createVertexArray(0, 1, 2)) {
    return false;
  };
  lightbox->setPosition(glm::vec3(0.0, 0.5, -1.5));
  lightbox->setScaling(glm::vec3(0.1, 0.1, 0.1));
  lightboxColor = glm::vec3(1.0, 1.0, 1.0);

  // Init models
  cube = std::make_shared<Cube>();
  bool constructed = cube->createVertexArray(0, 1, 2);
  if (!constructed)
    return constructed;
  cube->setPosition(glm::vec3(-2.5, 0.0, -1.0));
  cube->setScaling(glm::vec3(1.0, 2.0, 1.0));

  torus = std::make_shared<Torus>();
  constructed = torus->createVertexArray(0, 1, 2);
  torus->setPosition(glm::vec3(1.5, 0.0, 0.0));

  // Init multiline field for normals of objects
  normalsTorus =
      std::make_shared<MultiLine>(torus->getPositions(), torus->getNormals());
  constructed = normalsTorus->createVertexArray(0, 1, 2);
  normalsTorus->setPosition(glm::vec3(1.0, 0.0, 0.0));

  /* TODO: set light info here */
  // light.ambientTerm = glm::vec3(0.1, 0.1, 0.1);
  light.ambientTerm = glm::vec3(0.20f, 0.70f, 0.01f);
  // light.diffuseTerm = glm::vec3(0.8, 0.8, 0.8);
  light.diffuseTerm = glm::vec3(0.20f, 0.70f, 0.01f);

  light.specularTerm = glm::vec3(0.8, 0.8, 0.8);
  // End
  return constructed;
}

bool GLExample::update() {
  torus->setRotation(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

  if (animationDir == Forward) {
    if (animation > 5.0) {
      animationDir = Backward;
    } else {
      animation += 0.01;
    }
  } else {
    if (animation < -1.5) {
      animationDir = Forward;
    } else {
      animation -= 0.01;
    }
  }
  lightbox->setPosition(glm::vec3(0.0, 0.5, animation));
  return true;
}

bool GLExample::render() {
  glEnable(GL_DEPTH_TEST);

  // Clear the color and depth buffers
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  renderLightBox();

  addLightVariables(programForCube);
  addLightVariables(programForTorus);

  renderCubes();
  renderTorus();
  return true;
}

/* TODO: update this function to set the light information for the cube and the
 * torus shaders. Don't forget that shader have to be bound before shader
 * uniform can be set..
 */
void GLExample::addLightVariables(
    const std::shared_ptr<ShaderProgram> &_program) {

  glUniform3f(_program->getUniformLocation("lightColor"), lightboxColor[0],
              lightboxColor[1], lightboxColor[2]);

  glUniform3f(_program->getUniformLocation("ambientTerm"), light.ambientTerm[0],
              light.ambientTerm[1], light.ambientTerm[2]);

  glUniform3f(_program->getUniformLocation("diffuseTerm"), light.diffuseTerm[0],
              light.diffuseTerm[1], light.diffuseTerm[2]);

  glUniform3f(_program->getUniformLocation("specularTerm"),
              light.specularTerm[0], light.specularTerm[1],
              light.specularTerm[2]);

  glUniform3f(_program->getUniformLocation("viewPos"), cam.getPosition()[0],
              cam.getPosition()[1], cam.getPosition()[2]);
}
// END TODO

/* TODO: update this function as well to set the light information for the cube
 * shaders */
void GLExample::renderCubes() {
  programForCube->bind();
  mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
  glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1,
                     GL_FALSE, &cube->getModelMatrix()[0][0]);
  glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  addLightVariables(programForCube);
  cube->draw();
  programForCube->unbind();

  cube->setPosition(glm::vec3(-2.5, 0.0, 1.5));

  programForCube->bind();
  mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
  glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1,
                     GL_FALSE, &cube->getModelMatrix()[0][0]);
  glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  addLightVariables(programForCube);
  cube->draw();
  programForCube->unbind();

  cube->setPosition(glm::vec3(-2.5, 0.0, 4.0));

  programForCube->bind();
  mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
  glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1,
                     GL_FALSE, &cube->getModelMatrix()[0][0]);
  glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  addLightVariables(programForCube);
  cube->draw();
  programForCube->unbind();

  cube->setPosition(glm::vec3(-2.5, 0.0, 6.5));

  programForCube->bind();
  mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
  glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1,
                     GL_FALSE, &cube->getModelMatrix()[0][0]);
  glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  addLightVariables(programForCube);
  cube->draw();
  programForCube->unbind();

  cube->setPosition(glm::vec3(-2.5, 0.0, -1.0));
}
// END TODO

void GLExample::renderTorus() {
  programForTorus->bind();
  mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
  glUniformMatrix4fv(programForTorus->getUniformLocation("modelMatrix"), 1,
                     GL_FALSE, &torus->getModelMatrix()[0][0]);
  glUniformMatrix4fv(programForTorus->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  addLightVariables(programForTorus);
  torus->draw();
  programForTorus->unbind();

  // draw torus normals
  if (drawTorusNormals) {
    programForTorusNormals->bind();
    mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
    glUniformMatrix4fv(programForTorusNormals->getUniformLocation("mvpMatrix"),
                       1, GL_FALSE, &mvpMatrix[0][0]);
    normalsTorus->draw();
    programForTorusNormals->unbind();
  }
}

void GLExample::renderLightBox() {
  programForLightBox->bind();
  mvpMatrix = cam.getViewProjectionMatrix() * lightbox->getModelMatrix();
  glUniform3fv(programForLightBox->getUniformLocation("objectColor"), 1,
               &lightboxColor[0]);
  glUniformMatrix4fv(programForLightBox->getUniformLocation("mvpMatrix"), 1,
                     GL_FALSE, &mvpMatrix[0][0]);
  lightbox->draw();
  programForLightBox->unbind();
}

bool GLExample::end() {
  programForCube->deleteShaderProgramFromGPU();
  programForTorus->deleteShaderProgramFromGPU();
  programForTorusNormals->deleteShaderProgramFromGPU();
  return true;
}
} // namespace cgCourse
