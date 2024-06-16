#include "../include/quadtree/node.h"
#include "../include/quadtree/node_iterator.h"
#include "../include/quadtree/node_iterators.h"
#include "../include/quadtree/node_pool.h"
#include "../include/quadtree/node_viewer.h"
#include <iostream>

namespace quadtree {
Node::Node(NodeViewer father, const Rect &box_size, float value)
    : _box_size(box_size), _value(value), _child(), _uniform(true),
      _father(father) {}
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

float Node::operator()(float x, float y) const { return at(x, y).value(); }

Node &Node::at(float x, float y) {
  return const_cast<Node &>(const_cast<const Node *>(this)->at(x, y));
}

const Node &Node::at(float x, float y) const {
  if (uniform())
    return *this;
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

void Node::set_value(float x, float y, float new_value) {
  if (has_child()) {
    bool flushed = false;
    for (NodeViewer child_node : child_iterators()) {
      if (child_node->include(x, y)) {
        if (uniform()) {
          if (new_value == value())
            return;
          uniform(false);
          return child_node->set_value(x, y, new_value);
        } else {
          child_node->set_value(x, y, new_value);
          for (const NodeViewer child_node : child_iterators()) {
            if (!child_node->uniform())
              return;
          }
          if (child(0)->value() == child(1)->value() &&
              child(0)->value() == child(2)->value() &&
              child(0)->value() == child(3)->value()) {
            uniform(true);
            value(child(0)->value());
          }
        }
        flushed = true;
        // return;
      }
    }
    if (flushed)
      return;
    throw "不在范围\n";
  }
  value(new_value);
}

Point Node::center() const { return box_size().center(); }

void Node::set_value(const Trapezium &trapezium, float new_value) {
  if (!has_child() && (include(trapezium) || trapezium.include(box_size()))) {
    value(new_value);
    return;
  }
  if (trapezium.contain(box_size())) {
    uniform(true);
    value(new_value);
    return;
  }
  if (uniform() && new_value != value())
    uniform(false);
  for (NodeViewer child_node : child_iterators()) {
    if (child_node->include(trapezium) ||
        trapezium.include(child_node->box_size()))
      child_node->set_value(trapezium, new_value);
  }
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

bool Node::uniform() const { return _uniform; }

bool Node::uniform(bool uniform) { return _uniform = uniform; }

NodeIterators Node::child_iterators() { return NodeIterators{_child, 4}; }

const NodeIterators Node::child_iterators() const {
  return NodeIterators{
      const_cast<NodeViewer *>(dynamic_cast<const NodeViewer *>(_child)), 4};
}

Node &Node::up() { return const_cast<Node &>(const_cast<Node *>(this)->up()); }

const Node &Node::up() const {
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
      if (&*brother_node == this) {
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
  if (!_cache_up.viewable() || !_cache_up->uniform())
    _cache_up = (Node*)&up();
  return _cache_up->value();
}

Node& Node::down() {
    return const_cast<Node&>(const_cast<Node*>(this)->down());
}

const Node& Node::down() const {
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
      if (&*brother_node == this) {
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
  if (!_cache_down.viewable() || !_cache_down->uniform())
    _cache_down = (Node*)&down();
  return _cache_down->value();
}

Node& Node::left() {
    return const_cast<Node&>(const_cast<Node*>(this)->left());
}

const Node& Node::left() const {
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
      if (&*brother_node == this) {
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
  if (!_cache_left.viewable() || !_cache_left->uniform())
    _cache_left = (Node*)&left();
  return _cache_left->value();
}

Node& Node::right() {
    return const_cast<Node&>(const_cast<Node*>(this)->right());
}

const Node& Node::right() const {
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
      if (&*brother_node == this) {
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
  if (!_cache_right.viewable() || !_cache_right->uniform())
    _cache_right = (Node*)&right();
  return _cache_right->value();
}

} // namespace quadtree
