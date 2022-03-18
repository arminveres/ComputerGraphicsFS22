#ifndef CUBOID_H
#define CUBOID_H

#include "Shape.h"

namespace cgCourse {
class Cuboid : public Shape {
 public:
  Cuboid();
  void draw();

 private:
  float func0(float x);
};
}  // namespace cgCourse

#endif  //  CUBOID_H
