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
  void set_value(float x, float y, value_type new_value);
  [[nodiscard]] Point center() const;
  void set_value(const Trapezium &trapezium, value_type new_value);
  [[nodiscard]] bool uniform() const;
  bool uniform(bool uniform);
  [[nodiscard]] NodeIterators child_iterators();
  [[nodiscard]] const NodeIterators child_iterators() const;
  [[nodiscard]] Node &up();
  [[nodiscard]] const Node &up() const;
  [[nodiscard]] Node &down();
  [[nodiscard]] const Node &down() const;
  [[nodiscard]] Node &left();
  [[nodiscard]] const Node &left() const;
  [[nodiscard]] Node &right();
  [[nodiscard]] const Node &right() const;
  [[nodiscard]] value_type up_value() const;
  [[nodiscard]] value_type down_value() const;
  [[nodiscard]] value_type left_value() const;
  [[nodiscard]] value_type right_value() const;
  [[nodiscard]] Node &at(float x, float y);
  [[nodiscard]] const Node &at(float x, float y) const;

private:
  value_type _value;
  Rect _box_size;
  bool _uniform;
  NodeAccessor _child[4];
  mutable NodeViewer _cache_child;
  mutable NodeViewer _cache_up;
  mutable NodeViewer _cache_down;
  mutable NodeViewer _cache_right;
  mutable NodeViewer _cache_left;
  NodeViewer _father;
};

} // namespace quadtree
