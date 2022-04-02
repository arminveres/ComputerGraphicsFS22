#ifndef _MULTILINE_H
#define _MULTILINE_H

#include "Shape.h"

namespace cgCourse {
class MultiLine : public Shape {
public:
  MultiLine(const std::vector<glm::vec3> &_vertices,
            const std::vector<glm::vec3> &_normals);

  void draw() const override;
  void initIndexBuffer() override;

private:
  std::vector<glm::uvec2> lineIndices;
};
} // namespace cgCourse

#endif
