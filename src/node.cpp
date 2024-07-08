#include "../include/quadtree/node.h"
#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/node_iterators.h"
#include "../include/quadtree/node_pool.h"
#include "../include/quadtree/node_viewer.h"
#include <iostream>

namespace quadtree {
Node::Node(NodeViewer father, const Rect &box_size, float value)
    : _box_size(box_size), _value(value), _child(), _father(father),
      _refine_flag(false), _coarsen_flag(false) {}
float Node::value() const { return _value; }
float Node::value(float new_value) { return _value = new_value; }
const Rect &Node::box_size() const { return _box_size; }
NodeViewer Node::child(index_type index) { return _child[index].view(); }
const NodeViewer Node::child(index_type index) const {
  return _child[index].view();
}
bool Node::has_child() const { return child(0).viewable(); }
bool Node::include(float x, float y) const {
  if (x >= box_size().x_min() && x <= box_size().x_max() &&
      y >= box_size().y_min() && y <= box_size().y_max())
    return true;
  return false;
}

float Node::operator()(float x, float y) const { return at(x, y)->value(); }

NodeViewer Node::at(float x, float y) {
  return const_cast<const Node *>(this)->at(x, y);
}

const NodeViewer Node::at(float x, float y) const {
  if (!has_child())
    return this;
  for (NodeViewer child_node : child_iterators()) {
    if (child_node->include(x, y)) {
      return child_node->at(x, y);
    }
  }
  throw "can't find\n";
}

void Node::refine() {
  if (has_child()) {
    for (NodeViewer child_node : child_iterators()) {
      child_node->refine();
    }
    return;
  }
  for (int i = 0; i < 4; ++i) {
    _child[i] = _node_pool.allocate(this, box_size().subrect(i), value());
  }
}

void Node::coarsen() {
  if (!has_child())
    throw "coarsen: !has_child()\n";
  std::clog << "coarsen\n";
  value((child(0)->value() + child(1)->value() + child(2)->value() +
         child(3)->value()) /
        4.f);
  _child[0] = nullptr;
  _child[1] = nullptr;
  _child[2] = nullptr;
  _child[3] = nullptr;
}

void Node::set_value(float x, float y, float new_value) {
  if (!has_child())
    return (void)value(new_value);

  bool flushed = false;
  for (NodeViewer child_node : child_iterators()) {
    if (child_node->include(x, y)) {
      child_node->set_value(x, y, new_value);
      flushed = true;
    }
  }
  if (flushed)
    return;
  throw "不在范围\n";
}

Point Node::center() const { return box_size().center(); }

void Node::set_value(const Trapezium &trapezium, float new_value) {
  if (!has_child() && (include(trapezium) || trapezium.include(box_size())))
    return (void)value(new_value);

  for (NodeViewer child_node : child_iterators())
    if (child_node->include(trapezium) ||
        trapezium.include(child_node->box_size()))
      child_node->set_value(trapezium, new_value);
}

bool Node::include(const Trapezium &trapezium) const {
  return include(trapezium.bottom_min()) || include(trapezium.bottom_max()) ||
         include(trapezium.top_min()) || include(trapezium.top_max());
}

bool Node::contain(const Trapezium &trapezium) const {
  return include(trapezium.bottom_min()) && include(trapezium.bottom_max()) &&
         include(trapezium.top_min()) && include(trapezium.top_max());
}

bool Node::include(const Point &point) const {
  return include(point.x(), point.y());
}

NodeIterators Node::child_iterators() { return NodeIterators{_child, 4}; }

const NodeIterators Node::child_iterators() const {
  return NodeIterators{
      const_cast<NodeViewer *>(dynamic_cast<const NodeViewer *>(_child)), 4};
}

NodeViewer Node::up() {return const_cast<const Node *>(this)->up(); }

const NodeViewer Node::up() const {
  static bool valid = false;
  static float x = 0;
  if (!valid) {
    valid = true;
    x = box_size().x_center();
  }
  if (_father.viewable()) {
    if (box_size().y_max() == _father->box_size().y_max()) {
      return _father->up();
    }
    for (const NodeViewer brother_node : _father->child_iterators()) {
      if (brother_node == this) {
        continue;
      }
      if (brother_node->box_size().x_min() == box_size().x_min()) {
        valid = false;
        return brother_node->at(x, brother_node->box_size().y_min());
      }
    }
  }
  valid = false;
  return at(x, box_size().y_max());
}

Node::value_type Node::up_value() const {
  if (!_cache_up.viewable() || _cache_up->has_child())
    _cache_up = up();
  return _cache_up->value();
}

NodeViewer Node::down() { return const_cast<const Node *>(this)->down(); }

const NodeViewer Node::down() const {
  static bool valid = false;
  static float x = 0;
  if (!valid) {
    valid = true;
    x = box_size().x_center();
  }
  if (_father.viewable()) {
    if (box_size().y_min() == _father->box_size().y_min()) {
      return _father->down();
    }
    for (const NodeViewer brother_node : _father->child_iterators()) {
      if (brother_node == this) {
        continue;
      }
      if (brother_node->box_size().x_min() == box_size().x_min()) {
        valid = false;
        return brother_node->at(x, brother_node->box_size().y_max());
      }
    }
  }
  valid = false;
  return at(x, box_size().y_min());
}

Node::value_type Node::down_value() const {
  if (!_cache_down.viewable() || _cache_down->has_child())
    _cache_down = down();
  return _cache_down->value();
}

NodeViewer Node::left() { return const_cast<const Node *>(this)->left(); }

const NodeViewer Node::left() const {
  static bool valid = false;
  static float y = 0;
  if (!valid) {
    valid = true;
    y = box_size().y_center();
  }
  if (_father.viewable()) {
    if (box_size().x_min() == _father->box_size().x_min()) {
      return _father->left();
    }
    for (const NodeViewer brother_node : _father->child_iterators()) {
      if (brother_node == this) {
        continue;
      }
      if (brother_node->box_size().y_min() == box_size().y_min()) {
        valid = false;
        return brother_node->at(brother_node->box_size().x_max(), y);
      }
    }
  }
  valid = false;
  return at(box_size().x_min(), y);
}

Node::value_type Node::left_value() const {
  if (!_cache_left.viewable() || _cache_left->has_child())
    _cache_left = left();
  return _cache_left->value();
}

NodeViewer Node::right() { return const_cast<const Node *>(this)->right(); }

const NodeViewer Node::right() const {
  static bool valid = false;
  static float y = 0;
  if (!valid) {
    valid = true;
    y = box_size().y_center();
  }
  if (_father.viewable()) {
    if (box_size().x_max() == _father->box_size().x_max()) {
      return _father->right();
    }
    for (const NodeViewer brother_node : _father->child_iterators()) {
      if (brother_node == this) {
        continue;
      }
      if (brother_node->box_size().y_min() == box_size().y_min()) {
        valid = false;
        return brother_node->at(brother_node->box_size().x_min(), y);
      }
    }
  }
  valid = false;
  return at(box_size().x_max(), y);
}

Node::value_type Node::right_value() const {
  if (!_cache_right.viewable() || _cache_right->has_child())
    _cache_right = right();
  return _cache_right->value();
}

Node::value_type Node::linear_value(float x, float y) const {
  if (!include(x, y))
    throw "linear_value: !include\n";
  constexpr value_type epsilon = 1e-10;

  value_type x_distance = x - box_size().x_center();
  value_type y_distance = y - box_size().y_center();

  value_type x_rate;
  value_type y_rate;
  if (x >= box_size().x_center())
    x_rate = (right_value() - value()) /
             (right()->box_size().x_center() - box_size().x_center() + epsilon);
  else
    x_rate = (left_value() - value()) /
             (left()->box_size().x_center() - box_size().x_center() + epsilon);
  if (y >= box_size().y_center())
    y_rate = (up_value() - value()) /
             (up()->box_size().y_center() - box_size().y_center() + epsilon);
  else
    y_rate = (down_value() - value()) /
             (down()->box_size().y_center() - box_size().y_center() + epsilon);
  return value() + (x_distance)*x_rate + (y_distance)*y_rate;
}

Node::value_type Node::curvature() const {
  value_type y_curvature = up_value() + down_value() - 2 * value();
  value_type x_curvature = right_value() + left_value() - 2 * value();
  if (y_curvature < 0)
    y_curvature = -y_curvature;
  if (x_curvature < 0)
    x_curvature = -x_curvature;
  return box_size().area() *
         (x_curvature + y_curvature);
}

bool Node::refine_flag() const { return _refine_flag; }

void Node::refine_flag(bool flag) { _refine_flag = flag; }

bool Node::coarsen_flag() const { return _coarsen_flag; }

void Node::coarsen_flag(bool flag) { _coarsen_flag = flag; }

void Node::uncache() const {
  _cache_up = nullptr;
  _cache_down = nullptr;
  _cache_left = nullptr;
  _cache_right = nullptr;
}

} // namespace quadtree
