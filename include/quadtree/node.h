#pragma once
#include "node_accessor.h"
#include "node_viewer.h"
#include "rect.h"
#include "trapezium.h"

namespace quadtree {

class NodePool;
class NodeAccessor;
class NodeViewer;
class NodeIterators;

class Node {
  friend class NodeBlock;
  friend class NodeAccessor;

public:
  using value_type = float;
  using index_type = unsigned int;

public:
  Node(NodeViewer father = nullptr, const Rect &box_size = {0.f, 1.f, 0.f, 1.f},
       value_type value = 0.f);
  [[nodiscard]] value_type value() const;
  value_type value(float new_value);
  [[nodiscard]] const Rect &box_size() const;
  [[nodiscard]] NodeViewer child(index_type index);
  [[nodiscard]] const NodeViewer child(index_type index) const;
  [[nodiscard]] bool has_child() const;
  [[nodiscard]] bool include(float x, float y) const;
  [[nodiscard]] bool include(const Point &point) const;
  [[nodiscard]] bool include(const Trapezium &trapezium) const;
  [[nodiscard]] bool contain(const Trapezium &trapezium) const;
  [[nodiscard]] value_type operator()(float x, float y) const;
  void refine();
  void coarsen();
  void set_value(float x, float y, value_type new_value);
  [[nodiscard]] Point center() const;
  void set_value(const Trapezium &trapezium, value_type new_value);
  [[nodiscard]] NodeIterators child_iterators();
  [[nodiscard]] const NodeIterators child_iterators() const;
  [[nodiscard]] NodeViewer up();
  [[nodiscard]] const NodeViewer up() const;
  [[nodiscard]] NodeViewer down();
  [[nodiscard]] const NodeViewer down() const;
  [[nodiscard]] NodeViewer left();
  [[nodiscard]] const NodeViewer left() const;
  [[nodiscard]] NodeViewer right();
  [[nodiscard]] const NodeViewer right() const;
  [[nodiscard]] value_type up_value() const;
  [[nodiscard]] value_type down_value() const;
  [[nodiscard]] value_type left_value() const;
  [[nodiscard]] value_type right_value() const;
  [[nodiscard]] NodeViewer at(float x, float y);
  [[nodiscard]] const NodeViewer at(float x, float y) const;
  [[nodiscard]] value_type linear_value(float x, float y) const;
  [[nodiscard]] value_type curvature() const;
  [[nodiscard]] bool refine_flag() const;
  void refine_flag(bool flag);
  [[nodiscard]] bool coarsen_flag() const;
  void coarsen_flag(bool flag);
  void uncache() const;

private:
  value_type _value;
  Rect _box_size;
  NodeAccessor _child[4];
  bool _refine_flag;
  bool _coarsen_flag;
  mutable NodeViewer _cache_up;
  mutable NodeViewer _cache_down;
  mutable NodeViewer _cache_right;
  mutable NodeViewer _cache_left;
  NodeViewer _father;
};

} // namespace quadtree
