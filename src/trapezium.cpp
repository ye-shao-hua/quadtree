#include "../include/quadtree/trapezium.h"

namespace quadtree {
Trapezium::Trapezium(const Point &bottom_min, float bottom_width,
                     float top_height, float left_recip_k, float right_recip_k)
    : _bottom_min(bottom_min), _bottom_width(bottom_width),
      _top_relative_height(top_height), _left_recip_k(left_recip_k),
      _right_recip_k(right_recip_k) {}
bool Trapezium::include(float x, float y) const {
  if (y < _bottom_min.y())
    return false;
  if (y > _bottom_min.y() + _top_relative_height)
    return false;
  if (x < _bottom_min.x() + (y - _bottom_min.y()) * _left_recip_k)
    return false;
  if (x >
      _bottom_min.x() + _bottom_width + (y - _bottom_min.y()) * _right_recip_k)
    return false;
  return true;
}
Point Trapezium::bottom_min() const { return _bottom_min; }
Point Trapezium::bottom_max() const {
  return {_bottom_min.x() + _bottom_width, _bottom_min.y()};
}
Point Trapezium::top_min() const {
  return {_bottom_min.x() + _left_recip_k * _top_relative_height,
          _bottom_min.y() + _top_relative_height};
}
Point Trapezium::top_max() const {
  return {_bottom_min.x() + _bottom_width +
              _right_recip_k * _top_relative_height,
          _bottom_min.y() + _top_relative_height};
}
bool Trapezium::include(const Rect &box_size) const {
  return include(box_size.x_min(), box_size.y_min()) ||
         include(box_size.x_min(), box_size.y_max()) ||
         include(box_size.x_max(), box_size.y_min()) ||
         include(box_size.x_max(), box_size.y_max()) ||
         ((box_size.x_min() > bottom_min().x() ||
           box_size.x_min() > top_min().x()) &&
          (box_size.x_max() < bottom_max().x() ||
           box_size.x_max() < top_max().x()) &&
          (box_size.y_min() < bottom_min().y() ||
           box_size.y_min() < top_min().y()) &&
          (box_size.y_max() > bottom_max().y() ||
           box_size.y_max() > top_max().y()));
}
bool Trapezium::contain(const Rect &box_size) const {
  return include(box_size.x_min(), box_size.y_min()) &&
         include(box_size.x_min(), box_size.y_max()) &&
         include(box_size.x_max(), box_size.y_min()) &&
         include(box_size.x_max(), box_size.y_max());
}
} // namespace quadtree
