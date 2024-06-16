#pragma once

#include "calling_stack.h"
#include "node.h"
namespace quadtree {
class Quadtree;
class Node;
class NodeIterator;
class NodeIterators;
class QuadtreeIterator {
public:
  using index_type = unsigned int;

public:
  QuadtreeIterator(Quadtree &quadtree, index_type index);
  QuadtreeIterator &operator++();
  Node &operator*();

private:
  Quadtree &_quadtree;
  CallingStack _calling_stack;
};
} // namespace quadtree
