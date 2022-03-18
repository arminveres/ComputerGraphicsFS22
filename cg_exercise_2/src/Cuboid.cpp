#include <iostream>

#include "Cuboid.h"

// this define and include will enable M_PI from math.h.
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse {
Cuboid::Cuboid()
    : Shape() {
  float x_1, y_1;
  float x_2, y_2;
  float x_3, y_3;

  int number_of_elements = 40;
  glm::vec3 normal_z_axis = glm::vec3(0, 0, 1);

  for (int i = 0; i <= number_of_elements; ++i) {
    x_1 = i * (1.f/number_of_elements);
    x_2 = (i + 1) * (1.f/number_of_elements);
    x_3 = (i + 2) * (1.f/number_of_elements);
    y_1 = func0(x_1);
    y_2 = func0(x_2);
    y_3 = func0(x_3);
    glm::vec3 point_a = glm::vec3(x_1, y_1, 0);
    glm::vec3 point_b = glm::vec3(x_2, y_2, 0);
    // return vectors with new length 1
    glm::vec3 normal_a_xy =
        glm::normalize(glm::vec3(x_2 - x_1, -(y_2 - y_1), 0));
    glm::vec3 normal_b_xy =
        glm::normalize(glm::vec3(x_3 - x_2, -(y_3 - y_2), 0));

    // need to define my own vertices
    glm::vec3 vertices[] = {
        // index 0
        glm::vec3(point_a) + normal_a_xy,
        glm::vec3(point_a) + normal_z_axis,
        glm::vec3(point_b) + normal_b_xy,
        glm::vec3(point_b) + normal_z_axis,

        // index 4
        glm::vec3(point_a) + normal_z_axis,
        glm::vec3(point_a) - normal_a_xy,
        glm::vec3(point_b) + normal_z_axis,
        glm::vec3(point_b) - normal_b_xy,

        // index 8
        glm::vec3(point_a) - normal_a_xy,
        glm::vec3(point_a) - normal_z_axis,
        glm::vec3(point_b) - normal_b_xy,
        glm::vec3(point_b) - normal_z_axis,

        // index 12
        glm::vec3(point_a) - normal_z_axis,
        glm::vec3(point_a) + normal_a_xy,
        glm::vec3(point_b) - normal_z_axis,
        glm::vec3(point_b) + normal_b_xy,
    };

    glm::vec3 colors[16] = {{0.8f, 0.8f, 0.0f},
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

                            {0.0f, 0.0f, 0.8f},
                            {0.0f, 0.0f, 0.8f},
                            {0.0f, 0.0f, 0.8f},
                            {0.0f, 0.0f, 0.8f}};

    float indexOffset = i * 16.f + 4.f;

    glm::uvec3 faces[8] = {
        {0 + indexOffset, 2 + indexOffset, 1 + indexOffset},
        {1 + indexOffset, 2 + indexOffset, 3 + indexOffset},
        {4 + indexOffset, 6 + indexOffset, 5 + indexOffset},
        {5 + indexOffset, 6 + indexOffset, 7 + indexOffset},
        {8 + indexOffset, 10 + indexOffset, 9 + indexOffset},
        {9 + indexOffset, 10 + indexOffset, 11 + indexOffset},
        {12 + indexOffset, 14 + indexOffset, 13 + indexOffset},
        {13 + indexOffset, 14 + indexOffset, 15 + indexOffset}};

    // glm::uvec3 faces[8] = {
    //     {0,  2 , 1 },
    //     {1,  2 , 3 },
    //     {4,  6 , 5 },
    //     {5,  6 , 7 },
    //     {8,  10, 9 },
    //     {9,  10, 11},
    //     {12, 14, 13},
    //     {13, 14, 15}};

    for (int j = 0; j < 16; j++) {
      this->positions.push_back(vertices[j]);
      this->colors.push_back(colors[j]);
    }
    for (int j = 0; j < 8; j++) {
      this->faces.push_back(faces[j]);
    };

    // at some point I need to move the info to positions
    // this->positions.push_back();
    // this->colors.push_back();
  }

  // has 24 elements
  // positions = {};

  // float radius = 0.5f;
  // float shapeSize = 5.f;
  //
  // glm::vec3 perpendicularZ = glm::vec3(0., 0., 1.) * radius;
  //
  // for (int i = 0; i < number_of_elements - 1; i++) {
  //   float x = shapeSize / number_of_elements * i - shapeSize / 2.f;
  //   float x_1 = shapeSize / number_of_elements * (i + 1) - shapeSize / 2.f;
  //   float x_2 = shapeSize / number_of_elements * (i + 2) - shapeSize / 2.f;
  //   // float x = i;
  //   // float x_1 = i + 1;
  //   // float x_2 = i + 2;
  //   float y = func0(x);
  //   float y_1 = func0(x_1);
  //   float y_2 = func0(x_2);
  //
  //   glm::vec3 linePointA = glm::vec3(x, y, 0);
  //   glm::vec3 linePointB = glm::vec3(x_1, y_1, 0);
  //   glm::vec3 perpendicularAXY =
  //       glm::normalize(glm::vec3(y_1 - y, -(x_1 - x), 0)) * radius;
  //   glm::vec3 perpendicularBXY =
  //       glm::normalize(glm::vec3(y_2 - y_1, -(x_2 - x_1), 0)) * radius;
  //
  //   glm::vec3 vertices[16] = {
  //       glm::vec3(linePointA) + perpendicularAXY,  // index 0
  //       glm::vec3(linePointA) + perpendicularZ,
  //       glm::vec3(linePointB) + perpendicularBXY,
  //       glm::vec3(linePointB) + perpendicularZ,
  //
  //       glm::vec3(linePointA) + perpendicularZ,
  //       glm::vec3(linePointA) - perpendicularAXY,
  //       glm::vec3(linePointB) + perpendicularZ,
  //       glm::vec3(linePointB) - perpendicularBXY,
  //
  //       glm::vec3(linePointA) - perpendicularAXY,
  //       glm::vec3(linePointA) - perpendicularZ,
  //       glm::vec3(linePointB) - perpendicularBXY,
  //       glm::vec3(linePointB) - perpendicularZ,
  //
  //       glm::vec3(linePointA) - perpendicularZ,
  //       glm::vec3(linePointA) + perpendicularAXY,
  //       glm::vec3(linePointB) - perpendicularZ,
  //       glm::vec3(linePointB) + perpendicularBXY,
  //   };
  //
  //   glm::vec3 colors[16] = {{0.8f, 0.8f, 0.0f},
  //                           {0.8f, 0.8f, 0.0f},
  //                           {0.8f, 0.8f, 0.0f},
  //                           {0.8f, 0.8f, 0.0f},
  //
  //                           {0.8f, 0.0f, 0.0f},
  //                           {0.8f, 0.0f, 0.0f},
  //                           {0.8f, 0.0f, 0.0f},
  //                           {0.8f, 0.0f, 0.0f},
  //
  //                           {0.0f, 0.8f, 0.0f},
  //                           {0.0f, 0.8f, 0.0f},
  //                           {0.0f, 0.8f, 0.0f},
  //                           {0.0f, 0.8f, 0.0f},
  //
  //                           {0.0f, 0.0f, 0.8f},
  //                           {0.0f, 0.0f, 0.8f},
  //                           {0.0f, 0.0f, 0.8f},
  //                           {0.0f, 0.0f, 0.8f}};
  //
  //   float indexOffset = i * 16.f + 4.f;
  //
  //   glm::uvec3 faces[8] = {
  //       {0 + indexOffset, 2 + indexOffset, 1 + indexOffset},
  //       {1 + indexOffset, 2 + indexOffset, 3 + indexOffset},
  //       {4 + indexOffset, 6 + indexOffset, 5 + indexOffset},
  //       {5 + indexOffset, 6 + indexOffset, 7 + indexOffset},
  //       {8 + indexOffset, 10 + indexOffset, 9 + indexOffset},
  //       {9 + indexOffset, 10 + indexOffset, 11 + indexOffset},
  //       {12 + indexOffset, 14 + indexOffset, 13 + indexOffset},
  //       {13 + indexOffset, 14 + indexOffset, 15 + indexOffset}};
  //
  //   for (int j = 0; j < 16; j++) {
  //     this->positions.push_back(vertices[j]);
  //     this->colors.push_back(colors[j]);
  //   };
  //
  //   for (int j = 0; j < 8; j++) {
  //     this->faces.push_back(faces[j]);
  //   };
  // };
}

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
}  // namespace cgCourse
