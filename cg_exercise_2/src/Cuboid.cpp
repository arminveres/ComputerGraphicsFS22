#include <iostream>

#include "Cuboid.h"
// this define and include will enable M_PI from math.h.
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse {

void Cuboid::draw() {
  glBindVertexArray(vaoID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

float Cuboid::func0(float x) {
  return (x * x) + x;
}

Cuboid::Cuboid()
    : Shape() {
  float x_1, y_1;
  float x_2, y_2;
  // float x_3, y_3;

  // variables that decide the shape and segmentation of the function
  int number_of_elements = 40;
  float radius = 0.5f;
  const float interval_size = 4.0f;  // [-2,2] => 4

  glm::vec3 normal_z = glm::vec3(0.f, 0.f, 1.f) * radius;

  for (int i = 0; i < number_of_elements - 2; ++i) {
    // defining the coordinates and adjust x coordinates for interval
    x_1 = interval_size / number_of_elements * i - interval_size / 2.f;
    x_2 = interval_size / number_of_elements * (i + 1) - interval_size / 2.f;
    // x_3 = interval_size / number_of_elements * (i + 2) - interval_size / 2.f;
    y_1 = func0(x_1);
    y_2 = func0(x_2);
    // y_3 = func0(x_3);

    // textual debugging
    std::cout << "i: " << i << "\n";
    std::cout << "x1: " << x_1 << " | ";
    std::cout << "y1: " << y_1 << "\n";
    std::cout << "x2: " << x_2 << " | ";
    std::cout << "y2: " << y_2 << "\n";
    // std::cout << "x3: " << x_3 << "\n";
    // std::cout << "y3: " << y_3 << "\n";

    // vector definitions, in 2D
    glm::vec3 point_a = glm::vec3(x_1, y_1, 0);
    glm::vec3 point_b = glm::vec3(x_2, y_2, 0);

    /* get perpendicular vectors with new length 1
     * (a, b, c) => (b, -a, c)
     */
    glm::vec3 perpendicular_a_xy;
    // glm::normalize(glm::vec3(y_2 - y_1, -(x_2 - x_1), 0)) * radius;

    glm::vec3 perpendicular_b_xy;
    // glm::normalize(glm::vec3(y_3 - y_2, -(x_3 - x_2), 0)) * radius;

    perpendicular_a_xy = glm::vec3(1.f, 0.f, 0.f) * radius;
    perpendicular_b_xy = glm::vec3(1.f, 0.f, 0.f) * radius;

    // if (x_1 < 0 && x_2 < 0) {
    //   perpendicular_a_xy = glm::vec3(-1.f, 0.f, 0.f) * radius;
    //   perpendicular_b_xy = glm::vec3(-1.f, 0.f, 0.f) * radius;
    // } else if (x_1 > 0 && x_2 > 0) {
    //   perpendicular_a_xy = glm::vec3(1.f, 0.f, 0.f) * radius;
    //   perpendicular_b_xy = glm::vec3(1.f, 0.f, 0.f) * radius;
    // } else if (x_1 < 0 && x_2 == 0) {
    //   perpendicular_a_xy = glm::vec3(1.f, 0.f, 0.f) * radius;
    //   perpendicular_b_xy = glm::vec3(1.f, 0.f, 0.f) * radius;
    // } else if (x_1 == 0 && x_2 > 0) {
    //   perpendicular_a_xy = glm::vec3(1.f, 0.f, 0.f) * radius;
    //   perpendicular_b_xy = glm::vec3(1.f, 0.f, 0.f) * radius;
    // }

    // top cover
    if (i == 0) {
      glm::vec3 bottom_vertices[] = {
          glm::vec3(point_a) + perpendicular_a_xy,  // index 0
          glm::vec3(point_a) + normal_z,
          glm::vec3(point_a) - perpendicular_a_xy,
          glm::vec3(point_a) - normal_z,
      };

      glm::vec3 bottom_colors[] = {{0.0f, 0.8f, 0.8f},
                                   {0.0f, 0.8f, 0.8f},
                                   {0.0f, 0.8f, 0.8f},
                                   {0.0f, 0.8f, 0.8f}};

      glm::vec3 bottom_faces[] = {{0, 1, 2}, {0, 2, 3}};

      for (int j = 0; j < 4; j++) {
        this->positions.push_back(bottom_vertices[j]);
        this->colors.push_back(bottom_colors[j]);
      };

      for (int j = 0; j < 2; j++) {
        this->faces.push_back(bottom_faces[j]);
      };
    };

    // need to define my own vertices in each run
    glm::vec3 vertices[] = {
        // index 0
        glm::vec3(point_a) + perpendicular_a_xy,  // top right
        glm::vec3(point_a) + normal_z,  // bottom right
        glm::vec3(point_b) + perpendicular_b_xy,  // bottom left
        glm::vec3(point_b) + normal_z,  // top left

        // index 4
        glm::vec3(point_a) - perpendicular_a_xy,
        glm::vec3(point_a) + normal_z,
        glm::vec3(point_b) - perpendicular_b_xy,
        glm::vec3(point_b) + normal_z,

        // index 8
        glm::vec3(point_a) - perpendicular_a_xy,
        glm::vec3(point_a) - normal_z,
        glm::vec3(point_b) - perpendicular_b_xy,
        glm::vec3(point_b) - normal_z,

        // index 12
        glm::vec3(point_a) + perpendicular_a_xy,
        glm::vec3(point_a) - normal_z,
        glm::vec3(point_b) + perpendicular_b_xy,
        glm::vec3(point_b) - normal_z,
    };

    // manually defined colors userd by cube
    glm::vec3 colors[] = {
        {0.0f, 0.0f, 0.8f},
        {0.0f, 0.0f, 0.8f},
        {0.0f, 0.0f, 0.8f},
        {0.0f, 0.0f, 0.8f},

        {0.8f, 0.8f, 0.0f},
        {0.8f, 0.8f, 0.0f},
        {0.8f, 0.8f, 0.0f},
        {0.8f, 0.8f, 0.0f},

        {0.8f, 0.0f, 0.0f},
        {0.8f, 0.0f, 0.0f},
        {0.8f, 0.0f, 0.0f},
        {0.8f, 0.0f, 0.0f},

        {0.0f, 0.8f, 0.0f},
        {0.0f, 0.8f, 0.0f},
        {0.0f, 0.8f, 0.0f},
        {0.0f, 0.8f, 0.0f},
    };

    float index_offset = i * 16.f + interval_size;

    // 4 faces for the side cubes
    glm::uvec3 faces[] = {
        {0 + index_offset, 2 + index_offset, 1 + index_offset},
        {1 + index_offset, 2 + index_offset, 3 + index_offset},

        {4 + index_offset, 6 + index_offset, 5 + index_offset},
        {5 + index_offset, 6 + index_offset, 7 + index_offset},

        {8 + index_offset, 10 + index_offset, 9 + index_offset},
        {9 + index_offset, 10 + index_offset, 11 + index_offset},

        {12 + index_offset, 14 + index_offset, 13 + index_offset},
        {13 + index_offset, 14 + index_offset, 15 + index_offset}};

    for (int j = 0; j < 16; j++) {
      this->positions.push_back(vertices[j]);
      this->colors.push_back(colors[j]);
    }
    for (int j = 0; j < 8; j++) {
      this->faces.push_back(faces[j]);
    }

    if (i == number_of_elements - 3) {
      glm::vec3 bottom_vertices[] = {
          glm::vec3(point_b) + perpendicular_b_xy,  // index 0
          glm::vec3(point_b) + normal_z,
          glm::vec3(point_b) - perpendicular_b_xy,
          glm::vec3(point_b) - normal_z,
      };

      glm::vec3 bottom_colors[] = {{0.8f, 0.f, 0.8f},
                                   {0.8f, 0.f, 0.8f},
                                   {0.8f, 0.f, 0.8f},
                                   {0.8f, 0.f, 0.8f}};

      glm::vec3 bottom_faces[] = {
          {index_offset + 16 + 2, index_offset + 16 + 1, index_offset + 16 + 0},
          {index_offset + 16 + 0,
           index_offset + 16 + 3,
           index_offset + 16 + 2}};

      for (int j = 0; j < 4; ++j) {
        this->positions.push_back(bottom_vertices[j]);
        this->colors.push_back(bottom_colors[j]);
      }

      for (int j = 0; j < 2; ++j) {
        this->faces.push_back(bottom_faces[j]);
      }
    }
  }
}

}  // namespace cgCourse
