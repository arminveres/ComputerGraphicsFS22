#include "Cuboid.h"
#include <iostream>

// this define and include will enable M_PI from math.h.
#define _USE_MATH_DEFINES
#include <math.h>

namespace cgCourse {
Cuboid::Cuboid() : Shape() {
  /* TODO: add you code here
   */

  positions = {
      {-1.0f, -1.0f, -1.0f}, // index 0
      {-1.0f, -1.0f, 1.0f},  //
      {-1.0f, 1.0f, 1.0f},   //
      {-1.0f, 1.0f, -1.0f},  //

      {1.0f, 1.0f, 1.0f},   // index 4
      {1.0f, -1.0f, 1.0f},  //
      {1.0f, -1.0f, -1.0f}, //
      {1.0f, 1.0f, -1.0f},  //

      {-1.0f, -1.0f, -1.0f}, // index 8
      {1.0f, -1.0f, -1.0f},  //
      {1.0f, -1.0f, 1.0f},   //
      {-1.0f, -1.0f, 1.0f},  //

      {1.0f, 1.0f, 1.0f},   // index 12
      {1.0f, 1.0f, -1.0f},  //
      {-1.0f, 1.0f, -1.0f}, //
      {-1.0f, 1.0f, 1.0f},  //

      {-1.0f, -1.0f, -1.0f}, // index 16
      {-1.0f, 1.0f, -1.0f},  //
      {1.0f, 1.0f, -1.0f},   //
      {1.0f, -1.0f, -1.0f},  //

      {1.0f, 1.0f, 1.0f},   // index 20
      {-1.0f, 1.0f, 1.0f},  //
      {-1.0f, -1.0f, 1.0f}, //
      {1.0f, -1.0f, 1.0f}   //
  };

  colors = {
      {0.8f, 0.8f, 0.0f}, //
      {0.8f, 0.8f, 0.0f}, //
      {0.8f, 0.8f, 0.0f}, //
      {0.8f, 0.8f, 0.0f}, //

      {0.8f, 0.0f, 0.0f}, //
      {0.8f, 0.0f, 0.0f}, //
      {0.8f, 0.0f, 0.0f}, //
      {0.8f, 0.0f, 0.0f}, //

      {0.0f, 0.8f, 0.0f}, //
      {0.0f, 0.8f, 0.0f}, //
      {0.0f, 0.8f, 0.0f}, //
      {0.0f, 0.8f, 0.0f}, //

      {0.0f, 0.0f, 0.8f}, //
      {0.0f, 0.0f, 0.8f}, //
      {0.0f, 0.0f, 0.8f}, //
      {0.0f, 0.0f, 0.8f}, //

      {0.0f, 0.8f, 0.8f}, //
      {0.0f, 0.8f, 0.8f}, //
      {0.0f, 0.8f, 0.8f}, //
      {0.0f, 0.8f, 0.8f}, //

      {0.8f, 0.0f, 0.8f}, //
      {0.8f, 0.0f, 0.8f}, //
      {0.8f, 0.0f, 0.8f}, //
      {0.8f, 0.0f, 0.8f}  //
  };

  faces = {
      {0, 1, 2},    {2, 3, 0},    //
      {4, 5, 6},    {6, 7, 4},    //
      {8, 9, 10},   {10, 11, 8},  //
      {12, 13, 14}, {14, 15, 12}, //
      {16, 17, 18}, {18, 19, 16}, //
      {20, 21, 22}, {22, 23, 20}  //
  };

  // for the moment we don't add normals here that is why we will not set the
  // normals or face normals.
}

void Cuboid::draw() {
  /* TODO:
  */
  glBindVertexArray(vaoID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
} // namespace cgCourse
