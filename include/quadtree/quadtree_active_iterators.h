#pragma once

#include "quadtree_iterators.h"
namespace quadtree {

class Quadtree;
class NodeIterator;
class NodeViewer;

class QuadtreeActiveIterators : public QuadtreeIterators {
public:
  using QuadtreeIterators::QuadtreeIterators;
  NodeIterator begin() override;
  NodeIterator end() override;
};
} // namespace quadtree
