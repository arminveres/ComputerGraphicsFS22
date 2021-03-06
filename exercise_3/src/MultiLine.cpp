#include "MultiLine.h"
#include <iostream>

// to get M_PI from math libary enable defines
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse {
MultiLine::MultiLine(const std::vector<glm::vec3> &_vertices,
                     const std::vector<glm::vec3> &_normals)
    : Shape() {
  /* TODO: Create the multiline object by creating line segments from the
   *       vertices and normals of the incoming object.
   */
  float length = 0.3f;

  for (int i = 0; i < _vertices.size(); i++) {
    positions.push_back(_vertices[i]);
    positions.push_back(_vertices[i] + length * _normals[i]);

    colors.push_back({0.8f, 0.8f, 0});
    colors.push_back({0.8f, 0.8f, 0});

    lineIndices.push_back({2 * i, 2 * i + 1});
  }
  // End TODO:
}

void MultiLine::draw() const {
  // bind the Vertex Array Object and draw the lines
  glBindVertexArray(vaoID);

  /* TODO: make the draw call for all line indices. */
  glDrawElements(GL_LINES, 2 * lineIndices.size(), GL_UNSIGNED_INT, 0);
  // End TODO:

  glBindVertexArray(0);
}

void MultiLine::initIndexBuffer() {
  // Initialize buffer objects with index data
  glGenBuffers(1, &indexBufferID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineIndices.size() * sizeof(glm::uvec2),
               lineIndices.data(), GL_STATIC_DRAW);
}

} // namespace cgCourse
