#include "../include/quadtree/node_hasher.h"

namespace quadtree {

NodeHasher::NodeHasher(std::size_t min_value, std::size_t max_value)
    : _min_value(min_value), _value_length(max_value - min_value) {}
std::size_t NodeHasher::operator()(const Node *node_point) {
  return reinterpret_cast<std::size_t>(node_point) % _value_length + _min_value;
}
} // namespace quadtree
