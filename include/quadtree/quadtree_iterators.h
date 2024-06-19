#pragma once

namespace quadtree {

class Quadtree;
class NodeIterator;
class NodeViewer;

class QuadtreeIterators {
public:
  QuadtreeIterators(Quadtree &quadtree);
  virtual NodeIterator begin();
  virtual NodeIterator end();

protected:
  void _emplace(NodeViewer node);

protected:
  Quadtree &_quadtree;
};
} // namespace quadtree
