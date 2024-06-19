#pragma once

#include "point.h"
namespace quadtree {
class Rect {
public:
  Rect(float x_min = 0.f, float x_max = 1.f, float y_min = 0.f,
       float y_max = 1.f);
  Rect(const Point &min, const Point &max);
  float x_min() const;
  float x_max() const;
  float y_min() const;
  float y_max() const;
  float x_center() const;
  float y_center() const;
  Rect subrect(int select) const;
  Point center() const;
  float area() const;

private:
  float _x_min;
  float _x_max;
  float _y_min;
  float _y_max;
};
} // namespace quadtree
