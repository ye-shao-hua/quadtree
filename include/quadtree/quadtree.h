#pragma once
#include "node.h"
namespace quadtree {
class QuadtreeIterators;
class QuadtreeActiveIterators;
class Quadtree {
public:
  friend class QuadtreeIterators;

public:
  Quadtree(const Rect &box_size = {});
  float operator()(float x, float y) const;
  void refine_global(int times = 1);
  void set_value(float x, float y, float new_value);
  void set_value(const Trapezium &trapezium, float new_value);
  Node &at(float x, float y);
  const Node &at(float x, float y) const;
  QuadtreeIterators node_iterators();

private:
  Node _data;
};
} // namespace quadtree
