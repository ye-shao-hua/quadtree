#pragma once

namespace quadtree {

class Quadtree;
class NodeIterator;
class DynamicNodeList;
class NodeViewer;

class QuadtreeIterators {
public:
  QuadtreeIterators(Quadtree &quadtree);
  ~QuadtreeIterators();
  NodeIterator begin();
  NodeIterator end();
private:
  void _emplace(NodeViewer node);

private:
  DynamicNodeList* _node_list;
};
} // namespace quadtree
