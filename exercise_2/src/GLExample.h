#ifndef GLEXAMPLE_H
#define GLEXAMPLE_H

#include "Cube.h"
#include "Cuboid.h"
#include "GLApp.h"

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

  virtual bool init() override;
  virtual bool render() override;
  virtual bool end() override;

private:
  bool loadAndCompileShaderToGPU(GLuint _program, const std::string &_source);
  glm::mat4 computeViewProjectionMatrix() const;
  bool checkLinkStatusOfProgram(GLuint _program);

  GLuint program = 0;
  GLuint mvpUniformLocation = 0;
  glm::mat4 mvpMatrix;
  std::shared_ptr<Cube> cube = nullptr;
  std::shared_ptr<Cuboid> cuboid = nullptr;
};
} // namespace cgCourse

#endif // GLEXAMPLE_H