#pragma once

namespace quadtree {
class Node;
class NodeViewer;
class NodeIterators;
class DynamicNodeList {
public:
  using index_type = unsigned int;

public:
  DynamicNodeList();
  ~DynamicNodeList();
  void push_back(NodeViewer node);
  bool empty() const;
  index_type size() const;
  index_type capacity() const;
  NodeIterators iterators();


private:
  NodeViewer*_nodes;
  index_type _size;
  index_type _capacity;
};
} // namespace quadtree
