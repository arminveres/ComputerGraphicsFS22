#ifndef GLEXAMPLE_H
#define GLEXAMPLE_H

#include "Camera.h"
#include "Cube.h"
#include "GLApp.h"
#include "MultiLine.h"
#include "ShaderProgram.h"
#include "Torus.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <memory>

namespace cgCourse {
struct LightInfo {
  glm::vec3 ambientTerm;
  glm::vec3 diffuseTerm;
  glm::vec3 specularTerm;
};

class GLExample : public GLApp {
public:
  enum LightMotionMode { Forward = 0, Backward = 1 };

  GLExample(glm::uvec2 _windowSize, std::string _title);

  bool init() override;
  bool update() override;
  bool render() override;
  bool end() override;

private:
  void addLightVariables(const std::shared_ptr<ShaderProgram> &_program);
  void renderLightBox();
  void renderCubes();
  void renderTorus();

  std::shared_ptr<ShaderProgram> programForCube;
  std::shared_ptr<ShaderProgram> programForTorus;
  std::shared_ptr<ShaderProgram> programForTorusNormals;
  std::shared_ptr<ShaderProgram> programForLightBox;
  std::shared_ptr<Cube> cube;
  std::shared_ptr<Cube> lightbox;
  std::shared_ptr<Torus> torus;
  std::shared_ptr<MultiLine> normalsTorus;

  float animation;
  LightMotionMode animationDir;
  glm::vec3 lightboxColor;

  glm::mat4 mvpMatrix;

  Camera cam;
  LightInfo light;
  bool drawTorusNormals;
};
} // namespace cgCourse

#endif // GLEXAMPLE_H
