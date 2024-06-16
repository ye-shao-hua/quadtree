#pragma once

namespace quadtree {
class Node;
class NodeViewer;
class NodeIterator {
public:
  using index_type = unsigned int;

public:
  NodeIterator() = delete;
  NodeIterator(const NodeIterator &that);
  NodeIterator(NodeViewer node[], index_type index);
  NodeIterator &operator=(const NodeIterator &that) = delete;
  NodeIterator &operator=(NodeIterator &&that) = delete;
  NodeIterator &operator++();
  NodeIterator operator++(int);
  [[nodiscard]] bool operator==(const NodeIterator &that) const {
    return _index == that._index;
  }
  [[nodiscard]] bool operator!=(const NodeIterator &that) const {
    return !(_index == that._index);
  }
  [[nodiscard]] NodeViewer& operator*();

private:
  NodeViewer *_node;
  index_type _index;
};
} // namespace quadtree
