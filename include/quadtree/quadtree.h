#pragma once
#include "node.h"
namespace quadtree {
class QuadtreeIterators;
class QuadtreeActiveIterators;
class DynamicNodeList;
class Quadtree {
public:
  friend class QuadtreeIterators;
  friend class QuadtreeActiveIterators;
  friend class Evaluator;
  using value_type = float;

public:
  Quadtree(const Rect &box_size = {});
  ~Quadtree();
  [[nodiscard]] float operator()(float x, float y) const;
  void refine_global(int times = 1);
  void execute_refine_and_coarsen();
  void set_value(float x, float y, float new_value);
  void set_value(const Trapezium &trapezium, float new_value);
  NodeViewer at(float x, float y);
  const NodeViewer at(float x, float y) const;
  QuadtreeIterators node_iterators();
  QuadtreeActiveIterators active_node_iterators();
  [[nodiscard]] value_type linear_value(float x, float y) const;

private:
  Node _data;
  DynamicNodeList *_cache_node_list;
  DynamicNodeList *_cache_active_node_list;
};
} // namespace quadtree
