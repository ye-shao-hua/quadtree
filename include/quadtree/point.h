#pragma once

namespace quadtree {
class Point {
public:
  Point(float x = 0.f, float y = 0.f);
  float x() const;
  float y() const;

private:
  float _x;
  float _y;
};
} // namespace quadtree
