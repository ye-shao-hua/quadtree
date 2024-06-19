#include "../include/quadtree/rect.h"
namespace quadtree {
Rect::Rect(float x_min, float x_max, float y_min, float y_max)
    : _x_min(x_min), _x_max(x_max), _y_min(y_min), _y_max(y_max) {}
Rect::Rect(const Point &min, const Point &max)
    : Rect(min.x(), max.x(), min.y(), max.y()) {}
float Rect::x_min() const { return _x_min; }
float Rect::x_max() const { return _x_max; }
float Rect::y_min() const { return _y_min; }
float Rect::y_max() const { return _y_max; }
float Rect::x_center() const { return (x_min() + x_max()) / 2.f; }
float Rect::y_center() const { return (y_min() + y_max()) / 2.f; }
Rect Rect::subrect(int select) const {
  switch (select) {
  case 0: {
    return {x_min(), x_center(), y_min(), y_center()};
  }
  case 1: {
    return {x_center(), x_max(), y_min(), y_center()};
  }
  case 2: {
    return {x_center(), x_max(), y_center(), y_max()};
  }
  case 3: {
    return {x_min(), x_center(), y_center(), y_max()};
  }
  default: {
    throw "error";
  }
  }
}
Point Rect::center() const {
  return {(x_min() + x_max()) / 2.f, (y_min() + y_max()) / 2.f};
}
float Rect::area() const { return (x_max() - x_min()) * (y_max() - y_min()); }

} // namespace quadtree
