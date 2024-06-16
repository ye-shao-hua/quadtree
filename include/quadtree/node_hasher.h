#pragma once
#include "node.h"
#include <cstddef>

namespace quadtree {
class NodeHasher {
public:
  NodeHasher(std::size_t min_value = 0,
             std::size_t max_value = static_cast<std::size_t>(-1));
  std::size_t operator()(const Node *node_point);

private:
  std::size_t _min_value;
  std::size_t _value_length;
};
} // namespace quadtree
