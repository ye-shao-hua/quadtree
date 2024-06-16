#include "../include/quadtree/point.h"

namespace quadtree {
Point::Point(float x, float y) : _x(x), _y(y) {}
float Point::x() const { return _x; }
float Point::y() const { return _y; }
} // namespace quadtree
