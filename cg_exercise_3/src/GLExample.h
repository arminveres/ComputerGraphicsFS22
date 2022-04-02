#ifndef GLEXAMPLE_H
#define GLEXAMPLE_H

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
class GLExample : public GLApp {
public:
  enum MotionMode {
    NoMotionMode = 0,
    RotateMode = 1,
    TranslateMode = 2,
    ZoomMode = 3
  };

  GLExample(glm::uvec2 _windowSize, std::string _title);

  bool init() override;
  bool update() override;
  bool render() override;
  bool end() override;

private:
  void renderCube();
  void renderTorus();

  glm::mat4 computeViewProjectionMatrix() const;

  glm::mat4 mvpMatrix;
  glm::mat4 viewProjectionMatrix;

  std::shared_ptr<ShaderProgram> programForCube;
  std::shared_ptr<ShaderProgram> programForTorus;
  std::shared_ptr<ShaderProgram> programForTorusNormals;
  std::shared_ptr<Cube> cube;
  std::shared_ptr<Torus> torus;
  std::shared_ptr<MultiLine> normalsTorus;
};
} // namespace cgCourse

#endif // GLEXAMPLE_H
