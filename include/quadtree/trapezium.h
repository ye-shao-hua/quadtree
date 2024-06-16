#pragma once

#include "rect.h"

namespace quadtree {
class Trapezium {
public:
  Trapezium(const Point &bottom_min = {0.f, 0.f}, float bottom_width = 1.f,
            float top_relative_height = 1.f, float left_recip_k = 0.f,
            float right_recip_k = 0.f);
  [[nodiscard]] bool include(float x, float y) const;
  [[nodiscard]] Point bottom_min() const;
  [[nodiscard]] Point bottom_max() const;
  [[nodiscard]] Point top_min() const;
  [[nodiscard]] Point top_max() const;
  [[nodiscard]] bool include(const Rect &box_size) const;
  [[nodiscard]] bool contain(const Rect &box_size) const;

private:
  Point _bottom_min;
  float _bottom_width;
  float _top_relative_height;
  float _left_recip_k;
  float _right_recip_k;
};
} // namespace quadtree
