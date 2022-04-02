#ifndef _TORUS_H
#define _TORUS_H

#include "Shape.h"

namespace cgCourse {
class Torus : public Shape {
public:
  Torus();

  void addTwoFaces(unsigned int _idx1, unsigned int _idx2, unsigned int _idx3,
                   unsigned int _idx4);
};
} // namespace cgCourse

#endif
